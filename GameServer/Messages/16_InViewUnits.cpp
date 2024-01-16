#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_16_InViewUnits(GameClient *Client,ArrayList *Units)
{
	GamePacketOut *NewPacket = new GamePacketOut(16);
	NewPacket->WriteShort(Units->Count());
	for(int i=0 ; i < Units->Count() ; i ++)
	{
		GameUnit *Unit=(GameUnit *)Units->GetArray(i);
		NewPacket->WriteShort(Unit->X);
		NewPacket->WriteShort(Unit->Y);
		NewPacket->WriteShort(Unit->SkinID);
		NewPacket->WriteInt(Unit->ID);
		NewPacket->WriteByte((BYTE)0x30); // Lumiere
		NewPacket->WriteByte((BYTE)Unit->UnitType);
		NewPacket->WriteByte((BYTE)((Unit->HP_Max*100) / Unit->HP));
	}
	Client->SendPacket(NewPacket);	
}