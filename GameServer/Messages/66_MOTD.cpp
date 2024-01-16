#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_66_MOTD(GameClient *Client,char *Message)
{
	GamePacketOut *NewPacket = new GamePacketOut(66);
	NewPacket->WritePascalString(Message);
	Client->SendPacket(NewPacket);
}