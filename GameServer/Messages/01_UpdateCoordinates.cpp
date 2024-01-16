#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_01_UpdateCoordinates(GameClient *Client,GameUnit *Unit)
{
	GamePacketOut *NewPacket = new GamePacketOut(01);
	NewPacket->WriteShort(Unit->X);
	NewPacket->WriteShort(Unit->Y);
	NewPacket->WriteShort(Unit->SkinID);
	NewPacket->WriteInt(Unit->ID);
	NewPacket->WriteByte((BYTE)0x30); // Lumiere
	NewPacket->WriteByte((BYTE)Unit->UnitType);
	NewPacket->WriteByte((BYTE)((Unit->HP_Max*100) / Unit->HP));
	Client->SendPacket(NewPacket);
}