// TreatWebViewDlg.cpp : Implementation of CTreatWebViewDlg

#include "stdafx.h"
#include "TreatWebViewDlg.h"
#include <Wininet.h>	// for InternetSetCookie function

#pragma comment (lib, "Wininet.lib")

// CTreatWebViewDlg
CTreatWebViewDlg::CTreatWebViewDlg(CString strUrl) : m_strUrl(strUrl)
{
}


CTreatWebViewDlg::~CTreatWebViewDlg()
{
}

LRESULT CTreatWebViewDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_spWebBrowser)
	{
		HRESULT hr = DispEventAdvise(m_spWebBrowser, &DIID_DWebBrowserEvents2);
		ATLASSERT(FAILED(hr));
	}

	InitializeControl();

	return TRUE;  // Let the system set the focus
}

LRESULT CTreatWebViewDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_spWebBrowser)
	{
		HRESULT hr = DispEventUnadvise(m_spWebBrowser);
		ATLASSERT(FAILED(hr));
	}

	if (m_wndBrowser.IsWindow())
		m_wndBrowser.DestroyWindow();

	return TRUE;
}

LRESULT CTreatWebViewDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndDialog(IDOK);

	return 0;
}

void CTreatWebViewDlg::InitializeAttach()
{

}

void CTreatWebViewDlg::DestroyeDetach()
{

}

void CTreatWebViewDlg::InitializeControl()
{
	HRESULT hr;
	AtlAxWinInit();

	try
	{
		m_wndBrowser.Create(m_hWnd, GetWebBrowserRect(), m_strUrl, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL, WS_EX_CLIENTEDGE, IDW_BROWSER);
		m_wndBrowser.QueryControl(IID_IWebBrowser2, (void**)&m_spWebBrowser);
	}
	catch (...)
	{
		MessageBox(_T("Internet Explorer 6.0 이상을 설치해주세요."), _T("오류"), MB_OK | MB_ICONINFORMATION);
	}
}

void CTreatWebViewDlg::NavigateComplete2(/*[in]*/ IDispatch* pDisp, /*[in]*/ VARIANT* URL)
{
	USES_CONVERSION;
	if (URL->vt == VT_BSTR)
	{
		LPCTSTR lpszUrl = OLE2CT(URL->bstrVal);
		CString strUrl = lpszUrl;
		if (strUrl.Find(_T("#close")) != -1)
		{
			DestroyWindow();
			PostQuitMessage(0);
			return;
		}
	}

	SetWindowPos(HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void CTreatWebViewDlg::NavigateError(/*[in]*/ IDispatch* pDisp, /*[in]*/ VARIANT* URL, /*[in]*/ VARIANT* Frame, /*[in]*/ VARIANT* StatusCode, /*[in, out]*/ VARIANT_BOOL* Cancel)
{

}

void CTreatWebViewDlg::WindowClosing(/*[in]*/ VARIANT_BOOL IsChildWindow, /*[in, out]*/ VARIANT_BOOL* Cancel)
{
	EndDialog(IDOK);
}


CRect CTreatWebViewDlg::GetWebBrowserRect()
{
	CRect rcRect;

	GetClientRect(&rcRect);

	return rcRect;
}