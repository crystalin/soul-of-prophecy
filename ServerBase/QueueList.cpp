#include ".\QueueList.h"

QueueList::QueueList(void)
{
	m_first=NULL;
	m_last=NULL;
	m_counter=0;
}

QueueList::~QueueList(void)
{
	/*void *data;
	ObjectArrays *arrays1,*arrays2;

	if ((void *)m_first==NULL)
		return;
	arrays1 = m_first;
	while (arrays1 !=NULL )
	{
		arrays2 = arrays1->Next();
		data =arrays1->Data();

		delete data;
		delete arrays1;

		arrays1 = arrays2;
	}*/
}

// Ajouter un element a la file d'attente
void QueueList::Add(void *p_data)
{
	ObjectArrays *newArray = new ObjectArrays(p_data);
	if( m_first == NULL ) // Si la liste est vide
	{
		m_first = newArray;
		m_last  = newArray;
	}
	else // Si il y a deja un element dans la liste
	{
		m_last->SetNext(newArray);
		m_last  = newArray;
	}
	m_counter++;
}

// Retire le premier element de la file et retourne son adresse
void *QueueList::GetNext()
{
	void *data;
	ObjectArrays *tempArray;

	if( m_first == NULL ) //Si aucun element dans la liste
		return NULL;

	data = m_first->Data();

	if ( m_first == m_last) //Si il y a 1 seul element
	{
		delete m_first;

		m_first = NULL;
		m_last  = NULL;
	}
	else //Si il y a plusieurs elements
	{
		tempArray  = m_first->Next();
		delete m_first;

		m_first = tempArray;
	}
	m_counter--;
	return data;
}

int QueueList::Count()
{
	return m_counter;
}

ObjectArrays::ObjectArrays(void *p_pointer)
{
	m_data = p_pointer;
	m_next = NULL;
}
ObjectArrays::~ObjectArrays()
{
}


ObjectArrays *ObjectArrays::Next()
{
	return	m_next;
}

void *ObjectArrays::Data()
{
	return	m_data;
}

void ObjectArrays::SetNext(ObjectArrays *p_next)
{
	m_next = p_next;
}