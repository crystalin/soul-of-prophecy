// DebugConsole.cpp : définit le point d'entrée pour l'application console.
//

#define DEBUGMODE

#include "stdafx.h"
#include "DebugConsole.h"

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Lancement du server\n");

	GameServer *GS=new GameServer();

	GS->Start();


	while (1)
	{
		//GS->NS->Start();
		//GS->NS->Stop();
		Sleep(1000);
	}
	return 0;
}

