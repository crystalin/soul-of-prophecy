#include ".\packetout.h"

PacketOut::PacketOut(void)
{
	m_offset=0;
	m_client=NULL;
	memset(&m_sockaddr,0,sizeof(SOCKADDR_IN));
}

PacketOut::~PacketOut(void)
{
}

void PacketOut::WriteByte(BYTE Byte)
{
	m_buff[m_offset]=(char)Byte;
	m_offset++;
}

void PacketOut::WriteShort(USHORT Short)
{
	WriteByte((BYTE)(Short >> 8));
	WriteByte((BYTE)(Short & 0xff));
}

void PacketOut::WriteShortLowEndian(USHORT Short)
{
	WriteByte((BYTE)(Short & 0xff));
	WriteByte((BYTE)(Short >> 8));
}

void PacketOut::WriteInt(UINT Int)
{
	WriteByte((BYTE)(Int >> 24));
	WriteByte((BYTE)((Int >> 16) & 0xff));
	WriteByte((BYTE)((Int & 0xffff) >> 8));
	WriteByte((BYTE)((Int & 0xffff) & 0xff));
}

void PacketOut::WriteInt64(__int64 Int)
{
	WriteByte((BYTE)((Int >> 56) & 0xff));
	WriteByte((BYTE)((Int >> 48) & 0xff));
	WriteByte((BYTE)((Int >> 40) & 0xff));
	WriteByte((BYTE)((Int >> 32) & 0xff));
	WriteByte((BYTE)((Int >> 24) & 0xff));
	WriteByte((BYTE)((Int >> 16) & 0xff));
	WriteByte((BYTE)((Int >> 8) & 0xff));
	WriteByte((BYTE)(Int & 0xff));
}

void PacketOut::WriteInversedInt(UINT Int)
{
	WriteByte((BYTE)((Int & 0xffff) & 0xff));
	WriteByte((BYTE)((Int & 0xffff) >> 8));
	WriteByte((BYTE)((Int >> 16) & 0xff));
	WriteByte((BYTE)(Int >> 24));
}

void PacketOut::Fill(BYTE val, int num)
{
	for(int i = 0; i < num; ++i)
	{
		WriteByte(val);
	}
}

void PacketOut::WritePascalString(char* str)
{
	WriteShort((USHORT)strlen(str));

	if(strlen(str) <= 0)
	{
		return;
	}
	CopyMemory(&m_buff[m_offset],str,strlen(str));
	m_offset+=(int)strlen(str);
}
void PacketOut::WritePascalString(char* str,int len)
{
	WriteShort(len);

	if(strlen(str) <= 0)
	{
		return;
	}
	CopyMemory(&m_buff[m_offset],str,len);
	m_offset+=len;
}

void PacketOut::WriteString(char* str)
{
	if(strlen(str) <= 0)
	{
		return;
	}
	CopyMemory(&m_buff[m_offset],str,strlen(str));
	m_offset+=(int)strlen(str);
	WriteByte(0x0);
}

void PacketOut::WriteString(char* str, int maxlen)
{
	if(strlen(str) <= 0)
	{
		return;
	}
	CopyMemory(&m_buff[m_offset],str,(int)strlen(str) < maxlen ? strlen(str) : maxlen );
	m_offset+=((int)strlen(str) < maxlen ? (int)strlen(str) : maxlen);
}

ClientBase *PacketOut::GetTargetClient()
{
	return m_client;
}

void PacketOut::SetTargetClient(ClientBase *Client)
{
	m_client=Client;
	m_sockaddr=Client->GetAddrSock();
}

char *PacketOut::GetBuffer()
{
	return m_buff;
}

int PacketOut::GetLen()
{
	return m_offset;
}

void PacketOut::Log(void)
{
	printf("=====PACKET=Out=\n");

	printf("Size : %03d , Code : %03d\n",m_offset,m_buff[17]);

	char hextext[100]="";
	char text[50]="";
	char tmptxt[4];

	int curChar=0;
	for(int i=0;i<m_offset;i++)
	{
		wsprintf(tmptxt,"%02X ",(unsigned __int8) m_buff[i]);
		lstrcat(hextext,tmptxt);
		if(m_buff[i]>=32)	text[curChar]=m_buff[i];
		else				text[curChar]='.';

		curChar++;
		if(curChar==16) 
		{
			text[curChar]=0;
			lstrcat(text,"\r\n");
			lstrcat(hextext,"  ");			printf(hextext);
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

SOCKADDR_IN PacketOut::GetSockAddr()
{
	return m_sockaddr;
}