#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_35_UnitName(GameClient *Client, GameUnit * Unit)
{
	GamePacketOut *NewPacket = new GamePacketOut(35);

	NewPacket->WriteInt(Unit->ID);
	NewPacket->WritePascalString(Unit->Name);
	

	Client->SendPacket(NewPacket);	

}