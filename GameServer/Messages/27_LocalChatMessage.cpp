#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_27_LocalChatMessage(GameClient *Client, GameUnit *Unit, char *message)
{
	GamePacketOut *NewPacket = new GamePacketOut(27);

	NewPacket->WriteInt(Unit->ID);
	NewPacket->WriteByte(0x00);//Direction
	NewPacket->WriteInt(0x00);//Couleur ( UseLess ?? )
	if (Unit->UnitType==GU_UNITTYPE_PLAYER)
		NewPacket->WriteByte(0);
	else NewPacket->WriteByte(1);

	NewPacket->WritePascalString(message);
	NewPacket->WritePascalString(Unit->Name);

	Client->SendPacket(NewPacket);	

}