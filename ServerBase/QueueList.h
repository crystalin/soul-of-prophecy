#ifndef __QUEUELIST_H__
#define __QUEUELIST_H__

#include "ServerBase.h"

class ObjectArrays
{
public:
	ObjectArrays(void *p_pointer);
	~ObjectArrays();

	ObjectArrays	*Next();
	void			*Data();
	void			SetNext(ObjectArrays *p_next);

protected:

	void *m_data;
	ObjectArrays *m_next;
};

class QueueList
{
public:
	QueueList(void);
	~QueueList(void);

	void	Add(void *p_data);
	void	*GetNext();
	int		Count();

protected:

	ObjectArrays	*m_first;
	ObjectArrays	*m_last;
	int				m_counter;
	
};

#endif