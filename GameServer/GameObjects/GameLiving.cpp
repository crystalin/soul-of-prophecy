#include "StdAfx.h"
#include ".\gameliving.h"

GameLiving::GameLiving(void)
{

	strcpy(Name,"Living");

	Mana=100;
	Mana_Max=100;

	XP=100;
	XP_Next_Level=3000;
	XP_In_Level=500;

	Force=20;
	Endurance=20;
	Dexterite=20;
	//int Volonté;
	Sagesse=20;
	Intelligence=20;
	//int Chance;

	Or=100;
	Niveau=1;

	AF=5;
	ClassType=GU_CLASSTYPE_GAMELIVING;
}

GameLiving::~GameLiving(void)
{
}
