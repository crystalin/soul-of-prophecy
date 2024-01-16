#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_03_PlayerMoveE(GameClient *Client, GamePacketIn *InPak)
{
	Client->Player->MoveTo(GU_DIRECTION_EST);
}