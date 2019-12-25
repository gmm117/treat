#include "stdafx.h"
#include "CalcParser.h"


CCalcParser::CCalcParser()
{

}

CCalcParser::~CCalcParser()
{

}


CCalcParser& CCalcParser::Instance()
{
	static CCalcParser theInstance;
	return theInstance;
}

CString	CCalcParser::CalcTreat(long lIdx)
{
	double	dblCost = 0;
	double  dblTemp = 0;
	CString strCost = _T("");

	for (int nIdx = 0; nIdx < m_vecCurBasicData[lIdx].vecData.size(); nIdx++)
	{
		CString strTemp = m_vecCurBasicData[lIdx].vecData[nIdx];

		if (strTemp.Find('R') != -1)
		{
			long lIdx = _ttoi(strTemp.Mid(1));

			if (lIdx < 0)
			{
				lIdx *= -1;
				lIdx += 2;
			}
			
			CALCCOSTPROC  calcProc;

			calcProc = GetFunc(lIdx);
			
			dblCost = calcProc(dblCost);
			
			continue;
		}
		else if (strTemp.Find('C') != -1)
		{
			long lIdx = _ttoi(strTemp.Mid(1, 2));
			CString strPreCost = CalcTreat(lIdx);
			strPreCost.Remove(',');

			dblCost += _ttoi(strPreCost);
		}
		else if (strTemp.Find('D') != -1)
		{
			dblTemp = _tstof(m_vecBasicSuga[_ttoi(strTemp.Mid(1))].strCost);
		}
		else if ((strTemp.Compare(_T("+")) != 0) &&
				(strTemp.Compare(_T("-")) != 0) &&
				(strTemp.Compare(_T("*")) != 0) &&
				(strTemp.Compare(_T("/")) != 0))
		{
			dblTemp = _tstof(strTemp);
		}

		if (strTemp.Compare(_T("-")) == 0)
			dblCost -= dblTemp;
		else if (strTemp.Compare(_T("*")) == 0)
			dblCost *= dblTemp;
		else if (strTemp.Compare(_T("/")) == 0)
			dblCost /= dblTemp;
		else if (strTemp.Compare(_T("+")) == 0)
			dblCost += dblTemp;

	}

	strCost = MoneyFormat(dblCost);

	return strCost;
}

CString	CCalcParser::CalcHisCost(CString strCost, long lDivCost, CString strSatCost, CString strSatDiv)
{
	double dblCost = 0;
	double dblSatCost = 0;
	double dblSatDiv = 0;
	double dblDenoCnt = 100;

	strCost.Remove(',');
	strSatCost.Remove(',');

	dblCost = _ttoi(strCost);
	dblSatCost = _ttoi(strSatCost);
	dblSatDiv = _ttoi(strSatDiv);

	if (lDivCost > 100)
		dblDenoCnt = 1000;

	// 토요가산 계산을 위해서 수정함.
	if (dblSatDiv >= 0)
	{
		dblSatCost = dblSatCost * (dblSatDiv / 100);
	}

	dblCost -= dblSatCost;
	dblCost *= (static_cast<double>(lDivCost) / dblDenoCnt);

	CALCCOSTPROC  calcProc;
	calcProc = GetFunc(4); // 100원절사
	dblCost = calcProc(dblCost);

	strCost = MoneyFormat(dblCost);

	return strCost;
}

CString	CCalcParser::CalcSatCost(long lIdx)
{
	double	dblCost = 0;
	double  dblTemp = 0;
	CString strCost = _T("");
	bool	bSatFlag = false;

	for (int nIdx = 0; nIdx < m_vecCurBasicData[lIdx].vecData.size(); nIdx++)
	{
		CString strTemp = m_vecCurBasicData[lIdx].vecData[nIdx];

		if (strTemp.Find('C') != -1)
		{
			bSatFlag = true;
			m_vecCurBasicData[lIdx].strSatDiv = strTemp.Mid(3);
		}
		else if (strTemp.Find('R') != -1)
		{
			long lIdx = _ttoi(strTemp.Mid(1));

			if (lIdx < 0)
			{
				lIdx *= -1;
				lIdx += 2;
			}

			CALCCOSTPROC  calcProc;

			calcProc = GetFunc(lIdx);

			dblCost = calcProc(dblCost);

			continue;
		}
		else if (strTemp.Find('D') != -1)
		{
			dblTemp = _tstof(m_vecBasicSuga[_ttoi(strTemp.Mid(1))].strCost);
		}
		else if ((strTemp.Compare(_T("+")) != 0) &&
			(strTemp.Compare(_T("-")) != 0) &&
			(strTemp.Compare(_T("*")) != 0) &&
			(strTemp.Compare(_T("/")) != 0))
		{
			dblTemp = _tstof(strTemp);
		}

		if (strTemp.Compare(_T("-")) == 0)
			dblCost -= dblTemp;
		else if (strTemp.Compare(_T("*")) == 0)
			dblCost *= dblTemp;
		else if (strTemp.Compare(_T("/")) == 0)
			dblCost /= dblTemp;
		else if (strTemp.Compare(_T("+")) == 0)
			dblCost += dblTemp;
	}

	if (bSatFlag)
		strCost = MoneyFormat(dblCost);

	return strCost;
}