#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_29_PagerMessage(GameClient *Client)
{
	GamePacketOut *NewPacket = new GamePacketOut(29);

	NewPacket->WritePascalString("Message à envoyer !");
	NewPacket->WritePascalString("Emetteur");
	

	Client->SendPacket(NewPacket);	

}