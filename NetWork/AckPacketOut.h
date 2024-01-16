#pragma once
#define NETWORKDLL_EXPORTS 
#include "NetHeader.h"

class NETWORKDLL_API AckPacketOut :	public PacketOut
{
public:
	AckPacketOut(int PacketID);
	~AckPacketOut(void);
};
