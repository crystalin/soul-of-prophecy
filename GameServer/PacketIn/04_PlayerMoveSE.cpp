#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_04_PlayerMoveSE(GameClient *Client, GamePacketIn *InPak)
{
	Client->Player->MoveTo(GU_DIRECTION_SUD_EST);
}