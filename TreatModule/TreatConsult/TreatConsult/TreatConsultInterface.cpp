// TreatConsultInterface.cpp : Implementation of CTreatConsultInterface

#include "stdafx.h"
#include "TreatConsultInterface.h"
#include "CalcParser.h"
#include "TreatFixDlg.h"

// CTreatConsultInterface

CTreatConsultInterface::CTreatConsultInterface()
{

}

CTreatConsultInterface::~CTreatConsultInterface()
{

}

STDMETHODIMP CTreatConsultInterface::CreateModule(IUnknown* pUnkn, long lParentHwnd, long lLeft, long lTop, long lRight, long lBottom)
{
	// TODO: Add your implementation code here

	CDialogImpl<CTreatConsultInterface>::Create(reinterpret_cast<HWND>(lParentHwnd));
	if (!CDialogImpl<CTreatConsultInterface>::IsWindow())
		return E_FAIL;
	CDialogImpl<CTreatConsultInterface>::MoveWindow(CRect(lLeft, lTop, lRight, lBottom));

	m_obDbConn.Attach(pUnkn);

	// 진찰료 Edit,Static 컨트롤을 생성하는 함수
	CreatTreatControl();

	// ComboBox에 데이터를 로딩하는 함수.
	LoadComboHospDiv();

	// 기초수가를 vector에 저장하는 함수
	LoadBasicSuga();

	// Wrapper 클래스에 얻어온 자료를 vector에 저장하기 위한 함수.(계산식을 얻어옴)
	LoadTreatData();

	// Wrapper 클래스에 얻어온 자료를 vector에 저장하기 위한 함수.(계산식을 통해서 진료비를 계산함)
	CalcTreatData();

	return S_OK;
}


STDMETHODIMP CTreatConsultInterface::Show(VARIANT_BOOL bShow)
{
	// TODO: Add your implementation code here

	CDialogImpl<CTreatConsultInterface>::ShowWindow(bShow == VARIANT_TRUE ? SW_SHOW : SW_HIDE);

	// 기초수가 List에 추가하는 함수
	InsertBasicSugaList();

	// 환산지수를 EDITBOX에 세팅하는 함수
	SetJisuData();

	return S_OK;
}

STDMETHODIMP CTreatConsultInterface::ChildDestroy()
{
	// TODO: Add your implementation code here
	CDialogImpl<CTreatConsultInterface>::DestroyWindow();

	return S_OK;
}

STDMETHODIMP CTreatConsultInterface::RefleshEnvData()
{
	// TODO: Add your implementation code here

	// 기초수가를 vector에 저장하는 함수
	LoadBasicSuga();

	// 기초수가 List에 추가하는 함수
	InsertBasicSugaList();

	// 환산지수를 EDITBOX에 세팅하는 함수
	SetJisuData();

	// 좌표값,이름로딩하는 함수
	LoadTreatControl();

	// 진료비계산에 필요한 정보얻어오는 함수
	LoadTreatData();

	// Wrapper 클래스에 얻어온 자료를 vector에 저장하기 위한 함수.
	CalcTreatData();

	return S_OK;
}

LRESULT CTreatConsultInterface::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	InitializeAttach();

	InitializeControl();

	Hook();

	return TRUE;
}

LRESULT CTreatConsultInterface::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DestroyControl();
	
	DestroyDetach();

	UnHook();

	return TRUE;
}

LRESULT CTreatConsultInterface::OnChangeHospDiv(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	LoadComboHospDiv();

	// 기초수가를 vector에 저장하는 함수
	LoadBasicSuga();

	// 기초수가 List에 추가하는 함수
	InsertBasicSugaList();

	// 환산지수를 EDITBOX에 세팅하는 함수
	SetJisuData();

	// 좌표값, 이름로딩하는 함수
	LoadTreatControl();

	// 진료비계산에 필요한 정보얻어오는 함수
	LoadTreatData();

	// Wrapper 클래스에 얻어온 자료를 vector에 저장하기 위한 함수.
	CalcTreatData();

	return 0;
}

LRESULT CTreatConsultInterface::OnChangeStanddate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	// 기초수가를 vector에 저장하는 함수
	LoadBasicSuga();

	// 기초수가 List에 추가하는 함수
	InsertBasicSugaList();

	// 환산지수를 EDITBOX에 세팅하는 함수
	SetJisuData();

	// 좌표값,이름로딩하는 함수
	LoadTreatControl();

	// 진료비계산에 필요한 정보얻어오는 함수
	LoadTreatData();

	// Wrapper 클래스에 얻어온 자료를 vector에 저장하기 위한 함수.
	CalcTreatData();

	return 0;
}

