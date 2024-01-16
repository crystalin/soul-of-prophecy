#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_06_PlayerMoveSW(GameClient *Client, GamePacketIn *InPak)
{
	Client->Player->MoveTo(GU_DIRECTION_SUD_OUEST);
}