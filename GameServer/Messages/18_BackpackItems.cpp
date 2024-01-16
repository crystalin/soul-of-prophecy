#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_18_BackpackItems(GameClient *Client)
{
	GamePacketOut *NewPacket = new GamePacketOut(18);
	USHORT NbItems=1;
	int NbItems2=1;
	USHORT Icon=5;
	USHORT UnitID=0;
	USHORT ItemID=126;

	NewPacket->WriteByte(0x00);//inconnu
	NewPacket->WriteInt(Client->Player->ID);
	NewPacket->WriteShort(NbItems);

	for (USHORT i=0;i<NbItems;i++)
	{
		NewPacket->WriteShort(Icon);
		NewPacket->WriteInt(UnitID);
		NewPacket->WriteShort(ItemID);
		NewPacket->WriteInt(NbItems2);
		NewPacket->WriteInt(0x00);//inconnu
	}

	Client->SendPacket(NewPacket);	

}