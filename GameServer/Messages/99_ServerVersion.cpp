#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_99_ServerVersion(GameClient *Client,UINT Response)
{
	GamePacketOut *NewPacket = new GamePacketOut(99);
	NewPacket->WriteInt(Response);

	Client->SendPacket(NewPacket);	
}