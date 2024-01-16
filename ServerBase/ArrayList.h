#pragma once
#define SERVERBASE_EXPORTS 
#include "ServerBase.h"

class SERVERBASE_API ArrayList
{
public:
	ArrayList(int maxlen);
	~ArrayList(void);
	void Add(void *p_array);
	void Remove(void *p_array);
	int	 Count();
	int	 MaxSize();
	void *GetArray(int index);
protected:
	int m_maxsize;
	int m_count;
	void **m_list;
};
