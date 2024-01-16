#include ".\clientbase.h"

ClientBase::ClientBase(SOCKADDR_IN Address, int ID)
{
	memcpy(&m_address,&Address,sizeof(Address));
	m_id=ID;
}

ClientBase::ClientBase(void)
{
	memset(&m_address,0,sizeof(m_address));
	m_id=0;
}

ClientBase::~ClientBase(void)
{
}

int ClientBase::GetID()
{
	return m_id;
}
SOCKADDR_IN ClientBase::GetAddrSock()
{
	return m_address;
}