#ifndef	_HELPER_PARSER_H_
#define	_HELPER_PARSER_H_
#include "stdafx.h"

///	\brief	첫째자리에서 절사
///	\param	v	값
///	\return	절사된 값
///	

// 첫째자리에서 절사하여 10단위로 맞춤
// (ex.)	Floor0(123456) => 123450

static double Floor0(double v)
{
	v += 0.0000000001;

	long a = static_cast<long>(v);
	return a - (a % 10);
}



///	\brief	둘째자리에서 절사
///	\param	v	값
///	\return	절사된 값
///	

// 둘째자리에서 절사하여 100단위로 맞춤
// (ex.)	Floor00(123456) => 123400
// double->float 묵시적형변환시 이상한 값이 들어오는 버그수정

static double Floor1(double v)
{
	v += 0.0000000001;

	long a = static_cast<long>(v);
	return a - (a % 100);
}



///	\brief	소수셋째자리에서 반올림
///	\param	v	값
///	\return	소수셋째자리에서 반올림된 값
///	

///\brief 소수 3자리에서 4사5입하여 소수2째자리까지 기입
///
///		(ex.)	RoundOffDot3(123.456) => 123.46
// double->float 묵시적형변환시 이상한 값이 들어오는 버그수정

static double RoundOffDot3(double v)
{
	v += 0.0000000001;

	long a = static_cast<long>(v);
	double b = v - static_cast<double>(a);
	b *= 100.0f;
	b += 0.5f;
	int c;
	c = (int)(b);
	return (a + (c) / 100.0f);
}



///	\brief	소수첫째자리에서 반올림
///	\param	v	값
///	\return	소수첫째자리에서 반올림된 값
///	

///\brief	소수첫째자리에서 반올림
///
///		(ex.)	RoundOffDot1(123.456) => 123

static double RoundOffDot0(double v)
{
	if (v > 0)
		v += 0.0000000001;

	long a = static_cast<long>(v);
	double b = v - a;
	long c = (b + 0.5f);
	return (a + c);
}



///	\brief	첫째자리에서 반올림
///	\param	v	값
///	\return	첫째자리에서 반올림된 값
///	

///\brief	원단위에서 4사5입하여 10원단위까지 기입
///
///		(ex.)	RoundOff0(123456) => 123460

static double RoundOff0(double v)
{
	v += 0.0000000001;

	return (static_cast<long>((v / 10.0f) + 0.5))*10.0f;
}

static CString StrFromInt64(__int64 nCnt)
{
	CString result;
	_i64toa(nCnt, result.GetBuffer(40), 10); // the 10 is the RADIX
	result.ReleaseBuffer();
	return result;
}

static CString MoneyFormat(__int64 money)
{
	CString strMoney;
	////////////////////	양수인경우
	if (money > 0)
	{
		static NUMBERFMT nFmt = { 0, 0, 3, ",", ",", 0 };
		TCHAR szVal[15];
		TCHAR szOut[15];
		_stprintf(szVal, "%s", StrFromInt64(money));
		GetNumberFormat(NULL, NULL, szVal, &nFmt, szOut, 32);
		strMoney.Format(_T("%s"), szOut);

	}
	else		////////////////////	음수인경우	
	{
		strMoney = StrFromInt64(money);
		int nLength = strMoney.GetLength();

		if (nLength <= 4)
			return strMoney;

		strMoney.Remove('-');
		int nPos = strMoney.Find(_T('.'));
		if (nPos == -1) nPos = nLength - 1;
		for (int i = nPos - 3; i>0; i -= 3)
		{
			strMoney.Insert(i, _T(','));
		}
		strMoney.Insert(0, _T('-'));
	}
	return strMoney;
}

#endif // _HELPER_PARSER_H_