// CmdController.h : CCmdController ������

#pragma once
#include "resource.h"       // ������



#include "DetectorLib_i.h"
#include "src/CmdControllerImpl.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CCmdController

class ATL_NO_VTABLE CCmdController :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCmdController, &CLSID_CmdController>,
	public IDispatchImpl<ICmdController, &IID_ICmdController, &LIBID_DetectorLibLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
private:
	CmdControllerImpl m_CmdController;
public:
	CCmdController()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CMDCONTROLLER)


BEGIN_COM_MAP(CCmdController)
	COM_INTERFACE_ENTRY(ICmdController)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

public:
	STDMETHOD(get_CoderHandle)(ULONG* pVal);
public:
	STDMETHOD(put_CoderHandle)(ULONG newVal);
public:
	STDMETHOD(get_IntegrationTime)(long* pVal);//ST
public:
	STDMETHOD(put_IntegrationTime)(long newVal);
public:
	STDMETHOD(get_FrameOut)(LONG* pVal);//SF
public:
	STDMETHOD(put_FrameOut)(LONG newVal);

};

OBJECT_ENTRY_AUTO(__uuidof(CmdController), CCmdController)
