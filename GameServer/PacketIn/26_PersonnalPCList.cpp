#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_26_PersonnalPCList(GameClient *Client, GamePacketIn *InPak)
{
	ArrayList *Players = new ArrayList(1);
	Players->Add(Client->Player);
	Send_26_PersonnalPCList(Client,Players);	//penser a mettre en argument le nb de persos puis les persos !
	delete Players;
}