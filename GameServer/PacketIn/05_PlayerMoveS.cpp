#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_05_PlayerMoveS(GameClient *Client, GamePacketIn *InPak)
{
	Client->Player->MoveTo(GU_DIRECTION_SUD);
}