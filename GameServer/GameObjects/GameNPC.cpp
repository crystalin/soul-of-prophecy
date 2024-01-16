#include "StdAfx.h"
#include ".\gamenpc.h"

GameNPC::GameNPC(void)
{
	printf("=!=!= NPC %d Created =!=!=\n",ID);
	sprintf(Name,"NPC %d",ID);
}

GameNPC::~GameNPC(void)
{
}
