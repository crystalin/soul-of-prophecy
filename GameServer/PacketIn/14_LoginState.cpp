#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_14_LoginState(GameClient *Client, GamePacketIn *InPak)
{
	printf("Login !!");
	Send_14_LoginState(Client,0,"Bienvenue SoP !");//0=ok, 1=invalide, 2= dejà loggé
}