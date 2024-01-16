#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_31_ReRollDices(GameClient *Client)
{
	GamePacketOut *NewPacket = new GamePacketOut(31);
	BYTE Dext=25;
	BYTE Endu=25;
	BYTE Inte=25;
	BYTE Chance=25;
	BYTE Force=25;
	BYTE Volonte=25;
	BYTE Sagesse=25;
	int PV=50;
	int PVMax=50;
	USHORT PM=50;
	USHORT PMMax=50;

	NewPacket->WriteByte(0x00);//inconnu
	NewPacket->WriteByte(Dext);
	NewPacket->WriteByte(Endu);
	NewPacket->WriteByte(Inte);
	NewPacket->WriteByte(Chance);
	NewPacket->WriteByte(Force);
	NewPacket->WriteByte(Volonte);
	NewPacket->WriteByte(Sagesse);
	NewPacket->WriteInt(PV);
	NewPacket->WriteInt(PVMax);
	NewPacket->WriteShort(PM);
	NewPacket->WriteShort(PMMax);


	Client->SendPacket(NewPacket);	

}