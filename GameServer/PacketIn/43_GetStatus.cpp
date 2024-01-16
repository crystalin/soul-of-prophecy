#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_43_GetStatus(GameClient *Client, GamePacketIn *InPak)
{
	Send_43_SetStatus(Client,Client->Player);
}