#pragma once
#define GAMGESERVERDLL_EXPORTS
#include ".\GameServerHeader.h"
#include ".\GameObjects\GameNPC.h"
#include ".\GameObjects\GamePlayer.h"
#include ".\GameObjects\GameLiving.h"
#include ".\GameObjects\GameUnit.h"

typedef void (__stdcall PakMethod)(GameClient *Client,GamePacketIn *InPak);

class PacketManager
{
public:
	PacketManager(GameServer *GS);
	~PacketManager(void);

	void RunPacketIn(GameClient *Client, GamePacketIn *InPak);
	void Init();
	void UnInit();

	//====================Packet Send Functions============================//
	static void Send_66_MOTD(GameClient *Client,char *Message);
	static void Send_91_PatchResponse(GameClient *Client,UINT ServerVersion,char * URL, char *Fichier, char*Login, char * Password,USHORT Inconnu);
	static void Send_99_ServerVersion(GameClient *Client,UINT Response);
	static void Send_26_PersonnalPCList(GameClient *Client,ArrayList *Players);
	static void Send_01_UpdateCoordinates(GameClient *Client,GameUnit *Unit);
	static void Send_09_SynchronizePlayerCoordinates(GameClient *Client);
	static void Send_11_RemoveUnit(GameClient *Client,GameUnit *Unit);
	static void Send_12_SetUnitAppearance(GameClient *Client,GameUnit *Unit);
	static void Send_13_InfoPlayer(GameClient *Client,GamePlayer *Player);
	static void Send_14_LoginState(GameClient *Client,int State, char * Message);
	static void Send_15_DeletePlayer(GameClient *Client,int IsDelete);
	static void Send_16_InViewUnits(GameClient *Client,ArrayList *Units);
	static void Send_39_InfoSkills(GameClient *Client);
	static void Send_62_SpellList(GameClient *Client);
	static void Send_46_FromPreInGameToInGame(GameClient *Client,ArrayList *Units);
	static void Send_10_KeepAlive(GameClient *Client);
	static void Send_69_UnitAppearance(GameClient *Client,GameUnit * Unit);
	static void Send_70_UnitNotFound(GameClient *Client,int IDUnit);
	static void Send_104_PopupUnit(GameClient *Client,GameUnit * Unit);
	static void Send_18_BackpackItems(GameClient *Client);
	static void Send_19_EquipedItems(GameClient *Client);
	static void Send_20_ServerShutdown(GameClient *Client);
	static void Send_25_RollDices(GameClient *Client);
	static void Send_31_ReRollDices(GameClient *Client);
	static void Send_27_LocalChatMessage(GameClient *Client, GameUnit *Unit, char *Message);
	static void Send_29_PagerMessage(GameClient *Client);
	static void Send_33_UpdateLife(GameClient *Client, GamePlayer * Player);
	static void Send_35_UnitName(GameClient *Client, GameUnit * Unit);
	static void Send_37_UpdateLevel(GameClient *Client, GamePlayer * Player);
	static void Send_68_PuppetInfo(GameClient *Client,GameUnit *Unit);
	static void Send_43_SetStatus(GameClient *Client,GamePlayer *Player);
	static void Send_49_ChannelMessage(GameClient *Client, GameUnit *Unit, char *message, char *Channel);

private:

	GameServer	*m_GS;

	PakMethod *m_InList[200];
	PakMethod *m_OutList[200];

	void AddMethod(int Code,PakMethod Function,char* Description = NULL);

	//====================Packet Receive Fonctions=========================//
	static void __stdcall RunDefault(GameClient *Client, GamePacketIn *InPak, int code);
	static void __stdcall Run_66_Connection(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_91_PatchRequest(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_14_LoginState(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_99_ServerVersion(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_10_KeepAlive(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_89_ToggleMenu(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_26_PersonnalPCList(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_20_ExitGame(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_39_InfoSkills(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_62_SpellList(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_13_InfoPlayer(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_60_GetNearItems(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_46_FromPreInGameToInGame(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_01_PlayerMoveN(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_02_PlayerMoveNE(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_03_PlayerMoveE(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_04_PlayerMoveSE(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_05_PlayerMoveS(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_06_PlayerMoveSW(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_07_PlayerMoveW(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_08_PlayerMoveNW(GameClient *Client,GamePacketIn *InPak);
	static void __stdcall Run_68_PuppetInformation(GameClient *Client, GamePacketIn *InPak);
	static void __stdcall Run_43_GetStatus(GameClient *Client, GamePacketIn *InPak);
	static void __stdcall Run_27_IndirectTalk(GameClient *Client, GamePacketIn *InPak);
	static void __stdcall Run_28_Shout(GameClient *Client, GamePacketIn *InPak);

};
