#include "stdafx.h"
#include "XmlBasicSugaParser.h"


CXmlBasicSugaParser::CXmlBasicSugaParser()
{
}


CXmlBasicSugaParser::~CXmlBasicSugaParser()
{
	if (!m_vecXmlName.empty())
		m_vecXmlName.clear();

	if (!m_mapCurBasicSuga.empty())
		m_mapCurBasicSuga.clear();

	if (!m_mapTotBasicSuga.empty())
		m_mapTotBasicSuga.clear();
}

CXmlBasicSugaParser& CXmlBasicSugaParser::Instance()
{
	static CXmlBasicSugaParser theInstance;
	return theInstance;
}

void CXmlBasicSugaParser::AddVecXmlName()
{
	if (!m_vecXmlName.empty())
		m_vecXmlName.clear();

	m_vecXmlName.push_back(_T("T_CLINIC_BASIC_SUGA.xml"));
	m_vecXmlName.push_back(_T("T_HOSPCITY_BASIC_SUGA.xml"));
	m_vecXmlName.push_back(_T("T_HOSPUBMYUN_BASIC_SUGA.xml"));
	m_vecXmlName.push_back(_T("T_TOP_HOSPCITY_BASIC_SUGA.xml"));
	m_vecXmlName.push_back(_T("T_TOP_HOSPUBMYUN_BASIC_SUGA.xml"));

	for (int nIdx = 0; nIdx < 5; nIdx++)
	{
		entries[nIdx].lIdx = nIdx;
		entries[nIdx].strXmlName = m_vecXmlName[nIdx];
	}
}

