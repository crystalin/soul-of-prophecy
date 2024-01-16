#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_66_Connection(GameClient *Client, GamePacketIn *InPak)
{
	printf("connection !!!");
	Send_66_MOTD(Client,"Bienvenue sur <<<== Soul of Prophety ==>>>");
}