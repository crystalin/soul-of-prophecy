#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_02_PlayerMoveNE(GameClient *Client, GamePacketIn *InPak)
{
	Client->Player->MoveTo(GU_DIRECTION_NORD_EST);
}