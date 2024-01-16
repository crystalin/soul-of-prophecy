#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_26_PersonnalPCList(GameClient *Client, ArrayList *Players)
{
	GamePacketOut *NewPacket = new GamePacketOut(26);

	if (Players!=NULL)
	{
		NewPacket->WriteByte(Players->Count());
		for (BYTE i=0;i<Players->Count();i++)
		{	
			GamePlayer *Player = (GamePlayer *)Players->GetArray(i);
			NewPacket->WriteByte((BYTE)strlen(Player->Name));//taille du nom
			NewPacket->WriteString(Player->Name,(int)strlen(Player->Name));
			NewPacket->WriteShort(Player->SkinID);	//	sexe/skin
			NewPacket->WriteShort(Player->Niveau);	//level
		}
	}
	else NewPacket->WriteByte(0x00);
	Client->SendPacket(NewPacket);
}