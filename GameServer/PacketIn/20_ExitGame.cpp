#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_20_ExitGame(GameClient *Client, GamePacketIn *InPak)
{
	Client->ExitGame();
	printf("Client a quitte le jeu !\n");	//ici détruire le client
}