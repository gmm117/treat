// TreatBasicViewDlg.cpp : Implementation of CTreatBasicViewDlg

#include "stdafx.h"
#include "resource.h"
#include "TreatBasicViewDlg.h"
#include "TreatFixDlg.h"
#include "XmlParser.h"


// CTreatBasicViewDlg
CTreatBasicViewDlg::CTreatBasicViewDlg() : m_lHospDiv(0), m_strStandDate(_T(""))
{
}

CTreatBasicViewDlg::~CTreatBasicViewDlg()
{

}

LRESULT CTreatBasicViewDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// Initialize Control Attach
	InitializeAttach();

	// XML Loading
	if (!InitializeXML())
		return FALSE;
	
	// Windows Control Init
	InitializeControl();

	// 추후구현
	InitializeDB();

	// 콤보박스 이벤트를 날려서 XML의 읽은 데이터를 List에 추가하는 기능
	SendMessage(WM_COMMAND, MAKEWPARAM(m_cboStandDate.GetDlgCtrlID(), CBN_SELCHANGE), reinterpret_cast<LPARAM>(m_cboStandDate.m_hWnd)); 

	return TRUE;
}

LRESULT CTreatBasicViewDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 병원구분, 기준시점을 얻기위한작업
	m_lHospDiv		= GetHospDiv();
	m_strStandDate	= GetStandDate();

	// Destroy Control
	DestroyControl();

	// Destroy Control Detach
	DestroyDetach();

	// 추후구현
	DestroyDB();

	return TRUE;
}

LRESULT CTreatBasicViewDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndDialog(IDOK);

	return 0;
}

LRESULT CTreatBasicViewDlg::OnChangeHospDiv(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	LoadBasicSuga(GetHospDiv(), GetStandDate());

	return 0;
}

LRESULT CTreatBasicViewDlg::OnChangeStanddate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	LoadBasicSuga(GetHospDiv(), GetStandDate());

	return 0;
}

LRESULT CTreatBasicViewDlg::OnListDblClk(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
{
	LPNMITEMACTIVATE pnmia = reinterpret_cast<LPNMITEMACTIVATE>(pnmh);
	
	if (pnmia->iItem != -1)
	{
		TCHAR szText[1024];

		CHeaderCtrl& wndHeader = m_wndBasicList.GetHeader();

		HDITEM hdi;
		hdi.mask = HDI_TEXT;
		hdi.pszText = szText;
		hdi.cchTextMax = sizeof(szText)-1;

		wndHeader.GetItem(pnmia->iSubItem, &hdi);

		CTreatFixDlg obFixDlg(szText);
		obFixDlg.DoModal();

		CString strContent = obFixDlg.GetContentData();

		// List ui변경
		SetListData(pnmia->iItem, pnmia->iSubItem, strContent);

		if (pnmia->iSubItem == 0)
			m_vecBasicSugaParser[pnmia->iItem].strCode = strContent;
		else if (pnmia->iSubItem == 1)
			m_vecBasicSugaParser[pnmia->iItem].strName = strContent;
		else if (pnmia->iSubItem == 2)
			m_vecBasicSugaParser[pnmia->iItem].strCost = strContent;
	}

	return 0;
}

LRESULT CTreatBasicViewDlg::OnSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	// 추후구현 -> 리스트에 있는 것들을 vector에 저장

	CXmlParser::Instance().SetSequenceData(GetHospDiv(), GetStandDate(), m_vecBasicSugaParser);

	EndDialog(IDOK);

	return 0L;
}

void CTreatBasicViewDlg::SetListData(long lRow, long lCol, CString strData)
{
	if (strData.IsEmpty())
		return;

	m_wndBasicList.SetItemText(lRow, lCol, strData);
}

void CTreatBasicViewDlg::LoadBasicSuga(long lIdx, CString strStandDate)
{
	m_wndBasicList.DeleteAllItems();
	
	m_vecBasicSugaParser = CXmlParser::Instance().GetSequenceData(lIdx, strStandDate);
	
	std::vector<_S_BASIC_SUGA>::iterator iterVecBasicSuga = m_vecBasicSugaParser.begin();

	for (; iterVecBasicSuga != m_vecBasicSugaParser.end(); iterVecBasicSuga++)
	{
		int nItem = m_wndBasicList.InsertItem(m_wndBasicList.GetItemCount(), iterVecBasicSuga->strCode);
		m_wndBasicList.SetItemText(nItem, 1, iterVecBasicSuga->strName);
		m_wndBasicList.SetItemText(nItem, 2, iterVecBasicSuga->strCost);
	}
}

