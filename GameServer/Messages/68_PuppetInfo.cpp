#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_68_PuppetInfo(GameClient *Client,GameUnit *Unit)
{
	GamePacketOut *NewPacket = new GamePacketOut(68);
	NewPacket->WriteInt(Unit->ID);
	NewPacket->WriteShort(0x01A9); // veste/robe
	NewPacket->WriteShort(0x0104); // bottes
	NewPacket->WriteShort(0x00); // gants
	NewPacket->WriteShort(0x00); // casque
	NewPacket->WriteShort(0x00); // pantalon
	NewPacket->WriteShort(0x0127); // arme
	NewPacket->WriteShort(0x00); // bouclier
	NewPacket->WriteShort(0x00); // cape
	Client->SendPacket(NewPacket);	
} 