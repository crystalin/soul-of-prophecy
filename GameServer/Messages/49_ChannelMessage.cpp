#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_49_ChannelMessage(GameClient *Client, GameUnit *Unit, char *message, char *Channel)
{
	GamePacketOut *NewPacket = new GamePacketOut(49);

	NewPacket->WritePascalString(Channel);
	NewPacket->WritePascalString(Unit->Name);
	NewPacket->WritePascalString(message);

	Client->SendPacket(NewPacket);	

}