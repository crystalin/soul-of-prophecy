#pragma once
#define SERVERBASE_EXPORTS 
#include "ServerBase.h"

class SERVERBASE_API PacketIn
{
public:
	PacketIn();
	PacketIn(char *buff, int len, SOCKADDR_IN address);
	~PacketIn(void);

	BYTE		ReadByte();
	USHORT		ReadShort();
	USHORT		ReadShortLowEndian();
	UINT		ReadInt();
	UINT		ReadInversedInt();
	void		Skip(long num);
	void		Read(BYTE* buf,int start,int num);
	char*		ReadPascalString();
	char*		ReadString(int maxlen);
	int			GetLen();
	SOCKADDR_IN	GetAddress();

protected:
	
	SOCKADDR_IN m_address;
	int			m_len;
	int			m_offset;
	char		m_buff[PACKETIN_MAX_SIZE];

};