LRESULT CTreatConsultInterface::OnListDblClk(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
{
	LPNMITEMACTIVATE pnmia = reinterpret_cast<LPNMITEMACTIVATE>(pnmh);

	if(pnmia->iItem != -1)
	{
		CHeaderCtrl& wndHeader = m_wndBasicList.GetHeader();

		CTreatFixDlg obFixDlg(pnmia->iItem);
		if (obFixDlg.DoModal() == IDCANCEL)
		{
			CString strData = obFixDlg.GetData();

			m_wndBasicList.SetItemText(pnmia->iItem, 2, obFixDlg.GetData());

			CCalcParser::Instance().m_vecBasicSuga[pnmia->iItem].strCost = obFixDlg.GetData();

			if (pnmia->iItem == 2 || pnmia->iItem == 64)
			{
				// 좌표값,이름로딩하는 함수
				LoadTreatControl();

				// 진료비계산에 필요한 정보얻어오는 함수
				LoadTreatData();
			}
			else if (pnmia->iItem == 0)
			{
				m_editJisu.SetWindowText(obFixDlg.GetData());
			}
			

			CalcTreatData();
		}
	}

	return 0;
}

BOOL CTreatConsultInterface::OnHook(const MSG* msg)
{
	switch (msg->message)
	{
		case WM_KEYDOWN:
		{
			if (GetDlgItem(IDC_EDIT_JISU) == GetFocus() && msg->wParam == VK_RETURN)
			{
				TCHAR szBuff[1024];
				m_editJisu.GetWindowText(szBuff, 1024);

				m_wndBasicList.SetItemText(0, 2, szBuff);
				CCalcParser::Instance().m_vecBasicSuga[0].strCost = szBuff;

				CalcTreatData();
			}
		}
			break;
		default:
			break;
	}
	return FALSE;
}


LRESULT CTreatConsultInterface::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;

	static bool bLock = false;
	if (bLock) return 0;
	bLock = true;

	LRESULT lResult = OnDefaultCommand(uMsg, wParam, lParam, bHandled);

	// unlock this handler
	bLock = false;
	return lResult;
}

LRESULT CTreatConsultInterface::OnDefaultCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT uCode = HIWORD(wParam);
	UINT uID = LOWORD(wParam);
	HWND hWnd = (HWND)lParam;

	int nIdx = uID - static_cast<int>(IDC_EDIT_BASIC_CONTROL);

	if (uCode == EN_SETFOCUS)
	{
		if (m_lTotSize > 0 && nIdx >= 0)
		{
			TCHAR szBuff[1024];
			m_peditContData[nIdx].GetWindowText(szBuff, 1024);

			m_editCalc.SetWindowText(CCalcParser::Instance().m_vecCurBasicData[nIdx].strFormula);
			m_editHisCost.SetWindowText(CCalcParser::Instance().CalcHisCost(szBuff, _ttoi(CCalcParser::Instance().m_vecCurBasicData[nIdx].strHisCost), CCalcParser::Instance().m_vecCurBasicData[nIdx].strSatCost, CCalcParser::Instance().m_vecCurBasicData[nIdx].strSatDiv));
			m_stCalcFormula.SetWindowText(CCalcParser::Instance().m_vecCurBasicData[nIdx].strStName + _T(" 계산식"));
			m_sleCode.SetWindowText(CCalcParser::Instance().m_vecCurBasicData[nIdx].vecCode[m_cboHospDiv.GetCurSel()]);
			m_editSatCost.SetWindowText(CCalcParser::Instance().m_vecCurBasicData[nIdx].strSatCost);
		}
	}
	else if (uCode == EN_KILLFOCUS)
	{
		m_editCalc.SetWindowText(_T(""));
		m_editHisCost.SetWindowText(_T(""));
		m_stCalcFormula.SetWindowText(_T("계산식"));
		m_sleCode.SetWindowText(_T(""));
		m_editSatCost.SetWindowText(_T(""));
	}

	return 0;
}

