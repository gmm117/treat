#pragma once

#ifndef	_XML_BASICCONTROL_PARSER_H_
#define	_XML_BASICCONTROL_PARSER_H_

#include "stdafx.h"
#include "Xml.h"

class CXmlBasicControlParser
{

public:
	//////////////////////////////////////////////////////////////////////////////////
	// 생성자 소멸자																	//
	//////////////////////////////////////////////////////////////////////////////////
	CXmlBasicControlParser();
	~CXmlBasicControlParser();

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Function																//
	//////////////////////////////////////////////////////////////////////////////////
	bool	LoadXmlData();
	bool	SelectFileNode();
	bool	SelectTypeNode(CXMLNode, CRect&, _S_BASIC_CONTINFO&);
	bool	SelectRectNode(CXMLNode, CRect& rcRect);
	bool	SelectDataNode(CXMLNode, CRect& rcRect, _S_BASIC_CONTINFO&);

	long	GetTotalBasicContSize();
	long	GetCurControlSize(long);
	CString	GetCurStaticData(long);

	bool	LoadCurContInfo(long, _S_BASIC_CONTINFO&);
	

	_S_BASIC_CONTINFO GetSequenceData(long lContIdx)
	{
		_S_BASIC_CONTINFO struBasicContInfo;

		LoadCurContInfo(lContIdx, struBasicContInfo);

		return struBasicContInfo;
	};


	// SingleTon으로 구현
	static CXmlBasicControlParser& Instance();

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Values																//
	//////////////////////////////////////////////////////////////////////////////////
	CXMLDocument		 m_XmlDoc;
	std::vector<CString> m_vecXmlName;

	std::map<long, _S_BASIC_CONTINFO> m_mapTotBasicControl;

	struct Elem
	{
		CString strXmlName;
	};

	Elem entries[1];
};

#endif //_XML_BASICCONTROL_PARSER_H_

