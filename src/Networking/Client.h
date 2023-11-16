#pragma once
#include "ClientManager.h"

namespace Networking
{
    class Client
    {
    public:
        void Run();
        Client(SteamNetworkingIPAddr addrServer, Game& game);

        ~Client();

        bool m_IsRunning = true;

        void Tick();

    private:
        SteamNetworkingIPAddr m_AddrServer;
        HSteamNetConnection m_Connection;
        ISteamNetworkingSockets* m_pInterface;
        void PollIncomingMessages();
        void PollConnectionStateChanges();
        void PollLocalUserInput();
        void OnSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* pInfo);
        static Client* m_CallbackInstance;
        static void SteamNetConnectionStatusChangedCallback(SteamNetConnectionStatusChangedCallback_t* pInfo);
        void ParseFloatsFromVoidPtr(void* data, float& x, float& y);
        Game& m_Game;
    };
}