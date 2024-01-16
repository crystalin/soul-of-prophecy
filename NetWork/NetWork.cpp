// NetWork.cpp : définit le point d'entrée pour l'application DLL.
//

#include "stdafx.h"
#define NETWORKDLL_EXPORTS
#include "NetWork.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
NetServer::NetServer()
{
	hThreadReceive = INVALID_HANDLE_VALUE;
	hThreadAnalyse	= INVALID_HANDLE_VALUE;
	hThreadSend = INVALID_HANDLE_VALUE;
	port = 0;
}

NetServer::~NetServer()
{
}

bool NetServer::Start()
{
	Init();
	return true;
}

bool NetServer::Pause()
{
	SuspendThread(hThreadReceive);
	SuspendThread(hThreadAnalyse);
	SuspendThread(hThreadSend);
	return true;
}

bool NetServer::Resume()
{
	ResumeThread(hThreadReceive);
	ResumeThread(hThreadAnalyse);
	ResumeThread(hThreadSend);
	return true;
}

bool NetServer::Stop()
{
	return UnInit();
}

bool NetServer::Init()
{
	port = 11677;

	InPacketList = new QueueList();
	DecodedPacketList = new QueueList();
	PacketToSendList = new QueueList();

	InPacketList->GetNext();

	WSADATA wsa;
	WSAStartup(MAKEWORD(2,0),&wsa);

	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=INADDR_ANY;
	sin.sin_port=htons(port);
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if (bind(sock,(SOCKADDR*)&sin,sizeof(sin))==SOCKET_ERROR)
		return false;

	hThreadReceive =(HANDLE) _beginthread((void (__cdecl *)(void *))GetRcvFunction,0,(LPVOID)this);
	hThreadAnalyse =(HANDLE) _beginthread((void (__cdecl *)(void *))GetAnalyseFunction,0,(LPVOID)this);
	hThreadSend =(HANDLE) _beginthread((void (__cdecl *)(void *))GetSendFunction,0,(LPVOID)this);
	
	return true;
}

bool NetServer::UnInit()
{
	TerminateThread(hThreadReceive,0);
	TerminateThread(hThreadAnalyse,0);
	TerminateThread(hThreadSend,0);

	delete InPacketList;
	delete DecodedPacketList;
	delete PacketToSendList;

	closesocket(sock);
	WSACleanup();
	return true;
}



DWORD NetServer::ReceiveLoop()
{
	printf("Receive Loop Started! \n");
	SOCKADDR_IN client;
	char buffer[PACKETIN_MAX_SIZE];
	int sinsize=sizeof(sin);
	GamePacketIn *NewPacket;
	while(1)
	{
		memset(buffer,0,sizeof(buffer));
		int len=recvfrom(sock,buffer,sizeof(buffer),0,(SOCKADDR*)&client,&sinsize);
		if (len==SOCKET_ERROR && (WSAGetLastError()!=10054))
		{
			printf("Socket Error %d !!\n",WSAGetLastError());
			Stop();
		}
		else if ((WSAGetLastError()!=10054))
		{
			NewPacket=new GamePacketIn(buffer,len,client);
			InPacketList->Add(NewPacket);
		}
		
	}
	return 0;
}

DWORD NetServer::AnalyseLoop()
{
	printf("Analyse Loop Started! \n");
	GamePacketIn *NewPacket=NULL;
	while(1)
	{
		Sleep(10);
		NewPacket=(GamePacketIn *)InPacketList->GetNext();
		while (NewPacket!=NULL)
		{
			//printf("==> Packet Recv [%d] : size [%d] : address [%s:%d] : ACK [%s]\n",NewPacket->GetID(),NewPacket->GetLen(),inet_ntoa(NewPacket->GetAddress().sin_addr),ntohs(NewPacket->GetAddress().sin_port),(NewPacket->IsAckRequest())?"Oui":"Non");
			/*printf("Message: %s      ACK: %s\n",NewPacket->IsMessage()?"Oui":"Non",NewPacket->IsAckRequest()?"Oui":"Non");
			printf("Addresse: %s\n",inet_ntoa(NewPacket->GetAddress().sin_addr));*/
			if (NewPacket->IsMessage()){}
				NewPacket->Decode();
			NewPacket->Log();
			DecodedPacketList->Add(NewPacket);
			NewPacket=(GamePacketIn *)InPacketList->GetNext();
		}

	}
	return 0;
}

DWORD NetServer::SendLoop()
{
	printf("Send Loop Started! \n");
	PacketOut *NewPacket=NULL;
	while(1)
	{
		Sleep(10);
		NewPacket=(PacketOut *)PacketToSendList->GetNext();
		while (NewPacket!=NULL)
		{
			sendto(sock,NewPacket->GetBuffer(),NewPacket->GetLen(),0,(const sockaddr *)&NewPacket->GetSockAddr(),sizeof(SOCKADDR_IN));
			//printf("==> Packet Sent [%d]: size [%d] : address [%s]\n",((GamePacketOut *)NewPacket)->GetID(),NewPacket->GetLen(),inet_ntoa(NewPacket->GetSockAddr().sin_addr));
			//NewPacket->Log();
			delete NewPacket;
			NewPacket=(PacketOut *)PacketToSendList->GetNext();
		}

	}
	return 0;
}

GamePacketIn *NetServer::GetNextDecodedPacket()
{
	return (GamePacketIn *)DecodedPacketList->GetNext();
}

void NetServer::SendPacket(PacketOut *Packet)
{
	PacketToSendList->Add(Packet);
}
