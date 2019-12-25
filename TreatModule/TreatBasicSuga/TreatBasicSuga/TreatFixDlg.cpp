// TreatFixDlg.cpp : Implementation of CTreatFixDlg

#include "stdafx.h"
#include "TreatFixDlg.h"


// CTreatFixDlg
CTreatFixDlg::CTreatFixDlg(CString strTitle) : m_strData(_T("")), m_strTitle(strTitle)
{

}

CTreatFixDlg::~CTreatFixDlg()
{

}

LRESULT CTreatFixDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// center the dialog on the screen
	CenterWindow();

	// Init Attach Control
	InitializeAttach();

	// Init Control
	InitializeControl();

	return TRUE;  
}

LRESULT CTreatFixDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	// Destroy Detach Control
	DestroyDetach();


	return TRUE;
}

LRESULT CTreatFixDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	EndDialog(IDOK);

	return TRUE;
}

LRESULT CTreatFixDlg::OnSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	TCHAR szBuff[254];

	m_editContent.GetWindowText(szBuff, 254);
	m_strData = szBuff;
	m_strData.TrimLeft(); m_strData.TrimRight();

	EndDialog(IDOK);

	return TRUE;
}

void CTreatFixDlg::InitializeAttach()
{
	m_stTitle.Attach(GetDlgItem(IDC_ST_TITLE));
	m_editContent.Attach(GetDlgItem(IDC_EDIT_CONTENT));
	m_btnSave.Attach(GetDlgItem(IDC_BTN_SAVE));

}
void CTreatFixDlg::InitializeControl()
{
	m_stTitle.SetWindowText(m_strTitle.GetBuffer(0));
	m_strTitle.ReleaseBuffer();
}

void CTreatFixDlg::DestroyControl()
{
	// 추후구현
}

void CTreatFixDlg::DestroyDetach()
{
	m_stTitle.Detach();
	m_editContent.Detach();
	m_btnSave.Detach();
}

CString CTreatFixDlg::GetContentData()
{
	return m_strData;
}

