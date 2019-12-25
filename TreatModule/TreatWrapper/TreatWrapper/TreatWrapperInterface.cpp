// TreatWrapperInterface.cpp : Implementation of CTreatWrapperInterface

#include "stdafx.h"
#include "TreatWrapperInterface.h"


// CTreatWrapperInterface

CTreatWrapperInterface::CTreatWrapperInterface()
{

}

CTreatWrapperInterface::~CTreatWrapperInterface()
{

}

STDMETHODIMP CTreatWrapperInterface::CreateModule(IUnknown* pUnkn)
{
	// TODO: Add your implementation code here

	InitializeXML();

	return S_OK;
}

STDMETHODIMP CTreatWrapperInterface::ChildDestroy()
{
	// TODO: Add your implementation code here

	return S_OK;
}


LRESULT CTreatWrapperInterface::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CTreatWrapperInterface::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	return 0;
}

bool CTreatWrapperInterface::InitializeXML()
{
	// XML 파일로딩(타입에 맞게)
	if (!CXmlBasicSugaParser::Instance().LoadXmlData())
		return false;

	// XML 파일로딩(타입에 맞게)
	if (!CXmlBasicControlParser::Instance().LoadXmlData())
		return false;

	return true;
}

STDMETHODIMP CTreatWrapperInterface::LoadBasicSuga(long lHospDiv, BSTR bstrStandDate, BSTR* pvarCode, BSTR* pvarName, BSTR* pvarCost, short nCount, VARIANT_BOOL* pResult)
{
	// TODO: Add your implementation code here
	std::vector<_S_BASIC_SUGA> vecBasicSugaParser;

	USES_CONVERSION;
	CString strStandDate = OLE2CT(bstrStandDate);

	vecBasicSugaParser = CXmlBasicSugaParser::Instance().GetSequenceData(lHospDiv, strStandDate);

	for (int nIdx = 0; nIdx < nCount; nIdx++)
	{
		pvarCode[nIdx] = vecBasicSugaParser[nIdx].strCode.AllocSysString();
		pvarName[nIdx] = vecBasicSugaParser[nIdx].strName.AllocSysString();
		pvarCost[nIdx] = vecBasicSugaParser[nIdx].strCost.AllocSysString();
	}

	return S_OK;
}


STDMETHODIMP CTreatWrapperInterface::GetStandDate(long lHospDiv, BSTR* pbstrStandDate)
{
	// TODO: Add your implementation code here
	CString strStandDate;

	if (!CXmlBasicSugaParser::Instance().GetStandDate(lHospDiv, strStandDate))
		return S_FALSE;

	*pbstrStandDate = strStandDate.AllocSysString();

	return S_OK;
}


STDMETHODIMP CTreatWrapperInterface::GetTotalBasicContSize(long* plDataSize)
{
	// TODO: Add your implementation code here

	*plDataSize = CXmlBasicControlParser::Instance().GetTotalBasicContSize();

	return S_OK;
}


STDMETHODIMP CTreatWrapperInterface::GetCurControlSize(long lContIdx, long* plCurSize)
{
	// TODO: Add your implementation code here

	*plCurSize = CXmlBasicControlParser::Instance().GetCurControlSize(lContIdx);

	return S_OK;
}


STDMETHODIMP CTreatWrapperInterface::GetCurData(long lContIdx, BSTR* pbstrData)
{
	// TODO: Add your implementation code here
	_S_BASIC_CONTINFO struBasicContInfo;

	struBasicContInfo = CXmlBasicControlParser::Instance().GetSequenceData(lContIdx);

	pbstrData[0] = struBasicContInfo.strFormula.AllocSysString();
	pbstrData[1] = struBasicContInfo.strHisCost.AllocSysString();

	for (int nIdx = 2; nIdx < struBasicContInfo.vecData.size() + 2; nIdx++)
	{
		pbstrData[nIdx] = struBasicContInfo.vecData[nIdx-2].AllocSysString();
	}

	return S_OK;
}


STDMETHODIMP CTreatWrapperInterface::GetCurContRect(long lContIdx, long* plLeft, long* plTop, long* plRight, long* plBottom)
{
	// TODO: Add your implementation code here

	_S_BASIC_CONTINFO struBasicContInfo;

	struBasicContInfo = CXmlBasicControlParser::Instance().GetSequenceData(lContIdx);

	*plLeft =  struBasicContInfo.rcRect.left;
	*plTop = struBasicContInfo.rcRect.top;
	*plRight = struBasicContInfo.rcRect.right;
	*plBottom = struBasicContInfo.rcRect.bottom;

	return S_OK;
}


STDMETHODIMP CTreatWrapperInterface::GetCurContStatic(long lContIdx, BSTR* pbstrData)
{
	// TODO: Add your implementation code here
	CString strStName = CXmlBasicControlParser::Instance().GetCurStaticData(lContIdx);

	*pbstrData = strStName.AllocSysString();

	return S_OK;
}



STDMETHODIMP CTreatWrapperInterface::GetCurCode(long lContIdx, BSTR* pbstrData)
{
	// TODO: Add your implementation code here

	_S_BASIC_CONTINFO struBasicContInfo;

	struBasicContInfo = CXmlBasicControlParser::Instance().GetSequenceData(lContIdx);

	for (int nIdx = 0; nIdx < struBasicContInfo.vecCode.size(); nIdx++)
	{ 
		pbstrData[nIdx] = struBasicContInfo.vecCode[nIdx].AllocSysString();
	}

	return S_OK;
}
