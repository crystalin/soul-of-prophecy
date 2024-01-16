#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_19_EquipedItems(GameClient *Client)
{
	GamePacketOut *NewPacket = new GamePacketOut(19);
	int IDUnitItem=0;
	USHORT Icon=3;
	USHORT ItemID=0;
	USHORT NbItems=1;


	NewPacket->WriteByte(0x00);//inconnu
	for (USHORT i=0;i<13;i++)
	{

		/*<case value="0">Armure</case> 
  <case value="1">Gants</case> 
  <case value="2">Casque</case> 
  <case value="3">Jambieres</case> 
  <case value="4">Bracelet</case> 
  <case value="5">Collier</case> 
  <case value="6">Main droite (Arme)</case> 
  <case value="7">Main gauche (Bouclier/Fleches)</case> 
  <case value="8">Anneau 1</case> 
  <case value="9">Anneau 2</case> 
  <case value="10">Ceinture</case> 
  <case value="11">Cape</case> 
  <case value="12">Bottes</case> 
*/
		NewPacket->WriteInt(IDUnitItem);
		NewPacket->WriteShort(Icon);
		NewPacket->WriteShort(ItemID);
		NewPacket->WriteShort(NbItems);
		NewPacket->WriteInt(0x00);//inconnu
		NewPacket->WritePascalString("Nom de l'objet");
	}
	

	Client->SendPacket(NewPacket);	

}