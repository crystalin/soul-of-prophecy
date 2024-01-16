#include "StdAfx.h"
#include ".\ackpacketout.h"

AckPacketOut::AckPacketOut(int PacketID)
{
	WriteByte(0x00);//No fragments
	WriteByte(PACKET_TYPE_ACK_RESPONSE);//Simple Message
	WriteShort(0x00);//Reserved for PacketSize
	WriteInversedInt(PacketID);//Packet ID
	WriteInversedInt(0x50);//Packet MasterID
}

AckPacketOut::~AckPacketOut(void)
{
}
