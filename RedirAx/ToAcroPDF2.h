// ToAcroPDF2.h : CToAcroPDF2 の宣言
#pragma once
#include "resource.h"       // メイン シンボル
#include <atlctl.h>
#include "RedirAx.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif


// CToAcroPDF2
class ATL_NO_VTABLE CToAcroPDF2 :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IToAcroPDF2, &IID_IToAcroPDF2, &LIBID_RedirAxLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	//public IPersistStreamInitImpl<CToAcroPDF2>,
	public IOleControlImpl<CToAcroPDF2>,
	public IOleObjectImpl<CToAcroPDF2>,
	public IOleInPlaceActiveObjectImpl<CToAcroPDF2>,
	public IViewObjectExImpl<CToAcroPDF2>,
	public IOleInPlaceObjectWindowlessImpl<CToAcroPDF2>,
	public IObjectSafetyImpl<CToAcroPDF2, INTERFACESAFE_FOR_UNTRUSTED_CALLER|INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CComCoClass<CToAcroPDF2, &CLSID_ToAcroPDF2>,
	public CComCompositeControl<CToAcroPDF2>,
	public IPersistPropertyBag,
	public IBindStatusCallback
{
public:
	CToAcroPDF2()
	{
		m_bWindowOnly = TRUE;
		CalcExtent(m_sizeExtent);
	}

DECLARE_OLEMISC_STATUS(0
	|OLEMISC_RECOMPOSEONRESIZE
	|OLEMISC_CANTLINKINSIDE
	|OLEMISC_INSIDEOUT
	|OLEMISC_ACTIVATEWHENVISIBLE
	|OLEMISC_SETCLIENTSITEFIRST
	)

DECLARE_REGISTRY_RESOURCEID(IDR_TOACROPDF2)


BEGIN_COM_MAP(CToAcroPDF2)
	COM_INTERFACE_ENTRY(IToAcroPDF2)
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
	//COM_INTERFACE_ENTRY(IPersistStreamInit)
	//COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IPersistPropertyBag)
	COM_INTERFACE_ENTRY(IBindStatusCallback)
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
END_COM_MAP()

BEGIN_PROP_MAP(CToAcroPDF2)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// エントリの例
	// PROP_ENTRY("プロパティの説明", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CToAcroPDF2)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	CHAIN_MSG_MAP(CComCompositeControl<CToAcroPDF2>)
END_MSG_MAP()
// ハンドラ プロパティ:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

BEGIN_SINK_MAP(CToAcroPDF2)
	//イベント ハンドラに __stdcall 呼び出し規約があるかどうかを確認します。
END_SINK_MAP()

	STDMETHOD(OnAmbientPropertyChange)(DISPID dispid)
	{
		if (dispid == DISPID_AMBIENT_BACKCOLOR)
		{
			SetBackgroundColorFromAmbient();
			FireViewChange();
		}
		return IOleControlImpl<CToAcroPDF2>::OnAmbientPropertyChange(dispid);
	}
// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IToAcroPDF2

	enum { IDD = IDD_TOACROPDF2 };

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct() {
		return S_OK;
	}

	void FinalRelease() {
		if (tempFilePath.Length() != 0) {
			ATLVERIFY(DeleteFile(tempFilePath));
			tempFilePath.Empty();
		}
	}

protected:
	CComBSTR srcProp;
	bool isAsyncDownload;
	ULONG curPos;
	ULONG maxPos;
	CComPtr<IStream> pStreamAsync;
	CComBSTR statusText;
	CComPtr<IBinding> protocolBind;
	DWORD tickLastInv;
	CComBSTR tempFilePath;
	CComBSTR queuedSrc;
	bool loaded;

	bool LoadFromMoniker(LPBC pibc, LPMONIKER pMonikerDL);
	void Setsrc(LPCWSTR pcwSrc);
	bool LoadSyncSt(LPSTREAM pStream);

public:
	STDMETHOD(GetClassID)(CLSID *pClassID)
	{
		ATLTRACE(atlTraceCOM, 2, _T("IPersistImpl::GetClassID\n"));
		if (pClassID == NULL)
			return E_FAIL;
		*pClassID = GetObjectCLSID();
		return S_OK;
	}

	// IPersistPropertyBag : public IPersist
public:
	virtual HRESULT STDMETHODCALLTYPE InitNew( void)
	{
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Load( 
		/* [in] */ __RPC__in_opt IPropertyBag *pPropBag,
		/* [unique][in] */ __RPC__in_opt IErrorLog *pErrorLog)
	{
		HRESULT hr;
		if (pPropBag == NULL)
			return E_POINTER;

		loaded = false;
		isAsyncDownload = false;
		tickLastInv = 0;

		CComVariant srcVtProp;
		hr = pPropBag->Read(L"src", &srcVtProp, pErrorLog);

		srcProp.Empty();

		if (S_OK == srcVtProp.ChangeType(VT_BSTR)) {
			srcProp = srcVtProp.bstrVal;

			CComPtr<IBindCtx> pibc;
			if (SUCCEEDED(hr = CreateBindCtx(0, &pibc))) {
				IOleClientSite *pClientSite = m_spClientSite;
				if (pClientSite != NULL) {
					CComPtr<IMoniker> pMonikerDL;
					if (pMonikerDL == NULL) {
						CComQIPtr<IBindHost> pBindHost = pClientSite;
						if (pBindHost != NULL) {
							if (SUCCEEDED(hr = pBindHost->CreateMoniker((srcProp), pibc, &pMonikerDL, 0))) {

							}
						}
					}
					if (pMonikerDL == NULL) {
						CComPtr<IMoniker> pimkName;
						if (SUCCEEDED(hr = pClientSite->GetMoniker(OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_CONTAINER, &pimkName))) {
							CComPtr<IBindCtx> pibc;
							CreateBindCtx(0, &pibc);
							ULONG chEaten = 0;
							if (SUCCEEDED(hr = pimkName->ParseDisplayName(pibc, pimkName, (srcProp), &chEaten, &pMonikerDL))) {

							}
						}
					}

					if (pMonikerDL != NULL) {
						LPOLESTR pszDisplayName = NULL;
						if (SUCCEEDED(hr = pMonikerDL->GetDisplayName(pibc, NULL, &pszDisplayName))) {
							//m_title = pszDisplayName;
							CoTaskMemFree(pszDisplayName);
						}
					}

					LoadFromMoniker(pibc, pMonikerDL);
				}
			}
		}

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Save( 
		/* [in] */ __RPC__in_opt IPropertyBag *pPropBag,
		/* [in] */ BOOL fClearDirty,
		/* [in] */ BOOL fSaveAllProperties)
	{
		HRESULT hr;
		if (pPropBag == NULL)
			return E_POINTER;

		pPropBag->Write(L"src", &CComVariant(srcProp));

		return S_OK;
	}

	// IBindStatusCallback : public IUnknown
public:
	virtual HRESULT STDMETHODCALLTYPE OnStartBinding( 
		/* [in] */ DWORD dwReserved,
		/* [in] */ __RPC__in_opt IBinding *pib)
	{
		protocolBind = pib;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetPriority( 
		/* [out] */ __RPC__out LONG *pnPriority)
	{
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE OnLowResource( 
		/* [in] */ DWORD reserved)
	{
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE OnProgress( 
		/* [in] */ ULONG ulProgress,
		/* [in] */ ULONG ulProgressMax,
		/* [in] */ ULONG ulStatusCode,
		/* [unique][in] */ __RPC__in_opt LPCWSTR szStatusText)
	{
		statusText = szStatusText;
		curPos = ulProgress;
		maxPos = ulProgressMax;

		DWORD t = GetTickCount();
		if (m_hWndCD != NULL && (ulProgress == ulProgressMax || tickLastInv + 500 < t)) {
			FireViewChange();
			tickLastInv = t;
		}
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE OnStopBinding( 
		/* [in] */ HRESULT hresult,
		/* [unique][in] */ __RPC__in_opt LPCWSTR szError)
	{
		HRESULT hr;
		protocolBind.Release();

		if (hresult == S_OK && pStreamAsync != NULL) {
			LoadSyncSt(pStreamAsync);
		}
		return S_OK;
	}

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetBindInfo( 
		/* [out] */ DWORD *grfBINDF,
		/* [unique][out][in] */ BINDINFO *pbindinfo)
	{
		*grfBINDF |= BINDF_ASYNCHRONOUS | BINDF_NEEDFILE;
		return S_OK;
	}

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE OnDataAvailable( 
		/* [in] */ DWORD grfBSCF,
		/* [in] */ DWORD dwSize,
		/* [in] */ FORMATETC *pformatetc,
		/* [in] */ STGMEDIUM *pstgmed)
	{
		if (0 != (grfBSCF & (BSCF_DATAFULLYAVAILABLE|BSCF_LASTDATANOTIFICATION)) && pstgmed->tymed == TYMED_ISTREAM) {
			pStreamAsync = pstgmed->pstm;
		}

		ReleaseStgMedium(pstgmed);
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable( 
		/* [in] */ __RPC__in REFIID riid,
		/* [iid_is][in] */ __RPC__in_opt IUnknown *punk)
	{
		return S_OK;
	}

public:
	virtual HRESULT STDMETHODCALLTYPE DoVerb( 
		/* [in] */ LONG iVerb,
		/* [unique][in] */ __RPC__in_opt LPMSG lpmsg,
		/* [unique][in] */ __RPC__in_opt IOleClientSite *pActiveSite,
		/* [in] */ LONG lindex,
		/* [in] */ __RPC__in HWND hwndParent,
		/* [unique][in] */ __RPC__in_opt LPCRECT lprcPosRect)
	{
		return __super::DoVerb(iVerb, lpmsg, pActiveSite, lindex, hwndParent, lprcPosRect);
	}

	HWND Create(HWND hWndParent, RECT& /*rcPos*/, LPARAM dwInitParam = NULL)
	{
		CComControl< CToAcroPDF2, CAxDialogImpl< CToAcroPDF2 > >::Create(hWndParent, dwInitParam);
		if (m_hWnd != NULL) {
			SetBackgroundColorFromAmbient();
			ShowWindow(SW_SHOWNOACTIVATE);
		}
		return m_hWnd;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

OBJECT_ENTRY_AUTO(__uuidof(ToAcroPDF2), CToAcroPDF2)
