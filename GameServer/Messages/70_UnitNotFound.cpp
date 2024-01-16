#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_70_UnitNotFound(GameClient *Client,int IDUnit)
{
	GamePacketOut *NewPacket = new GamePacketOut(70);
	USHORT Code=0x00;

	NewPacket->WriteInt(IDUnit);
	NewPacket->WriteShort(Code);//Code du packet (oui oui le Code) qui a demandé l'info

	Client->SendPacket(NewPacket);	

}