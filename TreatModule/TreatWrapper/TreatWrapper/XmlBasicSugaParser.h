#pragma once
#ifndef	_XML_BASICSUGA_PARSER_H_
#define	_XML_BASICSUGA_PARSER_H_

#include "stdafx.h"
#include "Xml.h"

class CXmlBasicSugaParser
{
public:
	//////////////////////////////////////////////////////////////////////////////////
	// 생성자 소멸자																	//
	//////////////////////////////////////////////////////////////////////////////////
	CXmlBasicSugaParser();
	~CXmlBasicSugaParser();

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Function																//
	//////////////////////////////////////////////////////////////////////////////////
	void	AddVecXmlName();
	bool	LoadXmlData();
	bool	SelectFileNode(int nIdx);
	bool	SelectTypeNode(int nIdx, CXMLNode XmlNodeType, CString strStandDate);
	void	LoadMapXMLInfo(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA>& veCXmlBasicSugaParser);

	bool    InitEnvInfo(std::vector<long>& vecHospDiv, std::vector<CString>& vecStandDate);

	bool	SetSequenceData(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA> vecFixXMLParser);

	bool	SetXMLNode(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA>& vecFixXMLParser);
	bool	SetFileNode(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA>& vecFixXMLParser);
	bool	SetTypeNode(CXMLNode XmlNodeType, CString strStandDate, std::vector<_S_BASIC_SUGA>& vecFixXMLParser);

	bool	GetStandDate(long lIdx, CString& strStandDate);

	// SingleTon으로 구현
	static CXmlBasicSugaParser& Instance();

public:
	std::vector<_S_BASIC_SUGA> GetSequenceData(long lIdx, CString strStandDate)
	{
		std::vector<_S_BASIC_SUGA> veCXmlBasicSugaParser;

		if (!veCXmlBasicSugaParser.empty())
			veCXmlBasicSugaParser.clear();

		LoadMapXMLInfo(lIdx, strStandDate, veCXmlBasicSugaParser);

		return veCXmlBasicSugaParser;
	}

private:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Values																//
	//////////////////////////////////////////////////////////////////////////////////
	CXMLDocument		 m_XmlDoc;
	std::vector<CString> m_vecXmlName;
	std::map<CString, std::vector<_S_BASIC_SUGA> > m_mapCurBasicSuga;
	std::map<long, std::map<CString, std::vector<_S_BASIC_SUGA> > > m_mapTotBasicSuga;

private:
	// 병원종별 기초수가에 대한 정보를 얻어옴.
	struct Elem
	{
		long	lIdx;
		CString strXmlName;			
	};

	Elem entries[5];
};

#endif // _XML_BASICSUGA_PARSER_H_