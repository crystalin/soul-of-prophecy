#pragma once

#define GU_UNITTYPE_MONSTRE	0
#define GU_UNITTYPE_PNJ		1
#define GU_UNITTYPE_PLAYER	2

#define GU_CLASSTYPE_GAMEUNIT	0
#define GU_CLASSTYPE_GAMELIVING 1
#define GU_CLASSTYPE_GAMEPLAYER	(GU_CLASSTYPE_GAMELIVING+4)
#define GU_CLASSTYPE_GAMENPC	(GU_CLASSTYPE_GAMELIVING+8)

#define GU_DIRECTION_NORD		1
#define GU_DIRECTION_NORD_EST	2
#define GU_DIRECTION_EST		3
#define GU_DIRECTION_SUD_EST	4
#define GU_DIRECTION_SUD		5
#define GU_DIRECTION_SUD_OUEST	6
#define GU_DIRECTION_OUEST		7
#define GU_DIRECTION_NORD_OUEST	8

#define GU_MESSAGE_INDIRECT		0
#define GU_MESSAGE_DIRECT		1
#define GU_MESSAGE_SHOUT		2
#define GU_MESSAGE_PAGE			3
#define GU_MESSAGE_GM			4

class GameUnit
{
public:
	GameUnit(void);
	~GameUnit(void);
	
	int		ID;
	int		SkinID;
	char	Name[256];

	int		X;
	int		Y;
	int		World;

	int		HP;
	int		HP_Max;

	int		UnitType;
	int		ClassType;
	
	virtual void MoveTo(int Direction);
	virtual void Say(int Type, char *message, char *Channel_Target);

};
