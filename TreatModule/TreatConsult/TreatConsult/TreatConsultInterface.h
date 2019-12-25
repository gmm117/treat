// TreatConsultInterface.h : Declaration of the CTreatConsultInterface

#pragma once
#include "resource.h"       // main symbols
#include "TreatConsult_i.h"
#include "ADO.h"
#include "ProcHook.h"

#define IDC_LIST_BASIC_SUGA			WM_USER+2
#define IDC_EDIT_BASIC_CONTROL		WM_USER + 100
#define IDC_STATIC_BASIC_CONTROL	WM_USER + 300

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CTreatConsultInterface

class ATL_NO_VTABLE CTreatConsultInterface :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTreatConsultInterface, &CLSID_TreatConsultInterface>,
	public IDispatchImpl<ITreatConsultInterface, &IID_ITreatConsultInterface, &LIBID_TreatConsultLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public CDialogImpl<CTreatConsultInterface>,
	public CProcHooker<CTreatConsultInterface>
{
	// Dialog ID
public:
	enum { IDD = IDD_MAIN };

	//////////////////////////////////////////////////////////////////////////////////
	// 생성자 소멸자																	//
	//////////////////////////////////////////////////////////////////////////////////
public:
	CTreatConsultInterface();
	~CTreatConsultInterface();

	//////////////////////////////////////////////////////////////////////////////////
	// Message ComMap																//
	//////////////////////////////////////////////////////////////////////////////////

DECLARE_REGISTRY_RESOURCEID(IDR_TREATCONSULTINTERFACE)


BEGIN_COM_MAP(CTreatConsultInterface)
	COM_INTERFACE_ENTRY(ITreatConsultInterface)
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

	//////////////////////////////////////////////////////////////////////////////
	// Message Map																//
	//////////////////////////////////////////////////////////////////////////////

	BEGIN_MSG_MAP(CTreatConsultInterface)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)

		COMMAND_HANDLER(IDC_COMBO_HOSPDIV, CBN_SELCHANGE, OnChangeHospDiv)
		COMMAND_HANDLER(IDC_COMBO_STANDATE, CBN_SELCHANGE, OnChangeStanddate)

		NOTIFY_HANDLER(IDC_LIST_BASIC_SUGA, NM_DBLCLK, OnListDblClk)

	REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	//////////////////////////////////////////////////////////////////////////////
	// Message Handler															//
	//////////////////////////////////////////////////////////////////////////////
public:
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChangeHospDiv(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnChangeStanddate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDefaultCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	LRESULT OnListDblClk(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/);



	//////////////////////////////////////////////////////////////////////////////////
	// Member Interface																//
	//////////////////////////////////////////////////////////////////////////////////
public:
	STDMETHOD(CreateModule)(IUnknown* pUnkn, long lParentHwnd, long lLeft, long lTop, long lRight, long lBottom);
	STDMETHOD(Show)(VARIANT_BOOL bShow);
	STDMETHOD(ChildDestroy)();
	STDMETHOD(RefleshEnvData)();

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Function																//
	//////////////////////////////////////////////////////////////////////////////////
	void	InitializeAttach();
	void	DestroyDetach();
	void	InitializeControl();
	void	DestroyControl();

	void	CreatTreatControl();
	void	LoadTreatControl();
	void	LoadComboHospDiv();
	void	LoadBasicSuga();
	void	LoadTreatData();

	void	CalcTreatData();

	void	InsertBasicSugaList();
	void	SetJisuData(CString strJisu = _T(""));

	CString GetStandDate();
	long	GetHospDiv();


	BOOL OnHook(const MSG* msg);
	

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Control																//
	//////////////////////////////////////////////////////////////////////////////////
	CListViewCtrl	m_wndBasicList;		// 기초수가 List
	CComboBox		m_cboStandDate;		// 기준시점 수가
	CComboBox		m_cboHospDiv;		// 병원구분
	CEdit			m_editJisu;			// 환산지수
	CEdit			m_editCalc;			// 계산식	
	CEdit			m_editHisCost;		// 본인부담금
	CEdit			m_sleCode;			// 진찰료코드
	CEdit			m_editSatCost;		// 토요가산금

	CStatic			m_stCalcFormula;

	CEdit*			m_peditContData;
	CStatic*		m_pstContData;

	CFont			m_hStNameFont;

	CToolTipCtrl	m_wndToolTip;

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Values																//
	//////////////////////////////////////////////////////////////////////////////////
	CADOConnection m_obDbConn;

	long		m_lTotSize;
};

OBJECT_ENTRY_AUTO(__uuidof(TreatConsultInterface), CTreatConsultInterface)
