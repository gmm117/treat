#include "stdafx.h"
#include "TreatCalcDlg.h"

CTreatCalcDlg::CTreatCalcDlg()
{
}

CTreatCalcDlg::~CTreatCalcDlg()
{
}

LRESULT CTreatCalcDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	// Register Dll 
	InitDllResiter();

	// Control Attach
	InitializeAttach();

	// Init Control Setting
	InitializeControl();

	// Init ADO Connection
	InitializeDB();

	// Init interface 
	InitializeInterface();

	// Set Windows Text
	LoadWindowText();

	// Select Windows Dialog
	ShowChildWindow(DEF_CONSULT_DIALOG);

	return TRUE;
}

LRESULT CTreatCalcDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndDialog(IDOK);

	return 0;
}

LRESULT CTreatCalcDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// ������ ��� Window�� Destroy
	m_ptrConsultTreat->ChildDestroy();

	// XML Wrapper Window�� Destroy
	m_prtWrapper->ChildDestroy();

	// Control Detach
	DestroyDetach();

	// Destroy Database 
	DestroyDB();

	// Destroy interface 
	DestroyInterface();

	return TRUE;
}

LRESULT CTreatCalcDlg::OnWebView(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HMENU hMenu, hPopupMenu;
	hMenu = LoadMenu(_Module.m_hInst, MAKEINTRESOURCE(IDR_WEBPAGE_MENU));
	hPopupMenu = GetSubMenu(hMenu, 0);

	POINT pCursor;
	::GetCursorPos(&pCursor);

	TrackPopupMenu(hPopupMenu, TPM_LEFTALIGN, pCursor.x, pCursor.y, 0, m_hWnd, NULL);
	DestroyMenu(hMenu);

	return 0L;
}

// ���Ǻ�����
LRESULT CTreatCalcDlg::OnLoadWebPage1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL bResult = FALSE;
	CString strUrl = _T("http://www.mw.go.kr/front_new/index.jsp");
	BSTR bstrData = strUrl.AllocSysString();

	m_prtWebView->ShowWebView(bstrData, &bResult);

	SysFreeString(bstrData);
	
	return 0L;
}

// �ɻ��򰡿�
LRESULT CTreatCalcDlg::OnLoadWebPage2(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL bResult = FALSE;
	CString strUrl = _T("http://www.hira.or.kr/dummy.do?pgmid=HIRAA030056020200&cmsurl=/cms/information/03/03/02/1323050_25438.html");
	BSTR bstrData = strUrl.AllocSysString();

	m_prtWebView->ShowWebView(bstrData, &bResult);

	SysFreeString(bstrData);

	return 0L;
}

// �ٷκ�������
LRESULT CTreatCalcDlg::OnLoadWebPage3(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL bResult = FALSE;
	CString strUrl = _T("http://total.kcomwel.or.kr/main.do");
	BSTR bstrData = strUrl.AllocSysString();

	m_prtWebView->ShowWebView(bstrData, &bResult);

	SysFreeString(bstrData);

	return 0L;
}

// KTEDI
LRESULT CTreatCalcDlg::OnLoadWebPage4(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL bResult = FALSE;
	CString strUrl = _T("https://web.ktedi.com/");
	BSTR bstrData = strUrl.AllocSysString();

	m_prtWebView->ShowWebView(bstrData, &bResult);

	SysFreeString(bstrData);

	return 0L;
}

void CTreatCalcDlg::InitDllResiter()
{
	TCHAR szSubKey[MAX_PATH];
	TCHAR szPath[4096];

	Elem entries[]
	{
		{ _T("TreatBasicSuga.dll") },
		{ _T("TreatConsult.dll") },
		{ _T("TreatWebView.dll") },
		{ _T("TreatWrapper.dll") }
	};

	ZeroMemory(szSubKey, sizeof(szSubKey));
	ZeroMemory(szPath, sizeof(szSubKey));

	::GetModuleFileName(NULL, szPath, sizeof(szPath));
	::PathRemoveFileSpec(szPath);
	::PathAppend(szPath, szSubKey);

	
	for (int nIdx = 0; nIdx < 4; nIdx++)
	{
		CString strData;
		strData.Format(_T("%s\\%s"), szPath, entries[nIdx]);
		HINSTANCE hLib = LoadLibrary(strData);
		if (hLib >= (HINSTANCE)HINSTANCE_ERROR)
		{
			FARPROC lpDllEntry = GetProcAddress(hLib, _T("DllUnregisterServer"));

			if (lpDllEntry != NULL)
			{
				(*lpDllEntry)();
				lpDllEntry = NULL;
			}

			lpDllEntry = GetProcAddress(hLib, _T("DllRegisterServer"));

			if (lpDllEntry != NULL)
			{
				(*lpDllEntry)();
				FreeLibrary(hLib);
			}
			else
			{
				CString strMsg;
				strMsg.Format(_T("%s Dll���� �����Դϴ�.���������Ϳ� ���� �ٶ��ϴ�."), entries[nIdx]);
				MessageBox(strMsg, _T("����"));
			}
		}
	}
}

void CTreatCalcDlg::LoadWindowText()
{
	long	lHospDiv = 0;
	BSTR	bstrStandDate;
	CString strStandDate;

	Elem entries[]
	{
		{ _T("�ǿ�") },
		{ _T("�����õ�") },
		{ _T("��������") },
		{ _T("���պ����õ�") },
		{ _T("���պ�������") }
	};

	m_prtBasicSugaView->GetTreatEnvData(&lHospDiv, &bstrStandDate);

	USES_CONVERSION;
	strStandDate = OLE2CT(bstrStandDate);
	SysFreeString(bstrStandDate);

	CString strTemp;
	strTemp.Format(_T("���������(����:%s, ���ؽ���:%s)"), entries[lHospDiv], strStandDate);

	::SetWindowText(m_hWnd, strTemp);
}

