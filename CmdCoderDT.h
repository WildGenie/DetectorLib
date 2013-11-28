// CmdCoderDT.h : CCmdCoderDT ������

#pragma once
#include "resource.h"       // ������



#include "DetectorLib_i.h"
#include "_ICmdCoderDTEvents_CP.h"
#include "src/CmdCoderImpl.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CCmdCoderDT

class ATL_NO_VTABLE CCmdCoderDT :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCmdCoderDT, &CLSID_CmdCoderDT>,
	public IConnectionPointContainerImpl<CCmdCoderDT>,
	public CProxy_ICmdCoderDTEvents<CCmdCoderDT>,
	public IDispatchImpl<ICmdCoderDT, &IID_ICmdCoderDT, &LIBID_DetectorLibLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
private:
	CmdCoderImpl* m_pCmdCoder;

public:
	CCmdCoderDT()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CMDCODERDT)


BEGIN_COM_MAP(CCmdCoderDT)
	COM_INTERFACE_ENTRY(ICmdCoderDT)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCmdCoderDT)
	CONNECTION_POINT_ENTRY(__uuidof(_ICmdCoderDTEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_pCmdCoder = new CmdCoderImpl;
		return S_OK;
	}

	void FinalRelease()
	{
		if (m_pCmdCoder)
			delete m_pCmdCoder;
	}

public:
	STDMETHOD(get_ObjectHandle)(ULONG* pVal);
public:
	STDMETHOD(get_EngineHandle)(ULONG* pVal);
public:
	STDMETHOD(put_EngineHandle)(ULONG newVal);
};


OBJECT_ENTRY_AUTO(__uuidof(CmdCoderDT), CCmdCoderDT)
