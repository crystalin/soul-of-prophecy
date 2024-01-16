#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_68_PuppetInformation(GameClient *Client, GamePacketIn *InPak)
{
	int UnitID = InPak->ReadInt();
	int UnitX  = InPak->ReadShort();
	int UnitY  = InPak->ReadShort();

	GameUnit *Unit = GameServer::m_currentgameserver->GetUnitByID(UnitID);
	if (Unit!=NULL)
	{
		Send_68_PuppetInfo(Client,Unit);
		if (Unit->ClassType==GU_CLASSTYPE_GAMEPLAYER)
		{
			Send_68_PuppetInfo((GameClient *)(((GamePlayer *)Unit)->m_client),Client->Player);
			Send_01_UpdateCoordinates((GameClient *)(((GamePlayer *)Unit)->m_client),Client->Player);
		}

	}

	
}