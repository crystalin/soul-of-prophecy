#pragma once
#define GAMGESERVERDLL_EXPORTS
#include "GameServerHeader.h"
#include "ClientManager.h"
#include "PacketManager.h"
#include "GameClient.h"
#include ".\GameObjects\GameUnit.h"
#include ".\GameObjects\GameLiving.h"
#include ".\GameObjects\GamePlayer.h"
#include ".\GameObjects\GameNPC.h"

#define GS_VIEW_DISTANCE 50

class GAMGESERVERDLL_API GameServer // GameServer
{
public:
	GameServer();
	~GameServer();
	bool Start();
	bool Resume();
	bool Pause();
	bool Stop();

	NetServer		*NS;
	ClientManager	*CM;	
	PacketManager	*PM;
	static GameServer	*m_currentgameserver;

	ArrayList *GetAllUnits();
	ArrayList *GetAllLivings();
	ArrayList *GetAllPlayers();

	ArrayList *GetUnitsCloseTo(int X,int Y,int World);
	ArrayList *GetLivingsCloseTo(int X,int Y,int World);
	ArrayList *GetPlayersCloseTo(int X,int Y,int World);

	ArrayList *GetUnitsCloseToUnit(GameUnit *Unit);
	ArrayList *GetLivingsCloseToUnit(GameUnit *Unit);
	ArrayList *GetPlayersCloseToUnit(GameUnit *Unit);

	void AddUnit(GameUnit *Unit);
	void RemoveUnit(GameUnit *Unit);

	//GamePlayer	*GetPlayerByID(int ID);
	GameUnit	*GetUnitByID(int ID);

private:
	bool Init();
	bool UnInit();
	DWORD PacketReading();

	HANDLE				hThreadPacketReading;

	static	DWORD CALLBACK GameServer::GetAnalyseFunction(LPVOID lpParameter)
	{
		return ((GameServer*)lpParameter)->PacketReading();
	}

	ArrayList *m_UnitList;

};