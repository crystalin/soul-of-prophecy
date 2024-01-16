#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_37_UpdateLevel(GameClient *Client, GamePlayer * Player)
{
	GamePacketOut *NewPacket = new GamePacketOut(37);
	__int64 XPAvLevel=1000;

	NewPacket->WriteShort(Player->Niveau);
	NewPacket->WriteInt64(XPAvLevel);
	NewPacket->WriteInt(Player->HP);
	NewPacket->WriteInt(Player->HP_Max);
	NewPacket->WriteShort(Player->Mana);
	NewPacket->WriteShort(Player->Mana_Max);

	Client->SendPacket(NewPacket);	

}