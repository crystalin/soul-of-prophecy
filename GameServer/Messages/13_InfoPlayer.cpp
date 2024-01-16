#include "stdafx.h"
#include "..\PacketManager.h"
#include "..\GameServer.h"
void PacketManager::Send_13_InfoPlayer(GameClient *Client,GamePlayer *Player)//on rajoutera les parametres necessaires s'il le faut
{
	GamePacketOut *NewPacket = new GamePacketOut(13);
	printf("Vie : %d ",((Player->HP_Max*100)/Player->Mana));
	Player->Dexterite=100;

	NewPacket->WriteByte(0x00);//Unknow
	NewPacket->WriteInt(Player->ID);// Player ID
	NewPacket->WriteShort(Player->X);
	NewPacket->WriteShort(Player->Y);
	NewPacket->WriteShort(Player->World);
	NewPacket->WriteInt(Player->HP);// HP
	NewPacket->WriteInt(Player->HP_Max);// Max HP
	NewPacket->WriteShort(Player->Mana);// Mana
	NewPacket->WriteShort(Player->Mana_Max);// Max Mana
	NewPacket->WriteInt64(Player->XP);//XP
	NewPacket->WriteInt64(Player->XP_Next_Level);//XP avant prochain lvl

	NewPacket->WriteShort(Player->Force);// Force
	NewPacket->WriteShort(0x1234);// Endurance
	NewPacket->WriteShort(Player->Dexterite);// Dexterité
	NewPacket->WriteShort(0x00);// Volonté (Inutil)
	NewPacket->WriteShort(Player->Sagesse);// Sagesse
	NewPacket->WriteShort(Player->Intelligence);// Intelligence
	NewPacket->WriteShort(0x00);// Chance (Inutil)

	NewPacket->WriteByte(0x10);// Seconde
	NewPacket->WriteByte(0x10);// Minute
	NewPacket->WriteByte(0x10);// Heure
	NewPacket->WriteByte(0x10);// Semaine
	NewPacket->WriteByte(0x10);// Jour
	NewPacket->WriteByte(0x10);// Mois
	NewPacket->WriteInt(0x00); // Année

	NewPacket->WriteInt(0x00);  // Or
	NewPacket->WriteShort(0x00);  // Niveau
	NewPacket->WriteInt64(Player->XP_In_Level);// XP du prochain niveau

	Client->SendPacket(NewPacket);
}