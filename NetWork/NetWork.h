#pragma once
#define NETWORKDLL_EXPORTS 

#include <process.h>
#include "NetHeader.h"

class NETWORKDLL_API NetServer // Network Server
{
public:
	NetServer();
	~NetServer();
    bool			Start();
	bool			Pause();
	bool			Resume();
	bool			Stop();
	GamePacketIn	*GetNextDecodedPacket();
	void			SendPacket(PacketOut *Packet);

private:
	HANDLE		hThreadReceive;
	HANDLE		hThreadAnalyse;
	HANDLE		hThreadSend;
	int			port;
	SOCKET		sock;
	SOCKADDR_IN	sin;
	QueueList	*InPacketList;
	QueueList	*DecodedPacketList;
	QueueList	*PacketToSendList;

	bool		Init();
	bool		UnInit();

	DWORD		ReceiveLoop();
	DWORD		AnalyseLoop();
	DWORD		SendLoop();

	static DWORD CALLBACK GetRcvFunction(LPVOID lpParameter)
	{
		return ((NetServer*)lpParameter)->ReceiveLoop();
	}
	static DWORD CALLBACK GetAnalyseFunction(LPVOID lpParameter)
	{
		return ((NetServer*)lpParameter)->AnalyseLoop();
	}
	static DWORD CALLBACK GetSendFunction(LPVOID lpParameter)
	{
		return ((NetServer*)lpParameter)->SendLoop();
	}

};