bool CXmlBasicSugaParser::LoadXmlData()
{
	CString	strXmlPath = _T("");
	CString strFolderPath = _T("");

	AddVecXmlName();

	if (!m_mapTotBasicSuga.empty())
		m_mapTotBasicSuga.clear();

	std::vector< CString >::iterator IterVecName = m_vecXmlName.begin();

	::GetModuleFileName(NULL, strFolderPath.GetBuffer(MAX_PATH), MAX_PATH);
	strFolderPath.ReleaseBuffer();
	if (strFolderPath.Find('\\') != -1) {
		for (int i = strFolderPath.GetLength() - 1; i >= 0; i--) {
			TCHAR ch = strFolderPath[i];
			strFolderPath.Delete(i);
			if (ch == '\\') break;
		}
	}

	int nEndPos = strFolderPath.Find(_T("dll"));
	if (nEndPos != -1)
		strFolderPath = strFolderPath.Left(nEndPos - 1);

	int nIdx = 0; // 0: 의원, 1: 병원시도, 2: 병원읍면, 3: 종합병원시도, 4: 종합병원읍면
	for (IterVecName = m_vecXmlName.begin(); IterVecName != m_vecXmlName.end(); ++IterVecName)
	{
		if (!m_mapCurBasicSuga.empty())
			m_mapCurBasicSuga.clear();

		strXmlPath.Format(_T("%s\\include\\XML\\%s"), strFolderPath, *IterVecName);

		if (!m_XmlDoc.Open(strXmlPath))
		{
			CString	strXml = _T("");
			strXml.Format(_T("%s을 파일을 로드할 수 없습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), *IterVecName);
			MessageBox(NULL, strXml, _T("알림"), MB_OK);
			return false;
		}

		if (!SelectFileNode(nIdx))
		{
			CString	strXml = _T("");
			strXml.Format(_T("%s을 데이터를 로드하는데 실패하였습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), *IterVecName);
			MessageBox(NULL, strXml, _T("알림"), MB_OK | MB_ICONASTERISK);
			return false;
		}

		nIdx++;

		m_XmlDoc.Close();
	}

	return true;
}

bool CXmlBasicSugaParser::SelectFileNode(int nIdx)
{
	CString	 strStandDate = _T("");
	CXMLNode XmlNoderoot;
	CXMLNode XmlDocNode;

	XmlNoderoot = m_XmlDoc.getRootNode();
	if (XmlNoderoot.IsNull())
	{
		ATLASSERT(XmlNoderoot.IsNull());
		return false;
	}
	XmlDocNode = XmlNoderoot.selectSingleNode(_T("//BASICSUGA"));
	if (XmlDocNode.IsNull())
	{
		ATLASSERT(XmlDocNode.IsNull());
		return false;
	}

	CXMLIteratorNodes* iterXmlNode = static_cast<CXMLIteratorNodes*>(XmlDocNode.GetChildren());

	for (iterXmlNode->Begin(); iterXmlNode->IsDone() == false; iterXmlNode->Next())
	{
		CXMLNodeMap pAttpMap = iterXmlNode->CurrentItem().get_attributes();
		CXMLNode	 XmlNodeType = pAttpMap.Item(_T("standdate"));

		strStandDate.Format(_T("%s"), XmlNodeType.get_nodeValue());

		if (!SelectTypeNode(nIdx, iterXmlNode->CurrentItem(), strStandDate))
		{
			return false;
		}
	}

	m_mapTotBasicSuga.insert(std::pair<long, std::map<CString, std::vector<_S_BASIC_SUGA> > >(nIdx, m_mapCurBasicSuga));

	return true;
}

bool CXmlBasicSugaParser::SelectTypeNode(int nIdx, CXMLNode XmlNodeType, CString strStandDate)
{
	_S_BASIC_SUGA struBasicSuga;

	CXMLIteratorNodes* iterXmlTypeNode = static_cast<CXMLIteratorNodes*>(XmlNodeType.GetChildren());

	std::vector<_S_BASIC_SUGA>	vecXMLInfo;
	if (vecXMLInfo.size() > 0)
		vecXMLInfo.clear();

	for (iterXmlTypeNode->Begin(); iterXmlTypeNode->IsDone() == false; iterXmlTypeNode->Next())
	{
		CXMLNode XmlNodeName = iterXmlTypeNode->CurrentItem().selectSingleNode(_T("CODE"));
		if (XmlNodeName.IsNull())
		{
			ATLASSERT(XmlNodeName.IsNull());
			return false;
		}
		struBasicSuga.strCode = XmlNodeName.get_nodeValue();

		XmlNodeName = iterXmlTypeNode->CurrentItem().selectSingleNode(_T("NAME"));
		if (XmlNodeName.IsNull())
		{
			ATLASSERT(XmlNodeName.IsNull());
			return false;
		}
		struBasicSuga.strName = XmlNodeName.get_nodeValue();

		XmlNodeName = iterXmlTypeNode->CurrentItem().selectSingleNode(_T("COST"));
		if (XmlNodeName.IsNull())
		{
			ATLASSERT(XmlNodeName.IsNull());
			return false;
		}
		struBasicSuga.strCost = XmlNodeName.get_nodeValue();

		vecXMLInfo.push_back(struBasicSuga);
	}

	m_mapCurBasicSuga.insert(std::pair<CString, std::vector<_S_BASIC_SUGA> >(strStandDate, vecXMLInfo));

	return true;

}

void CXmlBasicSugaParser::LoadMapXMLInfo(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA>& veCXmlBasicSugaParser)
{
	std::map<long, std::map<CString, std::vector<_S_BASIC_SUGA> > >::iterator iterMapTotXMLFile = m_mapTotBasicSuga.find(lIdx);

	if (iterMapTotXMLFile == m_mapTotBasicSuga.end())
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s 파일을 찾을 수 없습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), entries[lIdx]);
		MessageBox(NULL, strXml, _T("알림"), MB_OK);
		return;
	}

	std::map<CString, std::vector<_S_BASIC_SUGA> >::iterator iterMapStandDate = iterMapTotXMLFile->second.find(strStandDate);

	if (iterMapStandDate == iterMapTotXMLFile->second.end())
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s 기준시점을 찾을 수 없습니다. %s 문서에 기준시점을 추가해주시기 바랍니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), strStandDate, entries[lIdx]);
		MessageBox(NULL, strXml, _T("알림"), MB_OK);
		return;
	}

	std::vector<_S_BASIC_SUGA>::iterator iterVecBasicSuga = iterMapStandDate->second.begin();
	
	for (; iterVecBasicSuga != iterMapStandDate->second.end(); iterVecBasicSuga++)
	{
		veCXmlBasicSugaParser.push_back(*iterVecBasicSuga);
	}
}

