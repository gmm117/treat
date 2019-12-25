// TreatBasicViewDlg.h : Declaration of the CTreatBasicViewDlg

#pragma once

#ifndef __TREAT_BASICVIEW_DIALOG__
#define __TREAT_BASICVIEW_DIALOG__

#include "resource.h"       // main symbols

#include <atlhost.h>

#define IDC_LIST_BASIC_SUGA	WM_USER+1

using namespace ATL;

class CTreatBasicViewDlg : public CDialogImpl<CTreatBasicViewDlg>
{
public:
	CTreatBasicViewDlg();
	~CTreatBasicViewDlg();

public:
	//////////////////////////////////////////////////////////////////////////////////
	//								enumerations									//
	//////////////////////////////////////////////////////////////////////////////////
	enum { IDD = IDD_TREATBASICVIEWDLG };

public:
	//////////////////////////////////////////////////////////////////////////////////
	//								MESSAGE MAP										//
	//////////////////////////////////////////////////////////////////////////////////
BEGIN_MSG_MAP(CTreatBasicViewDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	

	NOTIFY_HANDLER(IDC_LIST_BASIC_SUGA, NM_DBLCLK, OnListDblClk)
	COMMAND_HANDLER(IDC_COMBO_HOSPDIV, CBN_SELCHANGE, OnChangeHospDiv)
	COMMAND_HANDLER(IDC_COMBO_STANDDATE, CBN_SELCHANGE, OnChangeStanddate)
	COMMAND_ID_HANDLER(IDC_BTN_SAVE, OnSave)

	REFLECT_NOTIFICATIONS()
END_MSG_MAP()

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Message Handler																//
	//////////////////////////////////////////////////////////////////////////////////
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnChangeHospDiv(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnChangeStanddate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnListDblClk(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/);
	LRESULT OnSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Mamber Function																//
	//////////////////////////////////////////////////////////////////////////////////
	void	InitializeAttach();
	void	InitializeControl();
	void	InitializeDB();
	bool	InitializeXML();

	void	LoadBasicSuga(long lIdx, CString strStandDate);
	void	SetListData(long lRow, long lCol, CString strData);

	void	DestroyDB();
	void	DestroyControl();
	void	DestroyDetach();

	CString GetStandDate();
	long	GetHospDiv();
	void	GetTreatEnvData(long& lHospDiv, CString& strStandDat);


private:
	//////////////////////////////////////////////////////////////////////////////////
	// Mamber Controls																//
	//////////////////////////////////////////////////////////////////////////////////
	CListViewCtrl	m_wndBasicList;		// 기초수가 List
	CComboBox		m_cboStandDate;		// 기준시점 수가
	CComboBox		m_cboHospDiv;		// 병원구분
	CButton			m_btnSave;			// 저장

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Mamber Values																//
	//////////////////////////////////////////////////////////////////////////////////
	std::vector<_S_BASIC_SUGA> m_vecBasicSugaParser;
	long			m_lHospDiv;
	CString			m_strStandDate;

private:
	struct Elem
	{
		CString strName;
	};

};

#endif // __TREAT_BASICVIEW_DIALOG__