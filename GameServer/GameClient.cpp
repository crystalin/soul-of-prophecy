#include "StdAfx.h"
#define GAMGESERVERDLL_EXPORTS
#include ".\gameclient.h"

GameClient::GameClient(SOCKADDR_IN Address, int id, GameServer *p_GS)
{
	memcpy(&m_address,&Address,sizeof(Address));
	m_id=id;
	m_lastpakidsent=0;
	m_lastpakidreceived=(-1);
	m_lasttimesent=GetTickCount();
	m_lasttimereceived=GetTickCount();
	GS=p_GS;
	m_status=CS_WAITING_CONNECTION;
	Player = new GamePlayer(this);
}

GameClient::~GameClient(void)
{
	delete Player;
}

int GameClient::GetLastPacketIdSent()
{
	return m_lastpakidsent;
}

int GameClient::GetLastPacketIdReceived()
{
	return m_lastpakidreceived;
}

int GameClient::GetLastTimeSent()
{
	return m_lasttimesent;
}

int GameClient::GetLastTimeReceived()
{
	return m_lasttimereceived;
}


void GameClient::SendPacket(GamePacketOut *Packet)
{
	Packet->WritePacketID(++m_lastpakidsent);
	Packet->FinishPacket(this);
	GS->NS->SendPacket(Packet);
	m_lasttimesent=GetTickCount();
}

void GameClient::RespondACK(int packetid)
{
	AckPacketOut *AckPak = new AckPacketOut(packetid);
	AckPak->SetTargetClient(this);
	GS->NS->SendPacket(AckPak);
	m_lasttimesent=GetTickCount();
}

bool GameClient::OnRecv(GamePacketIn *Packet)
{
	if (Packet->GetID()!=m_lastpakidreceived+1)
		return false;
	else m_lastpakidreceived++;

	m_lasttimereceived=Packet->GetRecvTime();

	int Code = Packet->GetCode();
	if (Code == 14 && m_status == CS_WAITING_CONNECTION)
		m_status=CS_CONNECTED;
	return true;
}

int GameClient::GetStatus()
{
	return m_status;
}

void GameClient::Disconnected()
{
	printf("==>Client [%d] Disconnected\n",GetID());
	GS->RemoveUnit(Player);
	return;
}

void GameClient::ExitGame()
{
	GS->CM->RemoveClient(this);
	return;
}