bool CXmlBasicSugaParser::InitEnvInfo(std::vector<long>& vecHospDiv, std::vector<CString>& vecStandDate)
{
	std::map<long, std::map<CString, std::vector<_S_BASIC_SUGA> > >::iterator iterMapTotXMLFile = m_mapTotBasicSuga.begin();
	
	if (iterMapTotXMLFile == m_mapTotBasicSuga.end())
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s 파일을 찾을 수 없습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), entries[0]);
		MessageBox(NULL, strXml, _T("알림"), MB_OK);
		return false;
	}
	
	for (; iterMapTotXMLFile != m_mapTotBasicSuga.end(); iterMapTotXMLFile++)
	{
		std::map<CString, std::vector<_S_BASIC_SUGA> >::iterator iterMapBasicSuga = iterMapTotXMLFile->second.begin();
		vecStandDate.clear();

		for (; iterMapBasicSuga != iterMapTotXMLFile->second.end(); iterMapBasicSuga++)
		{
			vecStandDate.push_back(iterMapBasicSuga->first);
		}
		vecHospDiv.push_back(iterMapTotXMLFile->first);
	}

	return true;
}

bool CXmlBasicSugaParser::SetSequenceData(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA> vecFixXMLParser)
{
	std::map<long, std::map<CString, std::vector<_S_BASIC_SUGA> > >::iterator iterMapTotXMLFile = m_mapTotBasicSuga.find(lIdx);

	if (iterMapTotXMLFile == m_mapTotBasicSuga.end())
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s 파일을 찾을 수 없습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), entries[lIdx]);
		MessageBox(NULL, strXml, _T("알림"), MB_OK);
		return false;
	}

	std::map<CString, std::vector<_S_BASIC_SUGA> >::iterator iterMapStandDate = iterMapTotXMLFile->second.find(strStandDate);

	if (iterMapStandDate == iterMapTotXMLFile->second.end())
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s 기준시점을 찾을 수 없습니다. %s 문서에 기준시점을 추가해주시기 바랍니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), strStandDate, entries[lIdx]);
		MessageBox(NULL, strXml, _T("알림"), MB_OK);
		return false;
	}

	// 변경된 사항에 대해서 vector에 덮어쓰기 함.
	iterMapStandDate->second = vecFixXMLParser;

	//  XML에 데이터를 저장하는 함수.
	if (!SetXMLNode(lIdx, strStandDate, vecFixXMLParser))
		return false;

	::MessageBox(NULL, _T("저장이 완료되었습니다."), _T("알림"), MB_OK);

	return true;
}

bool CXmlBasicSugaParser::SetXMLNode(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA>& vecFixXMLParser)
{
	CString strFolderPath	= _T("");
	CString strXmlPath		= _T("");
	std::vector< CString >::iterator IterVecName = m_vecXmlName.begin();

	::GetModuleFileName(NULL, strFolderPath.GetBuffer(MAX_PATH), MAX_PATH);
	strFolderPath.ReleaseBuffer();
	if (strFolderPath.Find('\\') != -1) {
		for (int i = strFolderPath.GetLength() - 1; i >= 0; i--) {
			TCHAR ch = strFolderPath[i];
			strFolderPath.Delete(i);
			if (ch == '\\') break;
		}
	}

	int nEndPos = strFolderPath.Find(_T("dll"));
	if (nEndPos != -1)
		strFolderPath = strFolderPath.Left(nEndPos - 1);
	
	strXmlPath.Format(_T("%s\\include\\XML\\%s"), strFolderPath, *IterVecName);

	if (!m_XmlDoc.Open(strXmlPath))
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s을 파일을 로드할 수 없습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), *IterVecName);
		MessageBox(NULL, strXml, _T("알림"), MB_OK);
		return false;
	}

	// lIdx : 0: 의원, 1: 병원시도, 2: 병원읍면, 3: 종합병원시도, 4: 종합병원읍면
	if (!SetFileNode(lIdx, strStandDate, vecFixXMLParser))
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s을 데이터를 로드하는데 실패하였습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), *IterVecName);
		MessageBox(NULL, strXml, _T("알림"), MB_OK | MB_ICONASTERISK);
		return false;
	}

	m_XmlDoc.Save(strXmlPath);

	m_XmlDoc.Close();
	
	return true;
}