LRESULT CTreatCalcDlg::OnBasicSugaView(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	VARIANT_BOOL bRet = FALSE;
	bRet = m_prtBasicSugaView->ShowBasicView();
	
	// ������ ĸ���� �����ϱ� �����Լ�.
	LoadWindowText();

	// ���ʼ��� XML �ٽ� �ε��ϱ� ���� �Լ�
	m_prtWrapper->CreateModule(m_obDbConn.GetUnknown());

	// ���ʼ��� �������� ���ؼ� ȭ�鰻��
	m_ptrConsultTreat->RefleshEnvData();

	return 0L;
}

void CTreatCalcDlg::InitializeAttach()
{
	m_wndPageTab.Attach(GetDlgItem(IDC_PAGE_TAB));
	m_btnBasicSuga.Attach(GetDlgItem(IDC_BTN_SUGA_SETTING));
	m_btnWebView.Attach(GetDlgItem(IDC_BTN_WEBVIEW));
}

void CTreatCalcDlg::InitializeControl()
{
	m_wndPageTab.SetMinTabWidth(120);
	m_wndPageTab.SetItemSize(CSize(0, 20));
	
	// page tab ����
	static LPCTSTR ppszText[] =
	{
		_T("��������")
		//_T("�������"),
		//_T("������")
	};
	for (int nIdx = 0; nIdx<(sizeof(ppszText) / sizeof(LPCTSTR)); ++nIdx)
	{
		TCITEM tci;
		tci.mask = TCIF_TEXT;
		tci.pszText = (LPTSTR)ppszText[nIdx];
		tci.cchTextMax = _tcslen(tci.pszText);
		m_wndPageTab.InsertItem(nIdx, &tci);
	}
}

void CTreatCalcDlg::InitializeDB()
{
	if (m_obDbConn.m_pobConnection == NULL)
		m_obDbConn.m_pobConnection.CoCreateInstance(__uuidof(Connection));

	if (!m_obDbConn.IsOpen())
		m_obDbConn.Open(SQLConn, _T("sa"), _T("osstem"), adConnectUnspecified);
}


void CTreatCalcDlg::InitializeInterface()
{
	CoInitialize(NULL);

	if (FAILED(m_prtWrapper.CoCreateInstance(__uuidof(TreatWrapperInterface))))
		MessageBox(_T("�ý��ۿ� TreatWrapper.dll�� ���������� ��ϵ��� �ʾҽ��ϴ�."), _T("Ȯ��"), MB_ICONSTOP);

	if (FAILED(m_ptrConsultTreat.CoCreateInstance(__uuidof(TreatConsultInterface))))
		MessageBox(_T("�ý��ۿ� TreatConsult.dll�� ���������� ��ϵ��� �ʾҽ��ϴ�."), _T("Ȯ��"), MB_ICONSTOP);


	if (FAILED(m_prtWebView.CoCreateInstance(__uuidof(TreatHtmlModule))))
		MessageBox(_T("�ý��ۿ� TreatWebView.dll�� ���������� ��ϵ��� �ʾҽ��ϴ�."), _T("Ȯ��"), MB_ICONSTOP);

	if (FAILED(m_prtBasicSugaView.CoCreateInstance(__uuidof(TreatBasicViewModule))))
		MessageBox(_T("�ý��ۿ� TreatBasicSuga.dll�� ���������� ��ϵ��� �ʾҽ��ϴ�."), _T("Ȯ��"), MB_ICONSTOP);

	CRect rc;
	m_wndPageTab.GetClientRect(&rc);
	m_wndPageTab.AdjustRect(FALSE, &rc);

	m_prtWrapper->CreateModule(m_obDbConn.GetUnknown());
	m_ptrConsultTreat->CreateModule(m_obDbConn.GetUnknown(), reinterpret_cast<long>(m_wndPageTab.m_hWnd), rc.left, rc.top, rc.right, rc.bottom);

	CoUninitialize();
}

void CTreatCalcDlg::DestroyDetach()
{
	m_wndPageTab.Detach();
	m_btnBasicSuga.Detach();
	m_btnWebView.Detach();
}

void CTreatCalcDlg::DestroyDB()
{
	if (m_obDbConn.IsOpen())
		m_obDbConn.Close();
}

void CTreatCalcDlg::DestroyInterface()
{
	if (m_ptrConsultTreat)
		m_ptrConsultTreat.Release();

	if (m_prtWrapper)
		m_prtWrapper.Release();

	if (m_prtWebView)
		m_prtWebView.Release();

	if (m_prtBasicSugaView)
		m_prtBasicSugaView.Release();
}

void CTreatCalcDlg::ShowChildWindow(int nIdx)
{
	switch (nIdx)
	{
		case DEF_CONSULT_DIALOG:
			m_ptrConsultTreat->Show(VARIANT_TRUE);
		break;
		case DEF_CALCULATE_DIALOG:
			m_ptrConsultTreat->Show(VARIANT_FALSE);
		break;
		case DEF_BASIC_DIALOG:
			m_ptrConsultTreat->Show(VARIANT_FALSE);
		break;
	}
}

LRESULT CTreatCalcDlg::OnPageTabSelChange(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
{
	int nIdx = WM_USER + 1;

	ShowChildWindow(nIdx + m_wndPageTab.GetCurSel());
	
	return 0;
}