// SocketChannel.h : CSocketChannel ������

#pragma once
#include "resource.h"       // ������



#include "DetectorLib_i.h"
#include "_ISocketChannelEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CSocketChannel

class ATL_NO_VTABLE CSocketChannel :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSocketChannel, &CLSID_SocketChannel>,
	public IConnectionPointContainerImpl<CSocketChannel>,
	public CProxy_ISocketChannelEvents<CSocketChannel>,
	public IDispatchImpl<ISocketChannel, &IID_ISocketChannel, &LIBID_DetectorLibLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSocketChannel()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SOCKETCHANNEL)


BEGIN_COM_MAP(CSocketChannel)
	COM_INTERFACE_ENTRY(ISocketChannel)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSocketChannel)
	CONNECTION_POINT_ENTRY(__uuidof(_ISocketChannelEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(get_RemoteIP)(BSTR* pVal);
	STDMETHOD(put_RemoteIP)(BSTR newVal);
	STDMETHOD(get_RemotePort)(SHORT* pVal);
	STDMETHOD(put_RemotePort)(SHORT newVal);
	STDMETHOD(Open)(void);
	STDMETHOD(Close)(void);
	STDMETHOD(get_ObjectHandle)(ULONG* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(SocketChannel), CSocketChannel)
