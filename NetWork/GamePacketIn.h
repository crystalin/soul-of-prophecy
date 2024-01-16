#pragma once
#define NETWORKDLL_EXPORTS 
#include "NetHeader.h"

class NETWORKDLL_API GamePacketIn : public PacketIn
{
public:
	GamePacketIn(char *buff, int len, SOCKADDR_IN address);
	~GamePacketIn(void);
	bool VerifyChecksum();
	void Decode();

	bool		IsMessage();
	bool		IsAckReponse();
	bool		IsAckRequest();

	int			GetType();
	int			GetID();
	int			GetRecvTime();
	short		GetCode();
	int			GetMasterID();
	int			GetMessageLen();
	void		Log(void);

protected:
	unsigned short		m_code;
	unsigned int		m_pakfragnum;
	unsigned int		m_paktype;
	unsigned int		m_pakid;
	unsigned int		m_pakmasterid;
	unsigned short		m_cryptvalue;
	unsigned short		m_datachecksum;
	int					m_recvtime;
};

