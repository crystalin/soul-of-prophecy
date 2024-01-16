#pragma once
#include "GameServerHeader.h"
#include ".\GameObjects\GamePlayer.h"

#define  CS_NOT_CONNECTED		0
#define  CS_WAITING_CONNECTION	1
#define  CS_CONNECTED			2
#define  CS_INGAME				3

class GameClient : public ClientBase
{
public:
	GameClient(SOCKADDR_IN address,int id, GameServer *GS);
	~GameClient(void);

	void RespondACK(int packetid);
	void SendPacket(GamePacketOut *Packet);

	int	GetLastPacketIdSent();
	int	GetLastPacketIdReceived();

	int	GetLastTimeSent();
	int	GetLastTimeReceived();

	bool OnRecv(GamePacketIn *Packet);

	int GetStatus();

	void ExitGame();
	void Disconnected();

	GamePlayer *Player;
	GameServer *GS;


protected:

	int	m_status;

	int m_lastpakidsent;
	int m_lasttimesent;
	int m_lastpakidreceived;
	int m_lasttimereceived;
};
