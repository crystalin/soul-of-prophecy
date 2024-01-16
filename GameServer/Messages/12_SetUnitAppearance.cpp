#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_12_SetUnitAppearance(GameClient *Client,GameUnit *Unit)
{
	GamePacketOut *NewPacket = new GamePacketOut(12);
	NewPacket->WriteInt(Unit->SkinID);
	NewPacket->WriteInt(Unit->ID);
	Client->SendPacket(NewPacket);
}