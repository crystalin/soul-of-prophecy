#pragma once
//#include ".\GameServerHeader.h"
#include ".\GameServer.h"
#include ".\GameClient.h"

#define CM_KEEPALIVE_TIME	1000
#define CM_WAITING_CLIENT	300000
#define CM_LINK_DEAD_TIME	10000

class ClientManager
{
public:
	ClientManager(GameServer *GS);
	~ClientManager(void);

	bool Start();
	bool Pause();
	bool Resume();
	bool Stop();

	bool Init();
	bool UnInit();

	int MaxClients();
	int Count();

	GameClient	*GetClientByAddress(SOCKADDR_IN address);
	GameClient	*GetClientById(int id);

	GameClient	*CreateNewClient(SOCKADDR_IN address);
	void		RemoveClient(GameClient *Client);


private:

	DWORD WINAPI	ClientLoop();
	int				CreateID();

	HANDLE			hThreadCM;
	ArrayList		*m_clientslist;
	GameServer		*m_GS;

	static DWORD CALLBACK GetCMLoopFunction(LPVOID lpParameter)
	{
		return ((ClientManager*)lpParameter)->ClientLoop();
	}

};
