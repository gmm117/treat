#include "stdafx.h"
#include "XmlBasicControlParser.h"


CXmlBasicControlParser::CXmlBasicControlParser()
{

}

CXmlBasicControlParser::~CXmlBasicControlParser()
{

}

CXmlBasicControlParser& CXmlBasicControlParser::Instance()
{
	static CXmlBasicControlParser theInstance;
	return theInstance;
}

bool CXmlBasicControlParser::LoadXmlData()
{
	CString	strXmlPath = _T("");
	CString strFolderPath = _T("");
	CString strVecName = _T("T_CALC_BASIC_CONTROL.xml");

	if (!m_mapTotBasicControl.empty())
		m_mapTotBasicControl.clear();

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

	strXmlPath.Format(_T("%s\\include\\XML\\%s"), strFolderPath, _T("T_CALC_BASIC_CONTROL.xml"));

	if (!m_XmlDoc.Open(strXmlPath))
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s을 파일을 로드할 수 없습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), strVecName);
		MessageBox(NULL, strXml, _T("알림"), MB_OK);
		return false;
	}

	if (!SelectFileNode())
	{
		CString	strXml = _T("");
		strXml.Format(_T("%s을 데이터를 로드하는데 실패하였습니다. \n문제가 지속 될 경우 (주)하나로팀 청구담당자에게 문의해 주시기 바랍니다."), strVecName);
		MessageBox(NULL, strXml, _T("알림"), MB_OK | MB_ICONASTERISK);
		return false;
	}

	return true;
}

bool CXmlBasicControlParser::SelectFileNode()
{
	CString	 strStandDate = _T("");
	CXMLNode XmlNoderoot;
	CXMLNode XmlDocNode;
	CRect	 rcRect;
	

	XmlNoderoot = m_XmlDoc.getRootNode();
	if (XmlNoderoot.IsNull())
	{
		ATLASSERT(XmlNoderoot.IsNull());
		return false;
	}
	XmlDocNode = XmlNoderoot.selectSingleNode(_T("//BASICCONT"));
	if (XmlDocNode.IsNull())
	{
		ATLASSERT(XmlDocNode.IsNull());
		return false;
	}

	CXMLIteratorNodes* iterXmlNode = static_cast<CXMLIteratorNodes*>(XmlDocNode.GetChildren());

	int nIdx = 0;
	for (iterXmlNode->Begin(); iterXmlNode->IsDone() == false; iterXmlNode->Next())
	{
		_S_BASIC_CONTINFO struBasicControl;
		CXMLNode XmlNodeType = iterXmlNode->CurrentItem();

		if (!SelectTypeNode(XmlNodeType, rcRect, struBasicControl))
		{
			return false;
		}
		
		m_mapTotBasicControl.insert(std::pair<long, _S_BASIC_CONTINFO>(nIdx, struBasicControl));
		nIdx++;
	}

	return true;
}

bool CXmlBasicControlParser::SelectTypeNode(CXMLNode XmlNodeType, CRect& rcRect, _S_BASIC_CONTINFO& struBasicControl)
{
	CXMLIteratorNodes* iterXmlTypeNode = static_cast<CXMLIteratorNodes*>(XmlNodeType.GetChildren());

	for (iterXmlTypeNode->Begin(); iterXmlTypeNode->IsDone() == false; iterXmlTypeNode->Next())
	{
		if (iterXmlTypeNode->CurrentItem().get_nodeName() == _T("RECT"))
		{
			if (!SelectRectNode(iterXmlTypeNode->CurrentItem(), rcRect))
				return false;
		}

		if (iterXmlTypeNode->CurrentItem().get_nodeName() == _T("LIST"))
		{
			if (!SelectDataNode(iterXmlTypeNode->CurrentItem(), rcRect, struBasicControl))
				return false;
		}
	}

	return true;
}

