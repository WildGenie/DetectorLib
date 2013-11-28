#include "StdAfx.h"
#include "DataProvider.h"

DataProvider::DataProvider(void):m_ConsumerList()
{
//	m_ConsumerList.clear();
}

DataProvider::~DataProvider(void)
{
	
}
void DataProvider::AddConsumer (DataConsumerIF* consumer)
{
	m_ConsumerList.push_back (consumer);
}

void DataProvider::RemoveConsumer (DataConsumerIF* consumer)
{
	m_ConsumerList.remove (consumer);
}
//����������ʲô�ģ�
void DataProvider::OnNotify (BYTE* buf, int size)
{
	list <DataConsumerIF*>::iterator Iter;
	for ( Iter = m_ConsumerList.begin( ); Iter != m_ConsumerList.end( ); Iter++ )
		(*Iter)->OnNotify(buf, size);
}