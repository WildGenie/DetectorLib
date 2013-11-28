// Engine.h : CEngine ������

#pragma once
#include "resource.h"       // 
#include "DetectorLib_i.h"
#include "_IEngineEvents_CP.h"
#include "src/EngineIF.h"
#include "src/EngineImpl.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CEngine

class ATL_NO_VTABLE CEngine :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEngine, &CLSID_Engine>,
	public IConnectionPointContainerImpl<CEngine>,
	public CProxy_IEngineEvents<CEngine>,
	public IDispatchImpl<IEngine, &IID_IEngine, &LIBID_DetectorLibLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public DataConsumerIF,
	public ConnectionStatusIF
{
private:
	EngineIF* m_Engine;
public:
	CEngine()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ENGINE)


BEGIN_COM_MAP(CEngine)
	COM_INTERFACE_ENTRY(IEngine)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CEngine)
	CONNECTION_POINT_ENTRY(__uuidof(_IEngineEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_Engine = new (EngineImpl);
		m_Engine->SetMonitor (this);
		m_Engine->AddConsumer(this);
		return S_OK;
	}

	void FinalRelease()
	{
		if (m_Engine)
		{
			delete m_Engine;
			m_Engine = NULL;
		}
	}

public:

	STDMETHOD(Start)(void);
	STDMETHOD(Stop)(void);
	STDMETHOD(get_ChannelHandle)(ULONG* pVal);
	STDMETHOD(put_ChannelHandle)(ULONG newVal);
	STDMETHOD(get_ObjectHandle)(ULONG* pVal);

	virtual void OnNotify (BYTE* buf, int size);
	virtual void OnConnect () ;
	virtual void OnDisConnect ();
	STDMETHOD_(void, OnDataReady)(BYTE* buf, int size);
};

OBJECT_ENTRY_AUTO(__uuidof(Engine), CEngine)
