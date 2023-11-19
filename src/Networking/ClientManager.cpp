#include "ClientManager.h"
#include "Client.h"
#include "Program.h"
#include <csignal>
#include <unistd.h>


SteamNetworkingMicroseconds g_logTimeZero;

#define PRINT_NETWORK_ERROR(message) \
    do { \
        std::cout << "[NETWORK ERROR] " << message << std::endl; \
    } while (false)

void Networking::SignalHandler(int signum)
{
    kill( getpid(), SIGKILL );
}

void Networking::Run(Game& game)
{

    //Register Signal
    signal(SIGUSR1, SignalHandler);
    pid_t myPID = getpid();
    std::cout << "My Process ID (PID): " << myPID << std::endl;


    SteamNetworkingIPAddr addrServer;
    addrServer.Clear();

    addrServer.ParseString(IP_ADDR);
    addrServer.m_port = DEFAULT_SERVER_PORT;

    SteamDatagramErrMsg errMsg;
    if (!GameNetworkingSockets_Init(nullptr, errMsg))
    {
        PRINT_NETWORK_ERROR("GameNetworkingSockets_Init failed. " + std::string(errMsg));
    }
    g_logTimeZero = SteamNetworkingUtils()->GetLocalTimestamp();

    SteamNetworkingUtils()->SetDebugOutputFunction(k_ESteamNetworkingSocketsDebugOutputType_Msg, DebugOutput);

    Client client(addrServer, game);

    // Start the client thread
    client.Tick();

    client.m_IsRunning = false;
    std::cout << "CLIENT HAS STOPPED" << std::endl;
}

static void Networking::DebugOutput(ESteamNetworkingSocketsDebugOutputType eType, const char* pszMsg)
{
    SteamNetworkingMicroseconds time = SteamNetworkingUtils()->GetLocalTimestamp() - g_logTimeZero;
    printf("%10.6f %s\n", time * 1e-6, pszMsg);
    fflush(stdout);
    if (eType == k_ESteamNetworkingSocketsDebugOutputType_Bug)
    {
        fflush(stdout);
        fflush(stderr);
        NukeProcess(1);
    }
}

void Networking::NukeProcess(int rc)
{

}
