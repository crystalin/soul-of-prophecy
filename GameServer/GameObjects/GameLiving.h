#pragma once
#include "GameUnit.h"

class GameLiving : public GameUnit
{
public:
	GameLiving(void);
	~GameLiving(void);
	
	int Mana;
	int Mana_Max;

	__int64 XP;
	__int64 XP_Next_Level;
	__int64 XP_In_Level;

	int Force;
	int Endurance;
	int Dexterite;
	//int Volonté;
	int Sagesse;
	int Intelligence;
	//int Chance;

	int Or;
	int Niveau;

	int AF;

};