void CTreatConsultInterface::LoadTreatControl()
{
	long lLeft = 0;
	long lTop = 0;
	long lRight = 0;
	long lBottom = 0;

	CComPtr<ITreatWrapperInterface> prtWrapper;

	if (!CCalcParser::Instance().m_vecCurBasicData.empty())
		CCalcParser::Instance().m_vecCurBasicData.clear();

	CoInitialize(NULL);

	if (FAILED(prtWrapper.CoCreateInstance(__uuidof(TreatWrapperInterface))))
		MessageBox(_T("시스템에 TreatWrapper.dll이 정상적으로 등록되지 않았습니다."), _T("확인"), MB_ICONSTOP);

	prtWrapper->GetTotalBasicContSize(&m_lTotSize);

	for (long lIdx = 0; lIdx < m_lTotSize; lIdx++)
	{
		BSTR bstrStName;

		_S_BASIC_CONTINFO struBasicInfo;

		prtWrapper->GetCurContRect(lIdx, &lLeft, &lTop, &lRight, &lBottom);
		prtWrapper->GetCurContStatic(lIdx, &bstrStName);

		struBasicInfo.rcRect = CRect(lLeft, lTop, lRight, lBottom);

		USES_CONVERSION;
		CString strName = OLE2CT(bstrStName);
		struBasicInfo.strStName = strName;

		CCalcParser::Instance().m_vecCurBasicData.push_back(struBasicInfo);

		SysFreeString(bstrStName);
	}

	CoUninitialize();
}

void CTreatConsultInterface::CreatTreatControl()
{
	long lLeft		= 0; 
	long lTop		= 0; 
	long lRight		= 0;
	long lBottom	= 0;

	CComPtr<ITreatWrapperInterface> prtWrapper;

	if (!CCalcParser::Instance().m_vecCurBasicData.empty())
		CCalcParser::Instance().m_vecCurBasicData.clear();

	CoInitialize(NULL);

	if (FAILED(prtWrapper.CoCreateInstance(__uuidof(TreatWrapperInterface))))
		MessageBox(_T("시스템에 TreatWrapper.dll이 정상적으로 등록되지 않았습니다."), _T("확인"), MB_ICONSTOP);

	prtWrapper->GetTotalBasicContSize(&m_lTotSize);

	m_pstContData = new CStatic[m_lTotSize];

	m_peditContData = new CEdit[m_lTotSize];

	for (long lIdx = 0; lIdx < m_lTotSize; lIdx++)
	{
		BSTR bstrStName;

		_S_BASIC_CONTINFO struBasicInfo;

		prtWrapper->GetCurContRect(lIdx, &lLeft, &lTop, &lRight, &lBottom);
		prtWrapper->GetCurContStatic(lIdx, &bstrStName);

		struBasicInfo.rcRect = CRect(lLeft, lTop, lRight, lBottom);

		USES_CONVERSION;
		CString strName = OLE2CT(bstrStName);
		struBasicInfo.strStName = strName;

		m_peditContData[lIdx].Create(m_hWnd, CRect(lLeft, lTop, lRight, lBottom), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 0, IDC_EDIT_BASIC_CONTROL + lIdx);
		m_peditContData[lIdx].SetFont(m_hStNameFont);

		m_pstContData[lIdx].Create(m_hWnd, CRect(lLeft - 83, lTop + 4, lRight - 45, lBottom), strName, WS_CHILD | WS_VISIBLE | SS_LEFT, 0, IDC_STATIC_BASIC_CONTROL + lIdx);
		m_pstContData[lIdx].SetFont(m_hStNameFont);

		CCalcParser::Instance().m_vecCurBasicData.push_back(struBasicInfo);

		SysFreeString(bstrStName);
	}

	CoUninitialize();
}

void CTreatConsultInterface::InitializeAttach()
{
	m_cboStandDate.Attach(GetDlgItem(IDC_COMBO_STANDATE));
	m_cboHospDiv.Attach(GetDlgItem(IDC_COMBO_HOSPDIV));
	m_editJisu.Attach(GetDlgItem(IDC_EDIT_JISU));
	m_editCalc.Attach(GetDlgItem(IDC_EDIT_CALC));
	m_editHisCost.Attach(GetDlgItem(IDC_EDIT_HISCOST));
	m_stCalcFormula.Attach(GetDlgItem(IDC_STATIC_FORMULA));
	m_sleCode.Attach(GetDlgItem(IDC_EDIT_CODE));
	m_editSatCost.Attach(GetDlgItem(IDC_EDIT_SATCOST));
}

