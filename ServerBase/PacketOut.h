#pragma once
#define SERVERBASE_EXPORTS 

#include "ServerBase.h"

class SERVERBASE_API PacketOut
{
public:
	PacketOut(void);
	~PacketOut(void);

	void	WriteByte(BYTE Byte);
	void	WriteShort(USHORT Short);
	void	WriteShortLowEndian(USHORT Short);
	void	WriteInt(UINT Int);
	void	WriteInt64(__int64 Int);
	void	WriteInversedInt(UINT Int);
	void	Fill(BYTE val, int num);
	void	WritePascalString(char* str);
	void	WritePascalString(char* str,int len);
	void	WriteString(char* str);
	void	WriteString(char* str, int maxlen);
	void	Log(void);

	int			GetLen();
	SOCKADDR_IN GetSockAddr();
	ClientBase	*GetTargetClient();
	char		*GetBuffer();
	void		SetTargetClient(ClientBase *Client);

protected:

	char		m_buff[PACKETOUT_MAX_SIZE];
	int			m_offset;
	SOCKADDR_IN m_sockaddr;

	ClientBase		*m_client;

};
