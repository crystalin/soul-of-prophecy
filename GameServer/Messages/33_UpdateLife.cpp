#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_33_UpdateLife(GameClient *Client, GamePlayer * Player)
{
	GamePacketOut *NewPacket = new GamePacketOut(33);

	printf("<===== HP : %d/%d ======>",Player->HP,Player->HP_Max);

	NewPacket->WriteInt(Player->HP);
	NewPacket->WriteInt(Player->HP_Max);
	

	Client->SendPacket(NewPacket);	

}