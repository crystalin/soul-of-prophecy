#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_07_PlayerMoveW(GameClient *Client, GamePacketIn *InPak)
{
	Client->Player->MoveTo(GU_DIRECTION_OUEST);
}