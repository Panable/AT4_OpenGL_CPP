#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <algorithm>
#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <map>
#include <cctype>

#include <steam/steamnetworkingsockets.h>
#include <steam/isteamnetworkingutils.h>
#include "Game.h"

#ifndef STEAMNETWORKINGSOCKETS_OPENSOURCE
#include <steam/steam_api.h>
#endif

#ifdef _WIN32
#include <windows.h> // Ug, for NukeProcess -- see below
#elseaa

#include <unistd.h>
#include <signal.h>

#endif

namespace Networking
{
    static const uint16 DEFAULT_SERVER_PORT = 27020;
    static const char* IP_ADDR = "127.0.0.1";

    static void DebugOutput(ESteamNetworkingSocketsDebugOutputType eType, const char* pszMsg);
    void NukeProcess(int rc);
    /**
     * Run/Initialize the client.
     */
    void Run(Game& game);

    void Init();
}