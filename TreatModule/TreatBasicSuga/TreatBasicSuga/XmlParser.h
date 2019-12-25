#pragma once
#ifndef	_XML_PARSER_H_
#define	_XML_PARSER_H_

#include "stdafx.h"
#include "Xml.h"

class CXmlParser
{
public:
	//////////////////////////////////////////////////////////////////////////////////
	// 생성자 소멸자																	//
	//////////////////////////////////////////////////////////////////////////////////
	CXmlParser();
	~CXmlParser();

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Function																//
	//////////////////////////////////////////////////////////////////////////////////
	void	AddVecXmlName();
	bool	LoadXmlData();
	bool	SelectFileNode(int nIdx);
	bool	SelectTypeNode(int nIdx, CXMLNode XmlNodeType, CString strStandDate);
	void	LoadMapXMLInfo(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA>& vecXMLParser);

	bool    InitEnvInfo(std::vector<long>& vecHospDiv, std::vector<CString>& vecStandDate);

	bool	SetSequenceData(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA> vecFixXMLParser);

	bool	SetXMLNode(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA>& vecFixXMLParser);
	bool	SetFileNode(long lIdx, CString strStandDate, std::vector<_S_BASIC_SUGA>& vecFixXMLParser);
	bool	SetTypeNode(CXMLNode XmlNodeType, CString strStandDate, std::vector<_S_BASIC_SUGA>& vecFixXMLParser);

	// SingleTon으로 구현
	static CXmlParser& Instance();

public:
	std::vector<_S_BASIC_SUGA> GetSequenceData(long lIdx, CString strStandDate)
	{
		std::vector<_S_BASIC_SUGA> vecXMLParser;

		if (!vecXMLParser.empty())
			vecXMLParser.clear();

		LoadMapXMLInfo(lIdx, strStandDate, vecXMLParser);

		return vecXMLParser;
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

#endif // _XML_PARSER_H_