#include "StdAfx.h"
#define GAMGESERVERDLL_EXPORTS
#include ".\gameplayer.h"
#include "..\gameclient.h"

GamePlayer::GamePlayer(ClientBase *Client)
{
	m_client=Client;
	ClassType=GU_CLASSTYPE_GAMEPLAYER;

	printf("><>< Player %d Created on Client [%d] ><><\n",ID,m_client->GetID());
	X = 2942;
	Y = 1059;
	SkinID= 10012;
	World = 0;

	Karma = 0;
	Encombrement = 50;
	Encombrement_Max = 70;
	Skill_Points = 20;
	Stats_Points = 0;

	sprintf(Name,"Player %d",ID);
}

GamePlayer::~GamePlayer(void)
{
}

void GamePlayer::EnterInGame()
{
	//GamePlayer *neplay= new GamePlayer(m_client);
	//((GameClient *)m_client)->GS->AddUnit(neplay);
	ArrayList *Units = ((GameClient *)m_client)->GS->GetUnitsCloseToUnit(this);
	((GameClient *)m_client)->GS->PM->Send_46_FromPreInGameToInGame((GameClient *)m_client,Units);
	((GameClient *)m_client)->GS->AddUnit(this);
	printf("><>< Player %d Entered the Game with %d around ><><\n",ID,Units->Count());
	((GameClient *)m_client)->GS->PM->Send_68_PuppetInfo((GameClient *)m_client,this);
	delete Units;
}

void GamePlayer::MoveTo(int Direction)
{
	GameUnit::MoveTo(Direction);
	//printf("><><  %d Players in the Zone ><><\n",AllPlayers->Count());
		
	((GameClient *)m_client)->GS->PM->Send_09_SynchronizePlayerCoordinates((GameClient *)m_client);
}