bool CXmlBasicSugaParser::SetFileNode(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA>& vecFixXMLParser)
{
	CString strXMLStandDate;
	CXMLNode XmlNoderoot;
	CXMLNode XmlDocNode;

	XmlNoderoot = m_XmlDoc.getRootNode();
	if (XmlNoderoot.IsNull())
	{
		ATLASSERT(XmlNoderoot.IsNull());
		return false;
	}
	XmlDocNode = XmlNoderoot.selectSingleNode(_T("//BASICSUGA"));
	if (XmlDocNode.IsNull())
	{
		ATLASSERT(XmlDocNode.IsNull());
		return false;
	}

	CXMLIteratorNodes* iterXmlNode = static_cast<CXMLIteratorNodes*>(XmlDocNode.GetChildren());

	for (iterXmlNode->Begin(); iterXmlNode->IsDone() == false; iterXmlNode->Next())
	{
		CXMLNodeMap pAttpMap = iterXmlNode->CurrentItem().get_attributes();
		CXMLNode	 XmlNodeType = pAttpMap.Item(_T("standdate"));

		strXMLStandDate.Format(_T("%s"), XmlNodeType.get_nodeValue());

		if (strXMLStandDate == strStandDate)
		{
			if (!SetTypeNode(iterXmlNode->CurrentItem(), strStandDate, vecFixXMLParser))
			{
				return false;
			}
			break;
		}
	} 
	return true;
}
bool CXmlBasicSugaParser::SetTypeNode(CXMLNode XmlNodeType, CString strStandDate, std::vector<_S_BASIC_SUGA>& vecFixXMLParser)
{
	CXMLIteratorNodes* iterXmlTypeNode = static_cast<CXMLIteratorNodes*>(XmlNodeType.GetChildren());

	int nIdx = 0;
	for (iterXmlTypeNode->Begin(); iterXmlTypeNode->IsDone() == false; iterXmlTypeNode->Next())
	{
		CXMLNode XmlNodeName = iterXmlTypeNode->CurrentItem().selectSingleNode(_T("CODE"));
		if (XmlNodeName.IsNull())
		{
			ATLASSERT(XmlNodeName.IsNull());
			return false;
		}
		XmlNodeName.put_nodeValue(vecFixXMLParser[nIdx].strCode);

		XmlNodeName = iterXmlTypeNode->CurrentItem().selectSingleNode(_T("NAME"));
		if (XmlNodeName.IsNull())
		{
			ATLASSERT(XmlNodeName.IsNull());
			return false;
		}
		XmlNodeName.put_nodeValue(vecFixXMLParser[nIdx].strName);

		XmlNodeName = iterXmlTypeNode->CurrentItem().selectSingleNode(_T("COST"));
		if (XmlNodeName.IsNull())
		{
			ATLASSERT(XmlNodeName.IsNull());
			return false;
		}
		XmlNodeName.put_nodeValue(vecFixXMLParser[nIdx].strCost);

		nIdx++;
	}

	return true;
}


bool CXmlBasicSugaParser::GetStandDate(long lIdx, CString& strStandDate)
{
	std::map<long, std::map<CString, std::vector<_S_BASIC_SUGA> > >::iterator iterMapTotXMLFile = m_mapTotBasicSuga.find(lIdx);

	if (iterMapTotXMLFile == m_mapTotBasicSuga.end())
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s 파일을 찾을 수 없습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), entries[lIdx]);
		MessageBox(NULL, strXml, _T("알림"), MB_OK);
		return false;
	}

	std::map<CString, std::vector<_S_BASIC_SUGA> >::iterator iterMapStandDate = iterMapTotXMLFile->second.begin();

	if (iterMapStandDate == iterMapTotXMLFile->second.end())
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s 기준시점을 찾을 수 없습니다. %s 문서에 기준시점을 추가해주시기 바랍니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), strStandDate, entries[lIdx]);
		MessageBox(NULL, strXml, _T("알림"), MB_OK);
		return false;
	}

	for (; iterMapStandDate != iterMapTotXMLFile->second.end(); iterMapStandDate++)
	{
		strStandDate += iterMapStandDate->first + _T("/");
	}

	if (!strStandDate.IsEmpty())
		strStandDate = strStandDate.Left(strStandDate.GetLength() - 1);

	return true;
}