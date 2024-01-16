#pragma once
#define NETWORKDLL_EXPORTS 
#include "NetHeader.h"


class NETWORKDLL_API GamePacketOut : public PacketOut
{
public:
	GamePacketOut(void);
	GamePacketOut(int Code);
	~GamePacketOut(void);

	void		WritePacketID(int id);
	void		WritePacketMasterID(int masterID);
	void		FinishPacket(ClientBase *Client);

	int			GetID();

protected:

	void			Encode(short KeyStart);
	void			WriteChecksum();
	void			WriteLen();
};
