#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_104_PopupUnit(GameClient *Client,GameUnit * Unit)
{
	GamePacketOut *NewPacket = new GamePacketOut(10004);


	NewPacket->WriteShort(Unit->X);
	NewPacket->WriteShort(Unit->Y);
	NewPacket->WriteShort(Unit->SkinID);
	NewPacket->WriteInt(Unit->ID);
	NewPacket->WriteByte(0x00);//Unit->Halo);
	NewPacket->WriteByte(Unit->UnitType);
	NewPacket->WriteByte((BYTE)((Unit->HP_Max*100) / Unit->HP));//santé

	Client->SendPacket(NewPacket);	

}