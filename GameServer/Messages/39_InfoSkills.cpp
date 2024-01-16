#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_39_InfoSkills(GameClient *Client)
{

	GamePacketOut *NewPacket = new GamePacketOut(39);
	USHORT NbSkills=1;
	USHORT Points=5;
	USHORT Boost=0;
	USHORT ID=0x00;

	NewPacket->WriteShort(NbSkills);

	for (USHORT i=0;i<NbSkills;i++)
	{
		NewPacket->WriteShort(ID);
		NewPacket->WriteByte(0x00);//inconnu
		NewPacket->WriteShort(Points);//je c pas trop de quel point il parle
		NewPacket->WriteShort(Boost);//pareil
		NewPacket->WritePascalString("Nom de la compétence");
		NewPacket->WritePascalString("Description");
	}



	Client->SendPacket(NewPacket);	
}