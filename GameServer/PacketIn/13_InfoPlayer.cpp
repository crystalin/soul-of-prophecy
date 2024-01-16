#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_13_InfoPlayer(GameClient *Client, GamePacketIn *InPak)
{
	//GamePlayer  * Player=new GamePlayer(Client);//juste pour compiler

	Send_13_InfoPlayer(Client, Client->Player);
	Send_33_UpdateLife(Client, Client->Player);
	//Send_67
	//Send_53
	//Send_19
	//Send_53
	//Send_13
	//Send_18
	//Send_68
	//Send_16
	//Send_97
	//Send_97
	//Send_39


	//delete Player;
}