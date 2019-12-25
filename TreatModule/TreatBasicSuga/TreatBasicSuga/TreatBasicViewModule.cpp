// TreatBasicViewModule.cpp : Implementation of CTreatBasicViewModule

#include "stdafx.h"
#include "TreatBasicViewModule.h"
#include "TreatBasicViewDlg.h"

// CTreatBasicViewModule



STDMETHODIMP CTreatBasicViewModule::ShowBasicView(VARIANT_BOOL* vbResult)
{
	// TODO: Add your implementation code here

	CTreatBasicViewDlg wndBasicViewDlg;

	wndBasicViewDlg.DoModal();

	wndBasicViewDlg.GetTreatEnvData(m_lHospDiv, m_strStandDate);

	return S_OK;
}


STDMETHODIMP CTreatBasicViewModule::ChildDestroy()
{
	// TODO: Add your implementation code here

	// 추후구현

	return S_OK;
}


STDMETHODIMP CTreatBasicViewModule::GetTreatEnvData(LONG* plHospDiv, BSTR* pbstrStandDate)
{
	// TODO: Add your implementation code here

	*plHospDiv = m_lHospDiv;

	*pbstrStandDate = m_strStandDate.AllocSysString();


	return S_OK;
}
