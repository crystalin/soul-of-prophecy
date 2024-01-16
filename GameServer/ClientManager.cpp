#include "StdAfx.h"
#include ".\clientmanager.h"
#include "GameClient.h"

ClientManager::ClientManager(GameServer *GS)
{
	m_clientslist = NULL;
	hThreadCM = NULL;
	m_GS=GS;
}

ClientManager::~ClientManager(void)
{
}

bool ClientManager::Start()
{
	Init();
	return true;
}

bool ClientManager::Pause()
{
	SuspendThread(hThreadCM);
	return true;
}

bool ClientManager::Resume()
{
	ResumeThread(hThreadCM);
	return true;
}

bool ClientManager::Stop()
{
	return UnInit();
}

bool ClientManager::Init()
{
	DWORD dThread1;
	m_clientslist = new ArrayList(GAMESERVER_MAX_CLIENTS);
	hThreadCM = CreateThread( NULL,
					0,
					(LPTHREAD_START_ROUTINE)GetCMLoopFunction,
					(LPVOID)this,
					0,
					&dThread1 );
	return true;
}

bool ClientManager::UnInit()
{
	TerminateThread(hThreadCM,0);
	delete m_clientslist;
	return true;
}

int ClientManager::MaxClients()
{
	return m_clientslist->MaxSize();
}

int ClientManager::Count()
{
	return m_clientslist->Count();
}

GameClient *ClientManager::GetClientByAddress(SOCKADDR_IN p_address)
{
	GameClient *Client;
	SOCKADDR_IN address;
	for (int i = 0 ; i<m_clientslist->Count();i++)
	{
		Client=(GameClient *)(m_clientslist->GetArray(i));
		address=Client->GetAddrSock();
		if (address.sin_addr.s_addr == p_address.sin_addr.s_addr && address.sin_port == p_address.sin_port)
			return Client;
	}
	return NULL;
}

GameClient *ClientManager::GetClientById(int p_id)
{
	GameClient *Client;
	int ClientId;
	for (int i = 0 ; i<m_clientslist->Count();i++)
	{
		Client=(GameClient *)(m_clientslist->GetArray(i));
		ClientId = Client->GetID();
		if (ClientId == p_id)
			return Client;
	}
	return NULL;
}

GameClient *ClientManager::CreateNewClient(SOCKADDR_IN address)
{
	GameClient *Client = new GameClient(address,CreateID(), m_GS);
	m_clientslist->Add(Client);
	return Client;
}

int ClientManager::CreateID()
{
	int id=m_clientslist->Count();
	while (GetClientById(id)!=NULL)
		id++;
	return id;
}
	
DWORD WINAPI ClientManager::ClientLoop()
{
	int CurrentTime;
	while (1)
	{
		Sleep(100);
		CurrentTime=GetTickCount();
		for (int i = 0 ; i< m_clientslist->Count();i++)
		{
			GameClient *Client = (GameClient*)m_clientslist->GetArray(i);
			if (Client->GetStatus() == CS_CONNECTED &&(CurrentTime-Client->GetLastTimeReceived() > CM_LINK_DEAD_TIME ))
			{
				RemoveClient(Client);
			}
			else if (Client->GetStatus() == CS_WAITING_CONNECTION && (CurrentTime-Client->GetLastTimeReceived() > CM_WAITING_CLIENT ))
			{
				RemoveClient(Client);
			}
			else if (Client->GetStatus() == CS_CONNECTED && (CurrentTime-Client->GetLastTimeSent()) > CM_KEEPALIVE_TIME)
			{
				m_GS->PM->Send_10_KeepAlive(Client);
			}
		}	
	}
}

void ClientManager::RemoveClient(GameClient *Client)
{
	Client->Disconnected();
	m_clientslist->Remove(Client);
	delete Client;
}