#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_46_FromPreInGameToInGame(GameClient *Client, GamePacketIn *InPak)
{
	Client->Player->EnterInGame();
}