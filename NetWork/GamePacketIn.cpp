#include "StdAfx.h"
#include ".\gamepacketin.h"

GamePacketIn::GamePacketIn(char *buff, int len, SOCKADDR_IN address)
{
	m_recvtime = GetTickCount();
	if (len<=4096)
	{
		m_len=len;
		memcpy(m_buff,buff,len);
	}
	else
	{
		m_len=4096;
		memcpy(m_buff,buff,4096);
	}
	m_offset=0;
	m_address=address;

	if (m_len <12)
		return;
	m_pakfragnum=ReadByte();
	m_paktype=ReadByte();
	Skip(2);
	m_pakid=ReadInversedInt();
	m_pakmasterid=ReadInversedInt();

	if ((m_paktype&PACKET_TYPE_ACK_RESPONSE)==PACKET_TYPE_ACK_RESPONSE)
	{
		m_cryptvalue=0;
		m_datachecksum=0;
		m_code=0;
		return;
	}
	if (m_len <16)
		return;
	m_cryptvalue=ReadShortLowEndian();
	m_datachecksum=ReadShortLowEndian();
}

GamePacketIn::~GamePacketIn(void)
{
}

bool GamePacketIn::VerifyChecksum()
{
	return true;
}

void GamePacketIn::Decode()
{		
	unsigned short ushCleeTmp=m_cryptvalue;
	
	for (int i=16; i<m_len; i++)
	{
		ushCleeTmp=(ushCleeTmp*PACKET_CRYPT_KEY)+1;
		m_buff[i] ^= ushCleeTmp;
	}
	m_code=ReadShort();
}

bool GamePacketIn::IsAckReponse()
{
	return ((m_paktype&PACKET_TYPE_ACK_RESPONSE)==PACKET_TYPE_ACK_RESPONSE);
}

bool GamePacketIn::IsAckRequest()
{
	return ((m_paktype&PACKET_FLAG_ACK_REQUEST)==PACKET_FLAG_ACK_REQUEST);
}
bool GamePacketIn::IsMessage()
{
	return !((m_paktype&PACKET_TYPE_ACK_RESPONSE)==PACKET_TYPE_ACK_RESPONSE);
}

int GamePacketIn::GetID()
{
	return m_pakid;
}

int GamePacketIn::GetRecvTime()
{
	return m_recvtime;
}

short GamePacketIn::GetCode()
{
	return m_code;
}

int GamePacketIn::GetMasterID()
{
	return m_pakmasterid;
}

int GamePacketIn::GetMessageLen()
{
	if (m_len>16)
		return (m_len-16);
	return 0;
}

int GamePacketIn::GetType()
{
	return m_paktype;
}

void GamePacketIn::Log(void)
  {
		printf("=====PACKET=Inc=\n");

	printf("Size : %03d , Code : %03d\n",m_len,m_buff[17]);
	
	char hextext[100]="";
	char text[50]="";
	char tmptxt[4];

	int curChar=0;
	for(int i=0;i<m_len;i++)
	{
		wsprintf(tmptxt,"%02X ",(unsigned __int8) m_buff[i]);
		lstrcat(hextext,tmptxt);
		if(m_buff[i]>=32)	text[curChar]=m_buff[i];
		else				text[curChar]='.';

		curChar++;
		if(curChar==16) {
			text[curChar]=0;
			lstrcat(text,"\r\n");
			lstrcat(hextext,"  ");
			printf(hextext);
			printf(text);
			curChar=0;
			text[0]=0;
			hextext[0]=0;
		}
	}
	if(curChar!=0) {
		text[curChar]=0;
		while(curChar!=16) {
			lstrcat(hextext,"   ");
			curChar++;
		}
		lstrcat(text,"\r\n");
		lstrcat(hextext,"  ");
		printf(hextext);
		printf(text);
	}
	
	printf("=====End New Packet=====\n\n");
  }