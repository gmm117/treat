// WebBrowser.h: interface for the CWebBrowser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEBBROWSER_H__6DCBE2EC_3738_4058_999E_E8706500A313__INCLUDED_)
#define AFX_WEBBROWSER_H__6DCBE2EC_3738_4058_999E_E8706500A313__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0200

/********************************************************************************
			Micrsoft Web Browser Control의 Wrapper Class이다.
			간단한 Web Brosing의 기능을 지원한다.
********************************************************************************/

#include <atlbase.h>
#include <atlapp.h>				// for atlmisc.h
#include <atlwin.h>				// for CAxWindow
#include <atlcom.h>				// for atlhost.h
#include <atlhost.h>			// for AtlAxCreateControl function
#include <atlmisc.h>			// for CString

#define		ID_WEBBROWSER		2020



// Windows Version에 따라 Import를 달리 해야함
// 먼저 (Hanaro 소스폴더)\include\typelibrary\TypeLibrary\shdocvw.dll을 받으시오.
#import		<shdocvw.dll>	raw_interfaces_only, raw_native_types, rename_namespace(_T("IE")), named_guids, no_auto_exclude


/////////////////////////////////////////////////////////////////////////////////
// CWebBroser
class CWebBrowser
{
// Constructor
public:
	CWebBrowser()
	{
		m_hWnd = NULL;
	}

	virtual ~CWebBrowser()
	{
	}


// Attributes
protected:
	CAxWindow		m_wndWebBrowserContainer;


public:
	HWND			m_hWnd;


// Operations
public:
	virtual BOOL Create(HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName=NULL, DWORD dwStyle=0, DWORD dwExStyle=0, UINT nID=0, LPVOID lpCreateParam=NULL)
	{
		// Initializes the AxWin hosting code
		if( !AtlAxWinInit() )
		{
			ATLASSERT(FALSE);
			::MessageBox(NULL, _T("AxWin Hosting Code를 초기화 하는데 실패하였습니다."), _T("오류"), MB_ICONSTOP);
		}


		// ActiveX 윈도우를 생성한다
		HWND hWnd = m_wndWebBrowserContainer.Create(hWndParent, rcPos, _T("Shell.Explorer.2"), dwStyle, dwExStyle, nID, lpCreateParam);
		if(::IsWindow(hWnd) == FALSE)
		{
			ATLASSERT(FALSE);
			AtlAxWinTerm();
			::MessageBox(NULL, _T("Micrsoft 웹 브라우저 ActiveX를 생성하는데 실패하였습니다."), _T("오류"), MB_ICONSTOP);
			return FALSE;
		}

		m_hWnd = m_wndWebBrowserContainer.m_hWnd;

		return TRUE;
	}

	virtual void DestroyWindow()
	{
		// 윈도우를 파괴한다
		if(m_wndWebBrowserContainer.IsWindow())
			m_wndWebBrowserContainer.DestroyWindow();


		m_hWnd = NULL;


		// Unnitializes the AxWin hosting code
		AtlAxWinTerm();
	}

	virtual BOOL IsWindow()
	{
		return ::IsWindow(m_hWnd);
	}

	virtual BOOL MoveWindow(LPRECT lpRect, BOOL bRepaint=TRUE)
	{
		return MoveWindow(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);
	}

	virtual BOOL MoveWindow(int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint=TRUE)
	{
		return ::MoveWindow(m_hWnd, nLeft, nTop, nWidth, nHeight, bRepaint);
	}

	virtual BOOL ShowWindow(int nCmdShow)
	{
		return m_wndWebBrowserContainer.ShowWindow(nCmdShow);
	}

	virtual HRESULT GetInterface(IUnknown** ppUnkn)
	{
		return m_wndWebBrowserContainer.QueryControl(ppUnkn);
	}