void CTreatConsultInterface::InitializeControl()
{
	CRect rcList;
	long  lTotSize	= 0;
	long  lContIdx	= 0;
	long  lLeft		= 0;
	long  lTop		= 0;
	long  lRight	= 0;
	long  lBottom	= 0;


	GetClientRect(&rcList);
	rcList.left = rcList.left + 10;
	rcList.right = rcList.left + 400;
	rcList.top += 40;
	rcList.bottom -= 12;

	m_wndBasicList.Create(m_hWnd, rcList, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_SINGLESEL | LVS_REPORT, 0, IDC_LIST_BASIC_SUGA, NULL);
	m_wndBasicList.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);

	m_wndBasicList.InsertColumn(0, _T("수가코드"), LVCFMT_CENTER, 70, -1);
	m_wndBasicList.InsertColumn(1, _T("수가명"), LVCFMT_LEFT, 240, -1);
	m_wndBasicList.InsertColumn(2, _T("수가금액"), LVCFMT_RIGHT, 70, -1);
	
	m_cboHospDiv.AddString(_T("의원"));
	m_cboHospDiv.AddString(_T("병원시도"));
	m_cboHospDiv.AddString(_T("병원읍면"));
	m_cboHospDiv.AddString(_T("종합병원시도"));
	m_cboHospDiv.AddString(_T("종합병원읍면"));
	
	m_cboHospDiv.SetCurSel(0);

	m_hStNameFont = CreateFont(12, 0, 0, 0, FW_NORMAL, false, false, false, HANGEUL_CHARSET, 0, 0, 0, 0, _T("굴림"));
}

void CTreatConsultInterface::DestroyControl()
{
	if (!m_hStNameFont.IsNull())
		m_hStNameFont.DeleteObject();

	if (m_wndBasicList.IsWindow())
		m_wndBasicList.DestroyWindow();

	for (long lIdx = 0; lIdx < m_lTotSize; lIdx++)
	{
		if (m_peditContData->IsWindow())
			m_peditContData->DestroyWindow();
	}

	delete[] m_peditContData;

	for (long lIdx = 0; lIdx < m_lTotSize; lIdx++)
	{
		if (m_pstContData->IsWindow())
			m_pstContData->DestroyWindow();
	}

	delete[] m_pstContData;
}

void CTreatConsultInterface::DestroyDetach()
{
	m_cboStandDate.Detach();
	m_cboHospDiv.Detach();
	m_editJisu.Detach();
	m_editCalc.Detach();
	m_editHisCost.Detach();
	m_stCalcFormula.Detach();
	m_sleCode.Detach();
	m_obDbConn.Detach();
	m_editSatCost.Detach();

}

void CTreatConsultInterface::LoadComboHospDiv()
{
	CComPtr<ITreatWrapperInterface> prtWrapper;
	BSTR bstrStandDate;
	CString strStandDate;

	m_cboStandDate.ResetContent();

	CoInitialize(NULL);

	if (FAILED(prtWrapper.CoCreateInstance(__uuidof(TreatWrapperInterface))))
		MessageBox(_T("시스템에 TreatWrapper.dll이 정상적으로 등록되지 않았습니다."), _T("확인"), MB_ICONSTOP);

	int nComboIdx = m_cboHospDiv.GetCurSel();
	if (nComboIdx < 0)
		nComboIdx = 0;

	prtWrapper->GetStandDate(nComboIdx, &bstrStandDate);

	USES_CONVERSION;
	strStandDate = OLE2CT(bstrStandDate);
	SysFreeString(bstrStandDate);

	while (strStandDate.GetLength())
	{
		int nIdx = strStandDate.Find('/');

		CString strTemp = _T("");
		if (nIdx != -1)
			strTemp = strStandDate.Left(nIdx);
		else
			strTemp = strStandDate;

		m_cboStandDate.InsertString(0, strTemp);

		if (nIdx == -1)
			break;

		strStandDate = strStandDate.Mid(nIdx + 1);
	}

	CoUninitialize();

	m_cboStandDate.SetCurSel(0);
}

void CTreatConsultInterface::CalcTreatData()
{
	for (int nIdx = 0; nIdx < m_lTotSize; nIdx++)
	{
		CString strCost = CCalcParser::Instance().CalcTreat(nIdx);

		m_peditContData[nIdx].SetWindowText(strCost);
	}
}

