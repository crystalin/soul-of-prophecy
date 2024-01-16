#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_11_RemoveUnit(GameClient *Client,GameUnit *Unit)
{
	GamePacketOut *NewPacket = new GamePacketOut(11);
	NewPacket->WriteByte(0x00);
	NewPacket->WriteInt(Unit->ID);
	Client->SendPacket(NewPacket);
}