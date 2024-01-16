#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_46_FromPreInGameToInGame(GameClient *Client,ArrayList *Units)
{
	GamePacketOut *NewPacket = new GamePacketOut(46);
	NewPacket->WriteByte(Units==NULL);

	if (Units!=NULL)//si il y a des units a afficher
	{
		NewPacket->WriteShort(Units->Count());
		for(int i=0 ; i < Units->Count() ; i ++)
		{
			GameUnit *Unit=(GameUnit *)Units->GetArray(i);
			NewPacket->WriteShort(0x00);//inconnu
			NewPacket->WriteShort(Unit->X);
			NewPacket->WriteShort(Unit->Y);
			NewPacket->WriteShort(Unit->SkinID);
			NewPacket->WriteInt(Unit->ID);
			NewPacket->WriteByte((BYTE)0x30); // Lumiere
			NewPacket->WriteByte((BYTE)Unit->UnitType);
			NewPacket->WriteByte((BYTE)((Unit->HP_Max*100) / Unit->HP));
		}
	
	}

	Client->SendPacket(NewPacket);	
}