#pragma once

#ifdef SERVERBASE_EXPORTS 
#define SERVERBASE_API __declspec(dllexport) 
#else 
#define SERVERBASE_API __declspec(dllimport) 
#endif 


#define PACKETIN_MAX_SIZE	4096
#define PACKETOUT_MAX_SIZE	2048

#define PACKET_TYPE_MESSAGE			00
#define PACKET_TYPE_ACK_RESPONSE	01

#define PACKET_FLAG_ACK_REQUEST		02
#define PACKET_FLAG_FRAGMENTED		04

#define PACKET_CRYPT_KEY			0x7D2D4D

#include <windows.h>
#include <stdio.h>

class ObjectArrays;
class SERVERBASE_API QueueList;
class SERVERBASE_API ArrayList;

class SERVERBASE_API PacketIn;
class SERVERBASE_API PacketOut;
class SERVERBASE_API ClientBase;

#include ".\QueueList.h"
#include ".\ArrayList.h"
#include ".\PacketIn.h"
#include ".\PacketOut.h"
#include ".\ClientBase.h"

/*#include ".\GameClient.h"
#include ".\GamePacketOut.h"
#include ".\GamePacketIn.h"*/
