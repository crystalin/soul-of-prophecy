#include ".\packetin.h"

PacketIn::PacketIn()
{
	memset(m_buff,0,PACKETIN_MAX_SIZE);
	memset(&m_address,0,sizeof(m_address));
}

PacketIn::PacketIn(char *buff, int len, SOCKADDR_IN address)
{
	memset(m_buff,0,PACKETIN_MAX_SIZE);
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
}

PacketIn::~PacketIn(void)
{
}

BYTE PacketIn::ReadByte()
{
	BYTE value;
	value=(BYTE)m_buff[m_offset];
	m_offset++;
	return value;
}

USHORT PacketIn::ReadShort()
{
	int v1 = ReadByte();
	int v2 = ReadByte();

	return (USHORT)((v2 & 0xff) | (v1 & 0xff) << 8);
}

USHORT PacketIn::ReadShortLowEndian()
{
	int v1 = ReadByte();
	int v2 = ReadByte();

	return (USHORT)((v1 & 0xff) | (v2 & 0xff) << 8);
}

UINT PacketIn::ReadInt()
{
	int v1 = ReadByte();
	int v2 = ReadByte();
	int v3 = ReadByte();
	int v4 = ReadByte();

	return (UINT)((v1 << 24) | (v2 << 16) | (v3 << 8) | v4);
}

UINT PacketIn::ReadInversedInt()
{
	int v1 = ReadByte();
	int v2 = ReadByte();
	int v3 = ReadByte();
	int v4 = ReadByte();

	return (UINT)((v4 << 24) | (v3 << 16) | (v2 << 8) | v1);
}

void PacketIn::Skip(long num)
{
	m_offset+=num;
}

void PacketIn::Read(BYTE* buf,int start,int num)
{
	for(int i = 0; i < num ; ++i)
	{
		buf[i+start]=ReadByte();
	}
}

char* PacketIn::ReadPascalString(void)
{
	int size = ReadShort();
	return ReadString(size);
}

char* PacketIn::ReadString(int len)
{
	BYTE* buf = new BYTE[len+1];
	Read(buf, 0, len);
	buf[len]=0;
	return (char *)buf;
}

int PacketIn::GetLen()
{
	return m_len;
}

SOCKADDR_IN PacketIn::GetAddress()
{
	return m_address;
}