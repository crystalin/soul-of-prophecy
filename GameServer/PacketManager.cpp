#include "StdAfx.h"
#include ".\PacketManager.h"


PacketManager::PacketManager(GameServer *GS)
{
	memset(m_InList,0,sizeof(m_InList));
	m_GS=GS;
}

PacketManager::~PacketManager(void)
{
}

void PacketManager::Init(void)
{
	//printf("Init PM\n");
	AddMethod(1,Run_01_PlayerMoveN,"Player Movement (North)");
	AddMethod(2,Run_02_PlayerMoveNE,"Player Movement (North-East)");
	AddMethod(3,Run_03_PlayerMoveE,"Player Movement (East)");
	AddMethod(4,Run_04_PlayerMoveSE,"Player Movement (South-East)");
	AddMethod(5,Run_05_PlayerMoveS,"Player Movement (South)");
	AddMethod(6,Run_06_PlayerMoveSW,"Player Movement (South-West)");
	AddMethod(7,Run_07_PlayerMoveW,"Player Movement (West)");
	AddMethod(8,Run_08_PlayerMoveNW,"Player Movement (North-West)");

	AddMethod(66,Run_66_Connection);
	AddMethod(91,Run_91_PatchRequest);
	AddMethod(14,Run_14_LoginState);
	AddMethod(99,Run_99_ServerVersion);
	AddMethod(10,Run_10_KeepAlive);
	AddMethod(89,Run_89_ToggleMenu);
	AddMethod(26,Run_26_PersonnalPCList);
	AddMethod(20,Run_20_ExitGame);
	AddMethod(39,Run_39_InfoSkills);
	AddMethod(62,Run_62_SpellList);
	AddMethod(13,Run_13_InfoPlayer);
	AddMethod(60,Run_60_GetNearItems);
	AddMethod(46,Run_46_FromPreInGameToInGame);
	AddMethod(68,Run_68_PuppetInformation);
	AddMethod(43,Run_43_GetStatus);
	AddMethod(27,Run_27_IndirectTalk);
	AddMethod(28,Run_28_Shout);
}

void PacketManager::UnInit(void)
{
	memset(m_InList,0,sizeof(m_InList));
}

void PacketManager::AddMethod(int Code,PakMethod Function,char* Description)
{
	char *desc = "No Description";
	if (Description != NULL)
		desc = Description;

	if (Code>10000)
		Code-=9900;
	m_InList[Code]=Function;

	printf("Added Fonction %d : %X \t%s\n",Code,(int)(m_InList[Code]),desc);

}

void PacketManager::RunPacketIn(GameClient *Client, GamePacketIn *InPak)
{
	if (!Client->OnRecv(InPak))
		return;
	if (InPak->IsAckRequest() && Client!=NULL)
		Client->RespondACK(InPak->GetID());

	int code =(unsigned short) InPak->GetCode();
	PakMethod *CodeFunction=NULL;
	if (code >10000)
		code = code-9900;
	if (code>0 && code < 200)CodeFunction=m_InList[code];

	printf("Code Recu : \t%04X",code);
	if (CodeFunction==NULL)
		RunDefault(Client,InPak,code);
	else CodeFunction(Client,InPak);

	delete InPak;
}

void PacketManager::RunDefault(GameClient *Client, GamePacketIn *InPak, int code)
{
	printf("Unknow Packet [Code: %d, Client: %d]\n",code,Client==NULL?0:Client->GetID());
}


