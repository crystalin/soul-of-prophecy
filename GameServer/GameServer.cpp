// GameServer.cpp : définit le point d'entrée pour l'application DLL.
//

#include "stdafx.h"

#define GAMGESERVERDLL_EXPORTS
#include "GameServer.h"

GameServer *GameServer::m_currentgameserver=NULL;
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

GameServer::GameServer()
{
	NS = new NetServer();
	CM = new ClientManager(this);
	PM = new PacketManager(this);
	hThreadPacketReading=NULL;
	m_currentgameserver=this;
}

GameServer::~GameServer()
{
	delete NS;
	delete CM;
	delete PM;
}

bool GameServer::Start()
{
	Init();
	CM->Init();
	PM->Init();
	NS->Start();
	return true;
}

bool GameServer::Resume()
{
	NS->Resume();
	ResumeThread(hThreadPacketReading);
	return true;
}

bool GameServer::Pause()
{
	NS->Pause();
	SuspendThread(hThreadPacketReading);
	return true;
}

bool GameServer::Stop()
{
	UnInit();
	NS->Stop();
	CM->UnInit();
	PM->UnInit();
	
	return true;
}

bool GameServer::Init()
{
	DWORD dThread1;
	m_UnitList=new ArrayList(1000);
	hThreadPacketReading= CreateThread( NULL,
					0,
					(LPTHREAD_START_ROUTINE)GetAnalyseFunction,
					(LPVOID)this,
					0,
					&dThread1 );

	return true;
}

bool GameServer::UnInit()
{
	TerminateThread(hThreadPacketReading,0);
	delete m_UnitList;
	return true;
}

DWORD GameServer::PacketReading()
{
	GamePacketIn* Pak;
	GameClient *Client;
	while (1)
	{
		Sleep(10);
		Pak = NS->GetNextDecodedPacket();
		while (Pak!=NULL)
		{
			Client = CM->GetClientByAddress(Pak->GetAddress());
			if (Client==NULL) //Le client exist ...
			{
				Client=CM->CreateNewClient(Pak->GetAddress());
				printf("GameServer : Creation du client [%d] address : %s \n",Client->GetID(),inet_ntoa(Client->GetAddrSock().sin_addr));
			}
			PM->RunPacketIn(Client,Pak);
			Pak = NS->GetNextDecodedPacket();
		}		
	}

}

ArrayList *GameServer::GetAllUnits()
{
	ArrayList *AllUnits = new ArrayList(m_UnitList->Count());
	for (int i=0 ; i < m_UnitList->Count();i++)
	{
		AllUnits->Add(m_UnitList->GetArray(i));
	}
	return AllUnits;
}

ArrayList *GameServer::GetAllLivings()
{
	ArrayList *AllLivings = new ArrayList(m_UnitList->Count());
	GameUnit *Unit;
	for (int i=0 ; i < m_UnitList->Count();i++)
	{
		Unit=(GameUnit*)m_UnitList->GetArray(i);
		if ((Unit->ClassType & GU_CLASSTYPE_GAMELIVING )==GU_CLASSTYPE_GAMELIVING)
			AllLivings->Add(Unit);
	}
	return AllLivings;
}

ArrayList *GameServer::GetAllPlayers()
{
	ArrayList *AllPlayers = new ArrayList(m_UnitList->Count());
	GameUnit *Unit;
	for (int i=0 ; i < m_UnitList->Count();i++)
	{
		Unit=(GameUnit*)m_UnitList->GetArray(i);
		if ((Unit->ClassType & GU_CLASSTYPE_GAMEPLAYER )==GU_CLASSTYPE_GAMEPLAYER)
			AllPlayers->Add(Unit);
	}
	return AllPlayers;
}
	
ArrayList *GameServer::GetUnitsCloseTo(int X, int Y, int World)
{
	ArrayList *Units = new ArrayList(m_UnitList->Count());
	GameUnit *Unit;
	for (int i=0 ; i < m_UnitList->Count();i++)
	{
		Unit=(GameUnit*)m_UnitList->GetArray(i);
		if ((Unit->World == World)&&
			(sqrt(pow(Unit->X-X,2)+pow(Unit->Y-Y,2))< GS_VIEW_DISTANCE ))
			Units->Add(Unit);
	}
	return Units;
}

ArrayList *GameServer::GetLivingsCloseTo(int X, int Y, int World)
{
	ArrayList *Livings = new ArrayList(m_UnitList->Count());
	GameUnit *Unit;
	for (int i=0 ; i < m_UnitList->Count();i++)
	{
		Unit=(GameUnit*)m_UnitList->GetArray(i);
		if ((Unit->World == World)&&
			((Unit->ClassType & GU_CLASSTYPE_GAMELIVING )== GU_CLASSTYPE_GAMELIVING )&&
			(sqrt(pow(Unit->X-X,2)+pow(Unit->Y-Y,2))< GS_VIEW_DISTANCE ))
			Livings->Add(Unit);
	}
	return Livings;
}

ArrayList *GameServer::GetPlayersCloseTo(int X, int Y, int World)
{
	ArrayList *Players = new ArrayList(m_UnitList->Count());
	GameUnit *Unit;
	for (int i=0 ; i < m_UnitList->Count();i++)
	{
		Unit=(GameUnit*)m_UnitList->GetArray(i);
		if ((Unit->World == World)&&
			((Unit->ClassType & GU_CLASSTYPE_GAMEPLAYER )== GU_CLASSTYPE_GAMEPLAYER )&&
			(sqrt(pow(Unit->X-X,2)+pow(Unit->Y-Y,2))< GS_VIEW_DISTANCE ))
			Players->Add(Unit);
	}
	return Players;
}

ArrayList *GameServer::GetUnitsCloseToUnit(GameUnit *unit)
{
	return GetUnitsCloseTo(unit->X,unit->Y,unit->World);
}

ArrayList *GameServer::GetLivingsCloseToUnit(GameUnit *unit)
{
	return GetLivingsCloseTo(unit->X,unit->Y,unit->World);
}

ArrayList *GameServer::GetPlayersCloseToUnit(GameUnit *unit)
{
	return GetPlayersCloseTo(unit->X,unit->Y,unit->World);
}

void GameServer::AddUnit(GameUnit *Unit)
{
	printf(":::::Unit[%d] Added:::::\n",Unit->ID);
	ArrayList *Players = GetPlayersCloseToUnit(Unit);
	for (int i =0; i<Players->Count();i++)
	{
		GamePlayer *Player=(GamePlayer *)Players->GetArray(i);
			PM->Send_01_UpdateCoordinates((GameClient *)Player->m_client,Unit);
	}
	delete Players;

	m_UnitList->Add(Unit);

}

void GameServer::RemoveUnit(GameUnit *Unit)
{
	printf(":::::Unit[%d] Removed:::::\n",Unit->ID);
	m_UnitList->Remove(Unit);

	ArrayList *Players = GetPlayersCloseToUnit(Unit);
	for (int i =0; i<Players->Count();i++)
	{
		GamePlayer *Player=(GamePlayer *)Players->GetArray(i);
		PM->Send_11_RemoveUnit((GameClient *)(Player->m_client),Unit);
	}
	delete Players;
}

GameUnit *GameServer::GetUnitByID(int ID)
{
	GameUnit *Unit=NULL;
	for (int i = 0 ; i < m_UnitList->Count();i++)
	{
		Unit=(GameUnit *)m_UnitList->GetArray(i);
		if (Unit->ID==ID)
			return Unit;
	}
	return Unit;
}
