#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_28_Shout(GameClient *Client, GamePacketIn *InPak)
{

	delete InPak->ReadPascalString();

	int Couleur = InPak->ReadInt(); // UseLess

	char *Message = InPak->ReadPascalString();


	if (strlen(Message)==0)
	{
		delete Message;
		return;
	}

	Client->Player->Say(GU_MESSAGE_SHOUT,Message,"Main");
	delete Message;
}