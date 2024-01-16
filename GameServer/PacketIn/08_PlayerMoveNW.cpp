#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_08_PlayerMoveNW(GameClient *Client, GamePacketIn *InPak)
{
	Client->Player->MoveTo(GU_DIRECTION_NORD_OUEST);
}