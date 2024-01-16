#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_62_SpellList(GameClient *Client)
{
	GamePacketOut *NewPacket = new GamePacketOut(62);
	USHORT NbSpells=1;
	USHORT PM=500;
	USHORT PMMax=500;
	USHORT ID=0x00;
	BYTE Cible=11; //5=self 11=monstres
	USHORT PM2=10;//pts de mana consommés par le spell
	USHORT Inconnu=0x00;
	USHORT Icon=5;//l'icone du spell
	/********************************************************************/

	NewPacket->WriteByte(0x00);//inconnu
	NewPacket->WriteShort(PM);
	NewPacket->WriteShort(PMMax);
	NewPacket->WriteShort(NbSpells);

	for (USHORT i=0;i<NbSpells;i++)
	{
		NewPacket->WriteByte(Cible);
		NewPacket->WriteShort(ID);
		NewPacket->WriteShort(PM2);
		NewPacket->WriteShort(Inconnu);
		NewPacket->WriteShort(Inconnu);
		NewPacket->WriteShort(Inconnu);
		NewPacket->WriteShort(Inconnu);
		NewPacket->WriteShort(Inconnu);
		NewPacket->WriteShort(Inconnu);
		NewPacket->WriteShort(Icon);
		NewPacket->WritePascalString("Description");
		NewPacket->WritePascalString("Nom du sort");
		
	}



	Client->SendPacket(NewPacket);	
}