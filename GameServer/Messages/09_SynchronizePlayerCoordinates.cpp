#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_09_SynchronizePlayerCoordinates(GameClient *Client)
{
	GamePacketOut *NewPacket = new GamePacketOut(9);
	NewPacket->WriteShort(Client->Player->X);
	NewPacket->WriteShort(Client->Player->Y);
	NewPacket->WriteShort(Client->Player->World);
	Client->SendPacket(NewPacket);
}