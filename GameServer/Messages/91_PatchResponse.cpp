#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Send_91_PatchResponse(GameClient *Client,UINT ServerVersion, char * URL, char *Fichier, char*Login, char * Password,USHORT Inconnu)
{
	GamePacketOut *NewPacket = new GamePacketOut(91);
	NewPacket->WriteInt(ServerVersion);
	NewPacket->WritePascalString(URL);
	NewPacket->WritePascalString(Fichier);
	NewPacket->WritePascalString(Login);
	NewPacket->WritePascalString(Password);
	NewPacket->WriteShort(Inconnu);

	Client->SendPacket(NewPacket);	
}