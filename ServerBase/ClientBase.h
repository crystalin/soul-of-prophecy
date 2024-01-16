#pragma once
#define SERVERBASE_EXPORTS 
#include "ServerBase.h"

class SERVERBASE_API ClientBase
{
public:
	ClientBase(void);
	ClientBase(SOCKADDR_IN Address,int id);
	~ClientBase(void);

	int			GetID();
	SOCKADDR_IN GetAddrSock();

	virtual bool OnRecv(){return true;}

protected:
	
	int			m_id;
	SOCKADDR_IN m_address;

};
