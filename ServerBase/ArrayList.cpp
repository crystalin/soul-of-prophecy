#include ".\arraylist.h"


ArrayList::ArrayList(int maxlen)
{
	m_maxsize=maxlen;
	m_count=0;
	m_list=new void*[maxlen];
	memset(m_list,0,maxlen*4);
}

ArrayList::~ArrayList(void)
{
	if (m_list!=NULL)
		delete[] m_list;
}


void ArrayList::Add(void *p_array)
{
	if (m_count+1>m_maxsize)
		return;
	for (int i=0;i<m_maxsize;i++)
	{
		if (m_list[i]==NULL)
		{
			m_list[i]=p_array;
			m_count++;
			return;
		}
	}
}

void ArrayList::Remove(void *p_array)
{
	for (int i=0;i<m_maxsize;i++)
	{
		if (m_list[i]==p_array)
		{
			m_list[i]=NULL;
			m_count--;
			return;
		}
	}
}

int ArrayList::Count()
{
	return m_count;
}

int ArrayList::MaxSize()
{
	return m_maxsize;
}

void *ArrayList::GetArray(int index)
{
	int index_temp=-1;
	if (index>m_maxsize ||index>m_count)
		return NULL;
	for (int i = 0;i<m_maxsize;i++)
	{
		if (m_list[i]!=NULL)
			index_temp++;
		if (index_temp==index)
			return m_list[i];
	}
	return NULL;
}