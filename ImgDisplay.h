// ImgDisplay.h : CImgDisplay ������
#pragma once
#include "resource.h"       // ������
#include <atlctl.h>
#include "DetectorLib_i.h"
#include "_IImgDisplayEvents_CP.h"
#include "src/ImgDisplayImpl.h"
#include "src/DIBImage.h"
#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;



// CImgDisplay
class ATL_NO_VTABLE CImgDisplay :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CImgDisplay, IImgDisplay>,
	public IOleControlImpl<CImgDisplay>,
	public IOleObjectImpl<CImgDisplay>,
	public IOleInPlaceActiveObjectImpl<CImgDisplay>,
	public IViewObjectExImpl<CImgDisplay>,
	public IOleInPlaceObjectWindowlessImpl<CImgDisplay>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CImgDisplay>,
	public CProxy_IImgDisplayEvents<CImgDisplay>,
	public IQuickActivateImpl<CImgDisplay>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CImgDisplay>,
#endif
	public IProvideClassInfo2Impl<&CLSID_ImgDisplay, &__uuidof(_IImgDisplayEvents), &LIBID_DetectorLibLib>,
	public CComCoClass<CImgDisplay, &CLSID_ImgDisplay>,
	public CComControl<CImgDisplay>
{
private:
	ImgDisplayImpl* m_pImgDisplay;

	BOOL m_bOpened;
public:


	CImgDisplay()
	{
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_IMGDISPLAY)


BEGIN_COM_MAP(CImgDisplay)
	COM_INTERFACE_ENTRY(IImgDisplay)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IQuickActivate)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CImgDisplay)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY_TYPE("AutoSize", DISPID_AUTOSIZE, CLSID_NULL, VT_BOOL)
	PROP_ENTRY_TYPE("BorderVisible", DISPID_BORDERVISIBLE, CLSID_NULL, VT_BOOL)
	PROP_ENTRY_TYPE("DrawMode", DISPID_DRAWMODE, CLSID_NULL, VT_I4)
	// ʾ����
	// PROP_ENTRY_TYPE("������", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CImgDisplay)
	CONNECTION_POINT_ENTRY(__uuidof(_IImgDisplayEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CImgDisplay)
	CHAIN_MSG_MAP(CComControl<CImgDisplay>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_DISPLAY_REFRESH,OnRefresh)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
END_MSG_MAP()
// �������ԭ��:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IImgDisplay,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IImgDisplay
public:
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		BOOL bRunTime;
		GetAmbientUserMode(bRunTime);
		if(bRunTime)
		{
			if(!::IsWindow(m_hWnd))
			{
				return 0;
			}
			if (m_pImgDisplay)
			{
				if (m_pImgDisplay->IsOpened())
				{
					m_pImgDisplay->Refresh();
				}
			}
				
			return 0;
		}
		RECT& rc = *(RECT*)di.prcBounds;
		// ��������������Ϊ di.prcBounds ָ���ľ���
		HRGN hRgnOld = NULL;
		if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
			hRgnOld = NULL;
		bool bSelectOldRgn = false;

		HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

		if (hRgnNew != NULL)
		{
			bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
		}

		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ImgDisplay");
#ifndef _WIN32_WCE
		TextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			pszText,
			lstrlen(pszText));
#else
		ExtTextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			ETO_OPAQUE,
			NULL,
			pszText,
			ATL::lstrlen(pszText),
			NULL);
#endif

		if (bSelectOldRgn)
			SelectClipRgn(di.hdcDraw, hRgnOld);

		return S_OK;
	}

	void OnAutoSizeChanged()
	{
		ATLTRACE(_T("OnAutoSizeChanged\n"));
	}
	BOOL m_bBorderVisible;
	void OnBorderVisibleChanged()
	{
		ATLTRACE(_T("OnBorderVisibleChanged\n"));
	}
	LONG m_nDrawMode;
	void OnDrawModeChanged()
	{
		ATLTRACE(_T("OnDrawModeChanged\n"));
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_pImgDisplay = new ImgDisplayImpl();
		return S_OK;
	}

	void FinalRelease()
	{
		if (m_pImgDisplay)
			delete m_pImgDisplay;
	}

	STDMETHOD(Open)(ULONG width, ULONG height);
	STDMETHOD(Close)(void);
	STDMETHOD(get_ImgHandle)(ULONG* pVal);
	STDMETHOD(put_ImgHandle)(ULONG newVal);
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRefresh(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	STDMETHOD(get_MapStart)(ULONG* pVal);
	STDMETHOD(put_MapStart)(ULONG newVal);
	STDMETHOD(get_MapEnd)(ULONG* pVal);
	STDMETHOD(put_MapEnd)(ULONG newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(ImgDisplay), CImgDisplay)
