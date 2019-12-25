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

	// ���ı���
	InitializeDB();

	// �޺��ڽ� �̺�Ʈ�� ������ XML�� ���� �����͸� List�� �߰��ϴ� ���
	SendMessage(WM_COMMAND, MAKEWPARAM(m_cboStandDate.GetDlgCtrlID(), CBN_SELCHANGE), reinterpret_cast<LPARAM>(m_cboStandDate.m_hWnd)); 

	return TRUE;
}

LRESULT CTreatBasicViewDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// ��������, ���ؽ����� ��������۾�
	m_lHospDiv		= GetHospDiv();
	m_strStandDate	= GetStandDate();

	// Destroy Control
	DestroyControl();

	// Destroy Control Detach
	DestroyDetach();

	// ���ı���
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

		// List ui����
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
	// ���ı��� -> ����Ʈ�� �ִ� �͵��� vector�� ����

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
	// XML ���Ϸε�(Ÿ�Կ� �°�)
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
	
	m_wndBasicList.InsertColumn(0, _T("�����ڵ�"),	LVCFMT_CENTER, 80, -1);
	m_wndBasicList.InsertColumn(1, _T("������"),		LVCFMT_LEFT, 325,  -1);
	m_wndBasicList.InsertColumn(2, _T("�����ݾ�"),	LVCFMT_RIGHT, 70,  -1);

	// �޺��ڽ� �߰�
	// �������� ���ʼ����� ���� ������ ����.
	Elem entries[]
	{
		{ _T("�ǿ�") },		
		{ _T("�����õ�") },	
		{ _T("��������") },	
		{ _T("���պ����õ�") },
		{ _T("���պ�������") }
	};

	std::vector<long> vecHospDiv;
	std::vector<CString> vecStandDate;

	if (!CXmlParser::Instance().InitEnvInfo(vecHospDiv, vecStandDate))
	{
		CString	strXml = _T("");
		strXml.Format(_T("����ȯ�漼���� �ϴµ� �������� �ֽ��ϴ�. \n������ ���� �� ��� (��)�ϳ����� û������ڿ��� ������ �ֽñ� �ٶ��ϴ�."));
		::MessageBox(NULL, strXml, _T("�˸�"), MB_OK);
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
	// ���ı���
}

void CTreatBasicViewDlg::DestroyDB()
{
	// ���ı���
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

// ��������, ���ؽ����� ���ϱ� �����Լ�.
void CTreatBasicViewDlg::GetTreatEnvData(long& lHospDiv, CString& strStandDate)
{
	lHospDiv		= m_lHospDiv;
	strStandDate	= m_strStandDate;
}