bool CXmlBasicControlParser::SelectRectNode(CXMLNode XmlRectNode, CRect& rcRect)
{
	CXMLNode XmlNodeName = XmlRectNode.selectSingleNode(_T("LEFT"));
	if (XmlNodeName.IsNull())
	{
		ATLASSERT(XmlNodeName.IsNull());
		return false;
	}
	rcRect.left = _ttoi(XmlNodeName.get_nodeValue());

	XmlNodeName = XmlRectNode.selectSingleNode(_T("TOP"));
	if (XmlNodeName.IsNull())
	{
		ATLASSERT(XmlNodeName.IsNull());
		return false;
	}
	rcRect.top = _ttoi(XmlNodeName.get_nodeValue());

	XmlNodeName = XmlRectNode.selectSingleNode(_T("RIGHT"));
	if (XmlNodeName.IsNull())
	{
		ATLASSERT(XmlNodeName.IsNull());
		return false;
	}
	rcRect.right = _ttoi(XmlNodeName.get_nodeValue());

	XmlNodeName = XmlRectNode.selectSingleNode(_T("BOTTOM"));
	if (XmlNodeName.IsNull())
	{
		ATLASSERT(XmlNodeName.IsNull());
		return false;
	}
	rcRect.bottom = _ttoi(XmlNodeName.get_nodeValue());

	return true;
}

bool CXmlBasicControlParser::SelectDataNode(CXMLNode XmlDataData, CRect& rcRect, _S_BASIC_CONTINFO& struBasicControl)
{
	CXMLIteratorNodes* iterXmlDataNode = static_cast<CXMLIteratorNodes*>(XmlDataData.GetChildren());

	for (iterXmlDataNode->Begin(); iterXmlDataNode->IsDone() == false; iterXmlDataNode->Next())
	{
		if (iterXmlDataNode->CurrentItem().get_nodeName() == _T("FORMULA"))
		{
			struBasicControl.strFormula = iterXmlDataNode->CurrentItem().get_nodeValue();
		}
		else if (iterXmlDataNode->CurrentItem().get_nodeName() == _T("COUNT"))
		{
			struBasicControl.nCnt = _ttoi(iterXmlDataNode->CurrentItem().get_nodeValue());
		}
		else if (iterXmlDataNode->CurrentItem().get_nodeName() == _T("STATIC"))
		{
			struBasicControl.strStName = iterXmlDataNode->CurrentItem().get_nodeValue();
		}
		else if (iterXmlDataNode->CurrentItem().get_nodeName() == _T("HISCOST"))
		{
			struBasicControl.strHisCost = iterXmlDataNode->CurrentItem().get_nodeValue();
		}
		else if (iterXmlDataNode->CurrentItem().get_nodeName().Find(_T("CODE")) != -1)
		{
			struBasicControl.vecCode.push_back(iterXmlDataNode->CurrentItem().get_nodeValue());
		}
		else
		{
			struBasicControl.vecData.push_back(iterXmlDataNode->CurrentItem().get_nodeValue());
		}
		
	}
	struBasicControl.rcRect = rcRect;

	return true;
}

bool CXmlBasicControlParser::LoadCurContInfo(long lContIdx, _S_BASIC_CONTINFO& struBasicContInfo)
{
	std::map<long, _S_BASIC_CONTINFO>::iterator iterBasicInfo = m_mapTotBasicControl.find(lContIdx);

	if (iterBasicInfo == m_mapTotBasicControl.end())
		return false;

	struBasicContInfo = iterBasicInfo->second;

	return true;
}

long CXmlBasicControlParser::GetTotalBasicContSize()
{
	return m_mapTotBasicControl.size();
}

long CXmlBasicControlParser::GetCurControlSize(long lContIdx)
{
	std::map<long, _S_BASIC_CONTINFO>::iterator iterBasicInfo = m_mapTotBasicControl.find(lContIdx);

	if (iterBasicInfo == m_mapTotBasicControl.end())
		return 0;

	return iterBasicInfo->second.nCnt;
}

CString CXmlBasicControlParser::GetCurStaticData(long lContIdx)
{
	std::map<long, _S_BASIC_CONTINFO>::iterator iterBasicInfo = m_mapTotBasicControl.find(lContIdx);

	if (iterBasicInfo == m_mapTotBasicControl.end())
		return _T("");

	return iterBasicInfo->second.strStName;
}
