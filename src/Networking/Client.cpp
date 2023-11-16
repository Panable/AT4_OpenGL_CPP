#include "Client.h"

Networking::Client* Networking::Client::m_CallbackInstance = nullptr;

void Networking::Client::Run()
{
}

void Networking::Client::SteamNetConnectionStatusChangedCallback(SteamNetConnectionStatusChangedCallback_t* pInfo)
{
    m_CallbackInstance->OnSteamNetConnectionStatusChanged(pInfo);
}

void Networking::Client::Tick()
{
    m_IsRunning = true;
    // Select instance to use.  For now we'll always use the default.
    m_pInterface = SteamNetworkingSockets();

    // Start connecting
    char szAddr[SteamNetworkingIPAddr::k_cchMaxString];
    m_AddrServer.ToString(szAddr, sizeof(szAddr), true);
    printf("Connecting to chat server at %s", szAddr);
    SteamNetworkingConfigValue_t opt;
    opt.SetPtr(k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged,
               (void*) SteamNetConnectionStatusChangedCallback);
    m_Connection = m_pInterface->ConnectByIPAddress(m_AddrServer, 1, &opt);
    if (m_Connection == k_HSteamNetConnection_Invalid)
        printf("Failed to create connection");

    while (m_IsRunning)
    {
        PollIncomingMessages();
        PollConnectionStateChanges();
        PollLocalUserInput();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }


    NukeProcess(0);
    GameNetworkingSockets_Kill();
}

Networking::Client::Client(SteamNetworkingIPAddr addrServer, Game& game) :
        m_AddrServer(addrServer), m_Game(game)
{

}

Networking::Client::~Client()
{
    m_IsRunning = false;
}

void Networking::Client::ParseFloatsFromVoidPtr(void* data, float& x, float& y)
{
    // Convert void* to string
    std::string inputString = static_cast<char*>(data);

    // Create a string stream to parse the input
    std::stringstream ss(inputString);

    // Define variables to store the extracted floats
    float firstFloat, secondFloat;

    // Extract the floats from the string
    char comma; // To store the comma
    ss >> firstFloat >> comma >> secondFloat;

    // Check if extraction was successful
    if (ss.fail() || comma != ',')
    {
        std::cerr << "Error: Unable to extract floats from the string." << std::endl;
        // Handle the error in your own way
    } else
    {
        // Print the extracted floats
        x = firstFloat;
        y = secondFloat;
        std::cout << "First Float: " << firstFloat << std::endl;
        std::cout << "Second Float: " << secondFloat << std::endl;
    }
}

void Networking::Client::PollIncomingMessages()
{
    if (!m_Game.m_IsInitialized)
        return;
    while (m_IsRunning)
    {
        ISteamNetworkingMessage* pIncomingMsg = nullptr;
        int numMsgs = m_pInterface->ReceiveMessagesOnConnection(m_Connection, &pIncomingMsg, 1);
        if (numMsgs == 0)
            break;
        if (numMsgs < 0)
            std::cout << "ERROR" << std::endl;

        // Just echo anything we get from the server

        float x, y;

        ParseFloatsFromVoidPtr(pIncomingMsg->m_pData, x, y);

        m_Game.SetPlayer(x, y);

        // We don't need this anymore.
        pIncomingMsg->Release();
    }
}

void Networking::Client::PollConnectionStateChanges()
{
    m_CallbackInstance = this;
    m_pInterface->RunCallbacks();
}

//something something send data to server
void Networking::Client::PollLocalUserInput()
{
    if (!m_Game.m_IsInitialized) return;
    std::string cmd = m_Game.GetCoordinates();
    m_pInterface->SendMessageToConnection(m_Connection, cmd.c_str(), (uint32) cmd.length(),
                                          k_nSteamNetworkingSend_UnreliableNoDelay, nullptr);
}

void Networking::Client::OnSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* pInfo)
{
    assert(pInfo->m_hConn == m_Connection || m_Connection == k_HSteamNetConnection_Invalid);

    // What's the state of the connection?
    switch (pInfo->m_info.m_eState)
    {
        case k_ESteamNetworkingConnectionState_None:
            // NOTE: We will get callbacks here when we destroy connections.  You can ignore these.
            break;

        case k_ESteamNetworkingConnectionState_ClosedByPeer:
        case k_ESteamNetworkingConnectionState_ProblemDetectedLocally:
        {
            m_IsRunning = false;

            // Print an appropriate message
            if (pInfo->m_eOldState == k_ESteamNetworkingConnectionState_Connecting)
            {
                // Note: we could distinguish between a timeout, a rejected connection,
                // or some other transport problem.
                printf("We sought the remote host, yet our efforts were met with defeat.  (%s)",
                       pInfo->m_info.m_szEndDebug);
            } else if (pInfo->m_info.m_eState == k_ESteamNetworkingConnectionState_ProblemDetectedLocally)
            {
                printf("Alas, troubles beset us; we have lost contact with the host.  (%s)",
                       pInfo->m_info.m_szEndDebug);
            } else
            {
                // NOTE: We could check the reason code for a normal disconnection
                printf("The host hath bidden us farewell.  (%s)", pInfo->m_info.m_szEndDebug);
            }

            // Clean up the connection.  This is important!
            // The connection is "closed" in the network sense, but
            // it has not been destroyed.  We must close it on our end, too
            // to finish up.  The reason information do not matter in this case,
            // and we cannot linger because it's already closed on the other end,
            // so we just pass 0's.
            m_pInterface->CloseConnection(pInfo->m_hConn, 0, nullptr, false);
            m_Connection = k_HSteamNetConnection_Invalid;
            break;
        }
    }
}