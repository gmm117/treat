#include "stdafx.h"
#include "TreatFixDlg.h"


CTreatFixDlg::CTreatFixDlg(long lIdx) : m_strData(_T("")), m_lIdx(lIdx)
{
	
	
}

CTreatFixDlg::~CTreatFixDlg()
{

}

LRESULT CTreatFixDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// Initialize Control Attach
	InitializeAttach();

	// Windows Control Init
	InitializeControl();

	return TRUE;
}

LRESULT CTreatFixDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Destroy Control
	DestroyControl();

	// Destroy Control Detach
	DestroyDetach();

	return TRUE;
}

LRESULT CTreatFixDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndDialog(IDOK);
	return 0;
}

LRESULT CTreatFixDlg::OnSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	TCHAR szBuff[2048];
	ZeroMemory(szBuff, sizeof(szBuff));

	m_editContent.GetWindowText(szBuff, 2048);

	m_strData = szBuff;

	if (!m_strData.IsEmpty())
		EndDialog(IDCANCEL);

	return 0L;
}

void CTreatFixDlg::InitializeAttach()
{
	m_editContent.Attach(GetDlgItem(IDC_EDIT_CONTENT));
	m_btnSave.Attach(GetDlgItem(IDC_BTN_SAVE));
}

void CTreatFixDlg::DestroyDetach()
{
	m_editContent.Detach();
	m_btnSave.Detach();
}

CString	CTreatFixDlg::GetData()
{
	return m_strData;
}

void CTreatFixDlg::InitializeControl()
{
	CString strTemp;
	strTemp.Format(_T("기초수가 %d 변경"), m_lIdx);
	SetWindowText(strTemp);
}

void CTreatFixDlg::DestroyControl()
{

}