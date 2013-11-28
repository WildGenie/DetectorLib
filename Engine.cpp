// Engine.cpp : CEngine ��ʵ��

#include "stdafx.h"
#include "Engine.h"


// CEngine



STDMETHODIMP CEngine::Start(void)
{
	// TODO: �ڴ����ʵ�ִ��� 
	m_Engine->Start();
	return S_OK;
}


STDMETHODIMP CEngine::Stop(void)
{
	// TODO: �ڴ����ʵ�ִ���
	m_Engine->Stop();
	return S_OK;
}


STDMETHODIMP CEngine::get_ChannelHandle(ULONG* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	*pVal = (ULONG) m_Engine->GetChannel(); 
	return S_OK;
}


STDMETHODIMP CEngine::put_ChannelHandle(ULONG newVal)
{
	// TODO: �ڴ����ʵ�ִ���
	m_Engine->SetChannel((ChannelIF*) newVal);
	return S_OK;
}


STDMETHODIMP CEngine::get_ObjectHandle(ULONG* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	*pVal = (ULONG) m_Engine;
	return S_OK;
}

STDMETHODIMP_(void) CEngine::OnDataReady(BYTE* buf, int size)
{
	// TODO: Add your implementation code here
}

void CEngine::OnNotify ( BYTE* buf, int size)
{
	Fire_OnDataReady(buf, size);
}

void CEngine::OnConnect () 
{
	Fire_OnConnect ();
}
void CEngine::OnDisConnect ()
{
   Fire_OnDisconnect ();
}
