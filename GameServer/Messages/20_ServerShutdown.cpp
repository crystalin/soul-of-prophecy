#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_20_ServerShutdown(GameClient *Client)
{
	GamePacketOut *NewPacket = new GamePacketOut(20);
	

	Client->SendPacket(NewPacket);	

}