#ifndef __TREAT_FIX_DIALOG_H__
#define __TREAT_FIX_DIALOG_H__

#include "resource.h"       // main symbols
#include <atlhost.h>

using namespace ATL;

class CTreatFixDlg :
	public CAxDialogImpl<CTreatFixDlg>
{
public:
	CTreatFixDlg(long lIdx);
	~CTreatFixDlg();

public:
	//////////////////////////////////////////////////////////////////////////////////
	//								enumerations									//
	//////////////////////////////////////////////////////////////////////////////////
	enum { IDD = IDD_TREATFIXDLG };

public:
	//////////////////////////////////////////////////////////////////////////////////
	//								MESSAGE MAP										//
	//////////////////////////////////////////////////////////////////////////////////
	BEGIN_MSG_MAP(CTreatFixDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
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
	LRESULT OnSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Mamber Function																//
	//////////////////////////////////////////////////////////////////////////////////
	void	InitializeAttach();
	void	InitializeControl();

	void	DestroyControl();
	void	DestroyDetach();

	CString	GetData();

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Mamber Controls																//
	//////////////////////////////////////////////////////////////////////////////////
	CEdit	m_editContent;
	CButton m_btnSave;

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Mamber Values																//
	//////////////////////////////////////////////////////////////////////////////////
	CString			m_strData;
	long			m_lIdx;

};

#endif //_TREAT_FIX_DIALOG_H__