#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_10_KeepAlive(GameClient *Client)
{
	GamePacketOut *NewPacket = new GamePacketOut(10);

	Client->SendPacket(NewPacket);	
}