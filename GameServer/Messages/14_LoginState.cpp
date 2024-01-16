#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_14_LoginState(GameClient *Client,int State, char * Message)
{
	GamePacketOut *NewPacket = new GamePacketOut(14);
	NewPacket->WriteByte(State);
	NewPacket->WritePascalString(Message);

	Client->SendPacket(NewPacket);	
}