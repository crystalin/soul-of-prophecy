#include "stdafx.h"
#include "..\PacketManager.h"
void PacketManager::Run_91_PatchRequest(GameClient *Client, GamePacketIn *InPak)
{
	Send_91_PatchResponse(Client,125,"www.SoP.com","/webpatch/patch.img","Login","Pass",0);
}