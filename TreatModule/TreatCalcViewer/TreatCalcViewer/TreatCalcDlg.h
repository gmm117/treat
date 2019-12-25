// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#pragma once
#ifndef __TREATCALC_DIALOG__
#define __TREATCALC_DIALOG__

#include "ADO.h"
#define SQLConn TEXT("Provider=SQLOLEDB.1;Persist Security Info=False;Initial Catalog=Hanaro;Data Source=(local)")

#define	DEF_CONSULT_DIALOG		WM_USER + 1
#define	DEF_CALCULATE_DIALOG	WM_USER + 2	
#define	DEF_BASIC_DIALOG		WM_USER + 3	

class CTreatCalcDlg : public CDialogImpl<CTreatCalcDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP(CTreatCalcDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

		COMMAND_ID_HANDLER(IDC_BTN_WEBVIEW, OnWebView)
		COMMAND_ID_HANDLER(IDC_BTN_SUGA_SETTING, OnBasicSugaView)
		
		COMMAND_ID_HANDLER(IDC_WEBPAGE_1, OnLoadWebPage1)
		COMMAND_ID_HANDLER(IDC_WEBPAGE_2, OnLoadWebPage2)
		COMMAND_ID_HANDLER(IDC_WEBPAGE_3, OnLoadWebPage3)
		COMMAND_ID_HANDLER(IDC_WEBPAGE_4, OnLoadWebPage4)

		NOTIFY_HANDLER(IDC_PAGE_TAB, TCN_SELCHANGE, OnPageTabSelChange)

		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	//////////////////////////////////////////////////////////////////////////////////
	// 생성자 소멸자																	//
	//////////////////////////////////////////////////////////////////////////////////
public:
	CTreatCalcDlg();
	virtual ~CTreatCalcDlg();

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Message Handler																//
	//////////////////////////////////////////////////////////////////////////////////
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPageTabSelChange(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
	LRESULT OnWebView(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBasicSugaView(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	
	LRESULT OnLoadWebPage1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnLoadWebPage2(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnLoadWebPage3(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnLoadWebPage4(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Function																//
	//////////////////////////////////////////////////////////////////////////////////
	void	InitializeAttach();
	void	InitializeControl();
	void	InitializeConsult();
	void	InitializeCharge();
	void	InitializeFormula();
	void	InitializeDB();
	void	InitializeInterface();
	void	InitDllResiter();

	void	ShowChildWindow(int nIdx);

	void	DestroyDetach();
	void	DestroyDB();
	void	DestroyInterface();

	void	LoadWindowText();

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Controls																		//
	//////////////////////////////////////////////////////////////////////////////////
	CTabCtrl m_wndPageTab;
	CButton  m_btnBasicSuga;
	CButton  m_btnWebView;

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Values																//
	//////////////////////////////////////////////////////////////////////////////////
	CComPtr<ITreatConsultInterface> m_ptrConsultTreat;	// 진찰료계산
	CComPtr<ITreatHtmlModule>		m_prtWebView;		// HTML Viewer
	CComPtr<ITreatBasicViewModule>	m_prtBasicSugaView;	// 기초수가View
	CComPtr<ITreatWrapperInterface> m_prtWrapper;

	CADOConnection		m_obDbConn;

	struct Elem
	{
		CString strName;
	};

};

#endif // __TREATCALC_DIALOG__