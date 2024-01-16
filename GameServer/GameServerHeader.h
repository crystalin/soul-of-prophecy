#pragma once
#ifdef GAMGESERVERDLL_EXPORTS 
#define GAMGESERVERDLL_API __declspec(dllexport) 
#else 
#define GAMGESERVERDLL_API __declspec(dllimport) 
#endif 

#define GAMESERVER_MAX_CLIENTS 30

#include <math.h>
#include "..\NetWork\NetHeader.h"
#include "..\ServerBase\ServerBase.h"

class GameClient;
class GAMGESERVERDLL_API GameServer;
class ClientManager;
class PacketManager;

#include ".\GameServer.h"