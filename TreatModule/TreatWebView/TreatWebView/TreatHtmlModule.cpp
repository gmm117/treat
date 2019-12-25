// TreatHtmlModule.cpp : Implementation of CTreatHtmlModule

#include "stdafx.h"
#include "TreatHtmlModule.h"
#include "TreatWebViewDlg.h"

// CTreatHtmlModule

STDMETHODIMP CTreatHtmlModule::ShowWebView(BSTR pbstrData, VARIANT_BOOL* vbResult)
{
	// TODO: Add your implementation code here

	USES_CONVERSION;
	CString strUrl = OLE2CT(pbstrData);

	CTreatWebViewDlg wndWebDlg(strUrl);
	wndWebDlg.DoModal();

	return S_OK;
}


STDMETHODIMP CTreatHtmlModule::ChildDestroy()
{
	// TODO: Add your implementation code here

	return S_OK;
}
