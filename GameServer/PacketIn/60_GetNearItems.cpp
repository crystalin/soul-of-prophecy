#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_60_GetNearItems(GameClient *Client, GamePacketIn *InPak)
{
	ArrayList * Units=new ArrayList(0);//liste vide pour les tests

	Send_16_InViewUnits(Client,Units);
	delete Units;
}