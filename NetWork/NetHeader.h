#pragma once
#ifdef NETWORKDLL_EXPORTS 
#define NETWORKDLL_API __declspec(dllexport) 
#else 
#define NETWORKDLL_API __declspec(dllimport) 
#endif 

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#include "..\ServerBase\ServerBase.h"
#include "GamePacketIn.h"
#include "GamePacketOut.h"
#include "AckPacketOut.h"

class SERVERBASE_API GamePacketOut;
class SERVERBASE_API GamePacketIn;
class SERVERBASE_API AckPacketOut;
class NETWORKDLL_API NetServer;

#include "NetWork.h"