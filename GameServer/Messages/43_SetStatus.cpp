#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_43_SetStatus(GameClient *Client,GamePlayer *Player)
{
	GamePacketOut *NewPacket = new GamePacketOut(43);

	NewPacket->WriteInt(Player->HP);
	NewPacket->WriteInt(Player->HP_Max);
	NewPacket->WriteShort((short)Player->Mana);
	NewPacket->WriteShort((short)Player->Mana_Max);
	NewPacket->WriteInt64(Player->XP);
	NewPacket->WriteShort((short)(Player->AF+2)); // AF Boost�
	NewPacket->WriteShort((short)(Player->AF));
	NewPacket->WriteShort((short)(Player->Force+2));// Force Boost�
	NewPacket->WriteShort((short)(Player->Endurance+2));// Endurance Boost�
	NewPacket->WriteShort((short)(Player->Dexterite+2));// Dexterit� Boost�
	NewPacket->WriteShort(0x00);// Volont� Boost�e Useless
	NewPacket->WriteShort((short)(Player->Sagesse+2));// Sagesse Boost�
	NewPacket->WriteShort((short)(Player->Intelligence+2));// Intelligence Boost�
	NewPacket->WriteShort(0x00);// Chance Boost�e Useless
	NewPacket->WriteShort((short)(Player->Stats_Points));
	NewPacket->WriteShort((short)(Player->Force));
	NewPacket->WriteShort((short)(Player->Endurance));
	NewPacket->WriteShort((short)(Player->Dexterite));
	NewPacket->WriteShort(0x00);// Volont� Useless
	NewPacket->WriteShort((short)(Player->Sagesse));
	NewPacket->WriteShort((short)(Player->Intelligence));
	NewPacket->WriteShort(0x00);// Chance Useless
	NewPacket->WriteShort((short)(Player->Niveau));
	NewPacket->WriteShort((short)(Player->Skill_Points));
	NewPacket->WriteShort((short)(Player->Encombrement));
	NewPacket->WriteShort((short)(Player->Encombrement_Max));
	NewPacket->WriteShort((short)(Player->Karma));
	NewPacket->WriteShort((short)(Player->HP-10));

	Client->SendPacket(NewPacket);	
}