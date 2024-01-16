#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_27_IndirectTalk(GameClient *Client, GamePacketIn *InPak)
{

	int UnitID = InPak->ReadInt();
	int UnitDir = InPak->ReadByte();
	int MessageColor = InPak->ReadInt(); // UseLess
	char *Message = InPak->ReadPascalString();
	if (strlen(Message)==0)
	{
		delete Message;
		return;
	}
	Client->Player->Say(GU_MESSAGE_INDIRECT,Message,NULL);
	delete Message;
}