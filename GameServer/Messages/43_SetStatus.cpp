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
	NewPacket->WriteShort((short)(Player->AF+2)); // AF Boosté
	NewPacket->WriteShort((short)(Player->AF));
	NewPacket->WriteShort((short)(Player->Force+2));// Force Boosté
	NewPacket->WriteShort((short)(Player->Endurance+2));// Endurance Boosté
	NewPacket->WriteShort((short)(Player->Dexterite+2));// Dexterité Boosté
	NewPacket->WriteShort(0x00);// Volonté Boostée Useless
	NewPacket->WriteShort((short)(Player->Sagesse+2));// Sagesse Boosté
	NewPacket->WriteShort((short)(Player->Intelligence+2));// Intelligence Boosté
	NewPacket->WriteShort(0x00);// Chance Boostée Useless
	NewPacket->WriteShort((short)(Player->Stats_Points));
	NewPacket->WriteShort((short)(Player->Force));
	NewPacket->WriteShort((short)(Player->Endurance));
	NewPacket->WriteShort((short)(Player->Dexterite));
	NewPacket->WriteShort(0x00);// Volonté Useless
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