void CTreatConsultInterface::LoadTreatData()
{
	CComPtr<ITreatWrapperInterface> prtWrapper;

	CoInitialize(NULL);
	if (FAILED(prtWrapper.CoCreateInstance(__uuidof(TreatWrapperInterface))))
		MessageBox(_T("시스템에 TreatWrapper.dll이 정상적으로 등록되지 않았습니다."), _T("확인"), MB_ICONSTOP);

	USES_CONVERSION;

	for (int nIdx = 0; nIdx < m_lTotSize; nIdx++)
	{
		long lDataSize = 0;
		_S_BASIC_CONTINFO struContInfo;

		prtWrapper->GetCurControlSize(nIdx, &lDataSize);

		BSTR* pbstrCode = new BSTR[5];

		prtWrapper->GetCurCode(nIdx, pbstrCode);

		for (int nSubIdx = 0; nSubIdx < 5; nSubIdx++)
		{
			CString strTemp = OLE2CT(pbstrCode[nSubIdx]);

			CCalcParser::Instance().m_vecCurBasicData[nIdx].vecCode.push_back(strTemp);

			SysFreeString(pbstrCode[nSubIdx]);
		}

		delete[] pbstrCode;

		BSTR* pbstrData = new BSTR[lDataSize];

		prtWrapper->GetCurData(nIdx, pbstrData);

		CCalcParser::Instance().m_vecCurBasicData[nIdx].strFormula = OLE2CT(pbstrData[0]);
		SysFreeString(pbstrData[0]);
		CString strCost = OLE2CT(pbstrData[1]);
		CCalcParser::Instance().m_vecCurBasicData[nIdx].strHisCost = CCalcParser::Instance().m_vecBasicSuga[_ttoi(strCost.Mid(1))].strCost;

		SysFreeString(pbstrData[1]);

		for (int nSubIdx = 2; nSubIdx < lDataSize; nSubIdx++)
		{
			CString strTemp = OLE2CT(pbstrData[nSubIdx]);
			
			CCalcParser::Instance().m_vecCurBasicData[nIdx].vecData.push_back(strTemp);

			CCalcParser::Instance().m_vecCurBasicData[nIdx].strSatCost = CCalcParser::Instance().CalcSatCost(nIdx);

			SysFreeString(pbstrData[nSubIdx]);
		}

		delete[] pbstrData;

		pbstrData = NULL;
	}

	CoUninitialize();
}

void CTreatConsultInterface::LoadBasicSuga()
{
	CComPtr<ITreatWrapperInterface> prtWrapper;
	_S_BASIC_SUGA struBasicSuga;

	BSTR pbstrCode[65];
	BSTR pbstrName[65];
	BSTR pbstrCost[65];

	CString strStandDate;
	BSTR bstrStandDate;

	if (!CCalcParser::Instance().m_vecBasicSuga.empty())
		CCalcParser::Instance().m_vecBasicSuga.clear();

	CoInitialize(NULL);
	if (FAILED(prtWrapper.CoCreateInstance(__uuidof(TreatWrapperInterface))))
		MessageBox(_T("시스템에 TreatWrapper.dll이 정상적으로 등록되지 않았습니다."), _T("확인"), MB_ICONSTOP);

	bstrStandDate = GetStandDate().AllocSysString();

	prtWrapper->LoadBasicSuga(GetHospDiv(), bstrStandDate, pbstrCode, pbstrName, pbstrCost, 65);

	USES_CONVERSION;

	for (int nIdx = 0; nIdx < 65; nIdx++)
	{
		struBasicSuga.strCode = OLE2CT(pbstrCode[nIdx]);
		struBasicSuga.strName = OLE2CT(pbstrName[nIdx]);
		struBasicSuga.strCost = OLE2CT(pbstrCost[nIdx]);

		CCalcParser::Instance().m_vecBasicSuga.push_back(struBasicSuga);

		SysFreeString(pbstrCode[nIdx]);
		SysFreeString(pbstrName[nIdx]);
		SysFreeString(pbstrCost[nIdx]);
	}

	SysFreeString(bstrStandDate);

	CoUninitialize();
}

void CTreatConsultInterface::InsertBasicSugaList()
{
	m_wndBasicList.DeleteAllItems();

	std::vector<_S_BASIC_SUGA>::iterator iterVecBasicSuga = CCalcParser::Instance().m_vecBasicSuga.begin();

	for (; iterVecBasicSuga != CCalcParser::Instance().m_vecBasicSuga.end(); iterVecBasicSuga++)
	{
		int nItem = m_wndBasicList.InsertItem(m_wndBasicList.GetItemCount(), iterVecBasicSuga->strCode);
		m_wndBasicList.SetItemText(nItem, 1, iterVecBasicSuga->strName);
		m_wndBasicList.SetItemText(nItem, 2, iterVecBasicSuga->strCost);
	}
}

void CTreatConsultInterface::SetJisuData(CString strJisu)
{
	if (strJisu.IsEmpty())
		m_wndBasicList.GetItemText(0, 2, strJisu);

	m_wndBasicList.SetItemText(0, 2, strJisu);
	m_editJisu.SetWindowText(strJisu);
}

CString CTreatConsultInterface::GetStandDate()
{
	CString strTemp;
	m_cboStandDate.GetLBText(m_cboStandDate.GetCurSel(), strTemp);

	return strTemp;
}

long CTreatConsultInterface::GetHospDiv()
{
	return m_cboHospDiv.GetCurSel();
}