void CTreatBasicViewDlg::InitializeAttach()
{
	m_cboStandDate.Attach(GetDlgItem(IDC_COMBO_STANDDATE));
	m_cboHospDiv.Attach(GetDlgItem(IDC_COMBO_HOSPDIV));
	m_btnSave.Attach(GetDlgItem(IDC_BTN_SAVE));
}

bool CTreatBasicViewDlg::InitializeXML()
{
	// XML 파일로딩(타입에 맞게)
	if (!CXmlParser::Instance().LoadXmlData())
		return false;

	return true;
}

void CTreatBasicViewDlg::InitializeControl()
{
	CRect rcList;

	GetClientRect(&rcList);
	rcList.left = rcList.left + 10;
	rcList.right = rcList.right - 10;
	rcList.top += 50;
	rcList.bottom -= 10;

	m_wndBasicList.Create(m_hWnd, rcList, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_SINGLESEL | LVS_REPORT, 0, IDC_LIST_BASIC_SUGA, NULL);
	m_wndBasicList.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);
	
	m_wndBasicList.InsertColumn(0, _T("수가코드"),	LVCFMT_CENTER, 80, -1);
	m_wndBasicList.InsertColumn(1, _T("수가명"),		LVCFMT_LEFT, 325,  -1);
	m_wndBasicList.InsertColumn(2, _T("수가금액"),	LVCFMT_RIGHT, 70,  -1);

	// 콤보박스 추가
	// 병원종별 기초수가에 대한 정보를 얻어옴.
	Elem entries[]
	{
		{ _T("의원") },		
		{ _T("병원시도") },	
		{ _T("병원읍면") },	
		{ _T("종합병원시도") },
		{ _T("종합병원읍면") }
	};

	std::vector<long> vecHospDiv;
	std::vector<CString> vecStandDate;

	if (!CXmlParser::Instance().InitEnvInfo(vecHospDiv, vecStandDate))
	{
		CString	strXml = _T("");
		strXml.Format(_T("기초환경세팅을 하는데 문제점이 있습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."));
		::MessageBox(NULL, strXml, _T("알림"), MB_OK);
		return;
	}
	
	std::vector<long>::iterator iterHospDiv = vecHospDiv.begin();
	for (; iterHospDiv != vecHospDiv.end(); iterHospDiv++)
	{
		m_cboHospDiv.AddString(entries[*iterHospDiv].strName);
	}

	std::vector<CString>::iterator iterStandDate = vecStandDate.begin();
	for (; iterStandDate != vecStandDate.end(); iterStandDate++)
	{
		m_cboStandDate.InsertString(0, *iterStandDate);
	}

	m_cboHospDiv.SetCurSel(0);
	m_cboStandDate.SetCurSel(0);
}

void CTreatBasicViewDlg::InitializeDB()
{
	// 추후구현
}

void CTreatBasicViewDlg::DestroyDB()
{
	// 추후구현
}

void CTreatBasicViewDlg::DestroyDetach()
{
	m_cboStandDate.Detach();
	m_cboHospDiv.Detach();
	m_btnSave.Detach();
}

void CTreatBasicViewDlg::DestroyControl()
{
	if (m_wndBasicList.IsWindow())
		m_wndBasicList.DestroyWindow();
}

CString CTreatBasicViewDlg::GetStandDate()
{
	TCHAR szBuff[1024];
	m_cboStandDate.GetWindowText(szBuff, 1024);

	return szBuff;
}

long CTreatBasicViewDlg::GetHospDiv()
{
	return m_cboHospDiv.GetCurSel();
}

// 병원구분, 기준시점을 구하기 위한함수.
void CTreatBasicViewDlg::GetTreatEnvData(long& lHospDiv, CString& strStandDate)
{
	lHospDiv		= m_lHospDiv;
	strStandDate	= m_strStandDate;
}