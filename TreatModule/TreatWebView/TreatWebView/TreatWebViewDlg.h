// TreatWebViewDlg.h : Declaration of the CTreatWebViewDlg

#pragma once
#ifndef __TREAT_WEBVIEW_DIALOG__
#define __TREAT_WEBVIEW_DIALOG__

#include "stdafx.h"
#include "resource.h"       // main symbols


using namespace ATL;

class CTreatWebViewDlg : 
	public CDialogImpl<CTreatWebViewDlg>,
	public IDispEventImpl<IDC_WEBBROWSER, CTreatWebViewDlg, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 0>
{
public:
	CTreatWebViewDlg(CString strUrl);
	virtual ~CTreatWebViewDlg();

	//////////////////////////////////////////////////////////////////////////////////
	//								enumerations									//
	//////////////////////////////////////////////////////////////////////////////////
	enum { IDD = IDD_TREATWEBVIEWDLG };

	//////////////////////////////////////////////////////////////////////////////////
	//								MESSAGE MAP										//
	//////////////////////////////////////////////////////////////////////////////////
BEGIN_MSG_MAP(CTreatWebViewDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)

	REFLECT_NOTIFICATIONS()
END_MSG_MAP()

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Message Handler																//
	//////////////////////////////////////////////////////////////////////////////////
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Controls																		//
	//////////////////////////////////////////////////////////////////////////////////

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Function																//
	//////////////////////////////////////////////////////////////////////////////////
	void InitializeAttach();
	void DestroyeDetach();
	void InitializeControl();

	CRect GetWebBrowserRect();

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Values																//
	//////////////////////////////////////////////////////////////////////////////////
	CComQIPtr<IWebBrowser2, &IID_IWebBrowser2>				m_spWebBrowser;
	CAxWindow	m_wndBrowser;
	CString		m_strUrl;


	//////////////////////////////////////////////////////////////////////////////////
	// Member EventSink																//
	//////////////////////////////////////////////////////////////////////////////////
public:
	BEGIN_SINK_MAP(CTreatWebViewDlg)
		SINK_ENTRY_EX(IDC_WEBBROWSER, DIID_DWebBrowserEvents2, 0x000000fc, NavigateComplete2)
		SINK_ENTRY_EX(IDC_WEBBROWSER, DIID_DWebBrowserEvents2, 0x0000010f, NavigateError)
		SINK_ENTRY_EX(IDC_WEBBROWSER, DIID_DWebBrowserEvents2, 0x00000107, WindowClosing)
	END_SINK_MAP()

	void __stdcall NavigateComplete2(/*[in]*/ IDispatch* pDisp, /*[in]*/ VARIANT* URL);
	void __stdcall NavigateError(/*[in]*/ IDispatch* pDisp, /*[in]*/ VARIANT* URL, /*[in]*/ VARIANT* Frame, /*[in]*/ VARIANT* StatusCode, /*[in, out]*/ VARIANT_BOOL* Cancel);
	void __stdcall WindowClosing(/*[in]*/ VARIANT_BOOL IsChildWindow, /*[in, out]*/ VARIANT_BOOL* Cancel);


};
#endif //__TREAT_WEBVIEW_DIALOG__
