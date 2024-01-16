#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_99_ServerVersion(GameClient *Client, GamePacketIn *InPak)
{
	
	UINT Version=InPak->ReadInt();
	printf("Version Client : %d\n",Version);

	Send_99_ServerVersion(Client,1);//1=ok, 0 (et autres chiffres d'ailleurs)= version incompatible
}