	virtual HWND GetHWnd()
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		HRESULT hr = m_wndWebBrowserContainer.QueryControl(&pWebBrowser);
		ATLASSERT(SUCCEEDED(hr));
		if(SUCCEEDED(hr))
		{
			long lHWnd;
			hr = pWebBrowser->get_HWND(&lHWnd);
			ATLASSERT(SUCCEEDED(hr));
			if(SUCCEEDED(hr))
				return reinterpret_cast<HWND>(lHWnd);
			else
				return NULL;
		}
		else
		{
			return NULL;
		}
	}

	virtual BOOL Navigate(LPCTSTR lpszUrl, DWORD dwFlags = 0, LPCTSTR lpszTargetFrameName = NULL, LPCTSTR lpszHeaders = NULL, LPVOID lpvPostData = NULL, DWORD dwPostDataLen = 0)
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		if( SUCCEEDED(m_wndWebBrowserContainer.QueryControl(&pWebBrowser)) )
			return SUCCEEDED(pWebBrowser->Navigate(_bstr_t(lpszUrl), &vtMissing, &vtMissing, &vtMissing, &vtMissing));
		return FALSE;
	}

	virtual void Refresh()
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		HRESULT hr = m_wndWebBrowserContainer.QueryControl(&pWebBrowser);
		if(SUCCEEDED(hr))
		{
			hr = pWebBrowser->Refresh();
			ATLASSERT(SUCCEEDED(hr));
		}
	}

	virtual void GoBack()
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		HRESULT hr = m_wndWebBrowserContainer.QueryControl(&pWebBrowser);
		if(SUCCEEDED(hr))
		{
			hr = pWebBrowser->GoBack();
			ATLASSERT(SUCCEEDED(hr));
		}
	}

	virtual void GoForward()
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		HRESULT hr = m_wndWebBrowserContainer.QueryControl(&pWebBrowser);
		if(SUCCEEDED(hr))
		{
			hr = pWebBrowser->GoForward();
			ATLASSERT(SUCCEEDED(hr));
		}
	}

	virtual void GoHome()
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		HRESULT hr = m_wndWebBrowserContainer.QueryControl(&pWebBrowser);
		if(SUCCEEDED(hr))
		{
			hr = pWebBrowser->GoHome();
			ATLASSERT(SUCCEEDED(hr));
		}
	}

	virtual void Stop()
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		HRESULT hr = m_wndWebBrowserContainer.QueryControl(&pWebBrowser);
		if(SUCCEEDED(hr))
		{
			hr = pWebBrowser->Stop();
			ATLASSERT(SUCCEEDED(hr));
		}
	}

	virtual READYSTATE GetReadyState()
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		HRESULT hr = m_wndWebBrowserContainer.QueryControl(&pWebBrowser);
		ATLASSERT(SUCCEEDED(hr));

		READYSTATE enReadyState = READYSTATE_UNINITIALIZED;

		if(SUCCEEDED(hr))
		{
			hr = pWebBrowser->get_ReadyState(&enReadyState);
			ATLASSERT(SUCCEEDED(hr));
		}

		return enReadyState;
	}

	virtual CString GetLocationUrl()
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		HRESULT hr = m_wndWebBrowserContainer.QueryControl(&pWebBrowser);
		ATLASSERT(SUCCEEDED(hr));

		CString strLocationUrl;

		if(SUCCEEDED(hr))
		{
			BSTR bstrUrl;
			hr = pWebBrowser->get_LocationURL(&bstrUrl);
			ATLASSERT(SUCCEEDED(hr));
			if(SUCCEEDED(hr))
			{
				USES_CONVERSION;
				strLocationUrl = OLE2CT(bstrUrl);
				::SysFreeString(bstrUrl);
			}
			else
				ATLASSERT(FALSE);
		}
		else
			ATLASSERT(FALSE);

		return strLocationUrl;
	}

	virtual CString GetLocationName()
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		HRESULT hr = m_wndWebBrowserContainer.QueryControl(&pWebBrowser);
		ATLASSERT(SUCCEEDED(hr));

		CString strLocationName;

		if(SUCCEEDED(hr))
		{
			BSTR bstrName;
			hr = pWebBrowser->get_LocationName(&bstrName);
			ATLASSERT(SUCCEEDED(hr));
			if(SUCCEEDED(hr))
			{
				USES_CONVERSION;
				strLocationName = OLE2CT(bstrName);
				::SysFreeString(bstrName);
			}
			else
				ATLASSERT(FALSE);
		}
		else
			ATLASSERT(FALSE);

		return strLocationName;
	}

	virtual CString GetPath()
	{
		CComPtr<IWebBrowser2> pWebBrowser;
		HRESULT hr = m_wndWebBrowserContainer.QueryControl(&pWebBrowser);
		ATLASSERT(SUCCEEDED(hr));

		CString strPath;

		if(SUCCEEDED(hr))
		{
			BSTR bstrPath;
			hr = pWebBrowser->get_LocationName(&bstrPath);
			ATLASSERT(SUCCEEDED(hr));
			if(SUCCEEDED(hr))
			{
				USES_CONVERSION;
				strPath = OLE2CT(bstrPath);
				::SysFreeString(bstrPath);
			}
			else
				ATLASSERT(FALSE);
		}
		else
			ATLASSERT(FALSE);

		return strPath;
	}
};


#endif // !defined(AFX_WEBBROWSER_H__6DCBE2EC_3738_4058_999E_E8706500A313__INCLUDED_)
