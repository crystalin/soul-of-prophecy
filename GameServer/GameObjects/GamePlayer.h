#pragma once
#include "GameLiving.h"
#include "..\..\ServerBase\ClientBase.h"

class GamePlayer : public GameLiving
{
public:
	GamePlayer(ClientBase *Client);
	~GamePlayer(void);

	void EnterInGame();
	void MoveTo(int Direction);

	ClientBase *m_client;

	int Skill_Points;
	int Stats_Points;
	int Encombrement;
	int Encombrement_Max;

	int Karma;

private:

};