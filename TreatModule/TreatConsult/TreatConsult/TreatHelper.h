#ifndef	_HELPER_PARSER_H_
#define	_HELPER_PARSER_H_
#include "stdafx.h"

///	\brief	ù°�ڸ����� ����
///	\param	v	��
///	\return	����� ��
///	

// ù°�ڸ����� �����Ͽ� 10������ ����
// (ex.)	Floor0(123456) => 123450

static double Floor0(double v)
{
	v += 0.0000000001;

	long a = static_cast<long>(v);
	return a - (a % 10);
}



///	\brief	��°�ڸ����� ����
///	\param	v	��
///	\return	����� ��
///	

// ��°�ڸ����� �����Ͽ� 100������ ����
// (ex.)	Floor00(123456) => 123400
// double->float ����������ȯ�� �̻��� ���� ������ ���׼���

static double Floor1(double v)
{
	v += 0.0000000001;

	long a = static_cast<long>(v);
	return a - (a % 100);
}



///	\brief	�Ҽ���°�ڸ����� �ݿø�
///	\param	v	��
///	\return	�Ҽ���°�ڸ����� �ݿø��� ��
///	

///\brief �Ҽ� 3�ڸ����� 4��5���Ͽ� �Ҽ�2°�ڸ����� ����
///
///		(ex.)	RoundOffDot3(123.456) => 123.46
// double->float ����������ȯ�� �̻��� ���� ������ ���׼���

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



///	\brief	�Ҽ�ù°�ڸ����� �ݿø�
///	\param	v	��
///	\return	�Ҽ�ù°�ڸ����� �ݿø��� ��
///	

///\brief	�Ҽ�ù°�ڸ����� �ݿø�
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



///	\brief	ù°�ڸ����� �ݿø�
///	\param	v	��
///	\return	ù°�ڸ����� �ݿø��� ��
///	

///\brief	���������� 4��5���Ͽ� 10���������� ����
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
	////////////////////	����ΰ��
	if (money > 0)
	{
		static NUMBERFMT nFmt = { 0, 0, 3, ",", ",", 0 };
		TCHAR szVal[15];
		TCHAR szOut[15];
		_stprintf(szVal, "%s", StrFromInt64(money));
		GetNumberFormat(NULL, NULL, szVal, &nFmt, szOut, 32);
		strMoney.Format(_T("%s"), szOut);

	}
	else		////////////////////	�����ΰ��	
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