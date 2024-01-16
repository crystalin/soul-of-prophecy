#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_15_DeletePlayer(GameClient *Client,int IsDelete)
{
	GamePacketOut *NewPacket = new GamePacketOut(15);
	NewPacket->WriteByte(IsDelete);

	Client->SendPacket(NewPacket);	
}