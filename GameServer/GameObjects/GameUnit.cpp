#include "StdAfx.h"
#include "..\Gameserver.h"
#include ".\gameunit.h"
#include "..\..\ServerBase\serverbase.h"

GameUnit::GameUnit(void)
{
	
	ID=GetTickCount();
	SkinID=0;

	memset(Name,0,sizeof(Name));
	strcpy(Name,"Unit");

	X=0;
	Y=0;
	World=0;

	HP=100;
	HP_Max=100;

	ClassType = GU_CLASSTYPE_GAMEUNIT;
}

GameUnit::~GameUnit(void)
{
}

void GameUnit::MoveTo(int Direction)
{
	switch (Direction)
	{
	case GU_DIRECTION_NORD :
		Y--;
		break;
	case GU_DIRECTION_NORD_EST :
		X++;
		Y--;
		break;
	case GU_DIRECTION_EST :
		X++;
		break;
	case GU_DIRECTION_SUD_EST :
		X++;
		Y++;
		break;
	case GU_DIRECTION_SUD :
		Y++;
		break;
	case GU_DIRECTION_SUD_OUEST :
		X--;
		Y++;
		break;
	case GU_DIRECTION_OUEST :
		X--;
		break;
	case GU_DIRECTION_NORD_OUEST :
		X--;
		Y--;
		break;
	}

	ArrayList *AllPlayers= GameServer::m_currentgameserver->GetPlayersCloseToUnit(this);
	for (int i=0;i<AllPlayers->Count();i++)
	{
		GamePlayer *Player = (GamePlayer *)AllPlayers->GetArray(i);
		if (Player != this)
			GameServer::m_currentgameserver->PM->Send_01_UpdateCoordinates((GameClient *)Player->m_client,this);
	}
	delete AllPlayers;
}


void GameUnit::Say(int Type, char *message, char *Channel_Target)
{
	switch(Type)
	{
	case GU_MESSAGE_INDIRECT:
		{
			ArrayList *AllPlayers=GameServer::m_currentgameserver->GetPlayersCloseToUnit(this);
			for (int i=0;i<AllPlayers->Count();i++)
			{
				GamePlayer *Player = (GamePlayer *)AllPlayers->GetArray(i);
				GameServer::m_currentgameserver->PM->Send_27_LocalChatMessage((GameClient *)Player->m_client,this,message);
			}
			delete AllPlayers;
		}
		break;
	case GU_MESSAGE_DIRECT:
		{
			//Send direct message
		}
		break;
	case GU_MESSAGE_SHOUT:
		{
			ArrayList *AllPlayers=GameServer::m_currentgameserver->GetAllPlayers();
			for (int i=0;i<AllPlayers->Count();i++)
			{
				GamePlayer *Player = (GamePlayer *)AllPlayers->GetArray(i);
				GameServer::m_currentgameserver->PM->Send_49_ChannelMessage((GameClient *)Player->m_client,this,message,Channel_Target);
			}
			delete AllPlayers;
		}
		break;
	case GU_MESSAGE_PAGE:
		{
			//Send page  message
		}
		break;
	case GU_MESSAGE_GM:
		{
			//Send gm message
		}
		break;
	}
}