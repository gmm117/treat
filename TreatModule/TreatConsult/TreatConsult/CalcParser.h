#include "stdafx.h"
#include "TreatHelper.h"

#ifndef	_XML_CALCULATOR_PARSER_H_
#define	_XML_CALCULATOR_PARSER_H_

#pragma once

typedef double(*CALCCOSTPROC)(double dblValue);

class CCalcParser
{
public:
	//////////////////////////////////////////////////////////////////////////////////
	// 생성자 소멸자																	//
	//////////////////////////////////////////////////////////////////////////////////
	CCalcParser();
	~CCalcParser();

	// SingleTon으로 구현
	static CCalcParser& Instance();

public:
	std::vector<_S_BASIC_SUGA>		m_vecBasicSuga;
	std::vector<_S_BASIC_CONTINFO>	m_vecCurBasicData;

public:
	//////////////////////////////////////////////////////////////////////////////////
	// Member Function																//
	//////////////////////////////////////////////////////////////////////////////////
	CString		CalcTreat(long lIdx);
	CString		CalcHisCost(CString strCost, long lDivCost, CString strSatCost, CString strSatDiv);
	CString		CalcSatCost(long lIdx);

private:
	CALCCOSTPROC GetFunc(long lIdx)
	{
		CALCCOSTPROC func[] =
		{
			0L,
			&RoundOffDot0,
			&RoundOffDot3,
			&Floor0,
			&Floor1,
			&RoundOff0
		};

		return func[lIdx];
	}

};

#endif // _XML_CALCULATOR_PARSER_H_

