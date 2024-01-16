#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_69_UnitAppearance(GameClient *Client,GameUnit * Unit)
{
	GamePacketOut *NewPacket = new GamePacketOut(69);

	NewPacket->WriteShort(Unit->SkinID);
	NewPacket->WriteInt(Unit->ID);
	NewPacket->WriteByte(0x00);//Unit->Halo);
	NewPacket->WriteByte(Unit->UnitType);
	NewPacket->WriteByte((BYTE)((Unit->HP_Max*100) / Unit->HP));//santé
	Client->SendPacket(NewPacket);	
}