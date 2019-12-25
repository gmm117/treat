// ADO.cpp: implementation of the CADO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADO.h"
#include <math.h>
#include <atlapp.h>
#include <atlmisc.h>

#define		LCID_KOREA		1042
#define		LOCAL_LCID		LCID_KOREA

int GetLastDayOfMonth(int nYear, int nMonth)
{
	if(nMonth!=2)
	{
		int nRet =  30+((nMonth<=7)?(nMonth%2):(1-(nMonth%2)));
		return nRet;
	};

	if(nYear%4)
		if(nYear%100)
			if(nYear%400)
				return 29;
			else
				return 28;
		else
			return 29;
	else
		return 28;
}

//////////////////////////////////////////////////////////////////////
// CADOUtil class
BOOL CADOUtill::GetVariantValue(VARIANT varValue, BSTR* pbstrValue)
{
	USES_CONVERSION;
	switch(varValue.vt)
	{
	case VT_BOOL:
		return SUCCEEDED(VarBstrFromBool(varValue.boolVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_CY:
		return SUCCEEDED(VarBstrFromCy(varValue.cyVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_DATE:
		return SUCCEEDED(VarBstrFromDate(varValue.date, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_DECIMAL:
		return SUCCEEDED(VarBstrFromDec(&varValue.decVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_DISPATCH:
		return SUCCEEDED(VarBstrFromDisp(varValue.pdispVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_I1:
		return SUCCEEDED(VarBstrFromI1(varValue.cVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_I2:
		return SUCCEEDED(VarBstrFromI2(varValue.iVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_I4:
		return SUCCEEDED(VarBstrFromI4(varValue.lVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_R4:
		return SUCCEEDED(VarBstrFromR4(varValue.fltVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_R8:
		return SUCCEEDED(VarBstrFromR8(varValue.dblVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_BSTR:
		*pbstrValue = ::SysAllocString(varValue.bstrVal);
		return TRUE;

	case VT_UI1:
		return SUCCEEDED(VarBstrFromUI1(varValue.bVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_UI2:
		return SUCCEEDED(VarBstrFromUI2(varValue.uiVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	case VT_UI4:
		return SUCCEEDED(VarBstrFromUI4(varValue.ulVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pbstrValue));

	default:
		return FALSE;
	}
}

BOOL CADOUtill::GetVariantValue(VARIANT varValue, CString* pstrValue)
{
	USES_CONVERSION;

	CComBSTR bstrValue;
	if(CADOUtill::GetVariantValue(varValue, &bstrValue))
	{
		*pstrValue = OLE2CT(bstrValue);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOUtill::GetVariantValue(VARIANT varValue, long* plValue)
{
	switch(varValue.vt)
	{
	case VT_BOOL:
		return SUCCEEDED( VarI4FromBool(varValue.boolVal, plValue) );

	case VT_CY:
		return SUCCEEDED( VarI4FromCy(varValue.cyVal, plValue) );

	case VT_DATE:
		return SUCCEEDED( VarI4FromDate(varValue.date, plValue) );

	case VT_DECIMAL:
		return SUCCEEDED( VarI4FromDec(&varValue.decVal, plValue) );

	case VT_DISPATCH:
		return SUCCEEDED( VarI4FromDisp(varValue.pdispVal, LOCAL_LCID, plValue) );

	case VT_I1:
		return SUCCEEDED( VarI4FromI1(varValue.cVal, plValue) );

	case VT_I2:
		return SUCCEEDED( VarI4FromI2(varValue.iVal, plValue) );

	case VT_I4:
		*plValue = varValue.lVal;
		return TRUE;

	case VT_INT:
		return SUCCEEDED( VarI4FromInt(varValue.intVal, plValue) );

	case VT_R4:
		return SUCCEEDED( VarI4FromR4(varValue.fltVal, plValue) );

	case VT_R8:
		return SUCCEEDED( VarI4FromR8(varValue.dblVal, plValue) );

	case VT_BSTR:
		return SUCCEEDED( VarI4FromStr(varValue.bstrVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, plValue) );

	case VT_UI1:
		return SUCCEEDED( VarI4FromUI1(varValue.bVal, plValue) );

	case VT_UI2:
		return SUCCEEDED( VarI4FromUI2(varValue.uiVal, plValue) );

	case VT_UI4:
		return SUCCEEDED( VarI4FromUI4(varValue.ulVal, plValue) );

	default:
		return FALSE;
	}
}

BOOL CADOUtill::GetVariantValue(VARIANT varValue, short* pnValue)
{
	switch(varValue.vt)
	{
	case VT_BOOL:
		return SUCCEEDED( VarI2FromBool(varValue.boolVal, pnValue) );

	case VT_CY:
		return SUCCEEDED( VarI2FromCy(varValue.cyVal, pnValue) );

	case VT_DATE:
		return SUCCEEDED( VarI2FromDate(varValue.date, pnValue) );

	case VT_DECIMAL:
		return SUCCEEDED( VarI2FromDec(&varValue.decVal, pnValue) );

	case VT_DISPATCH:
		return SUCCEEDED( VarI2FromDisp(varValue.pdispVal, LOCAL_LCID, pnValue) );

	case VT_I1:
		return SUCCEEDED( VarI2FromI1(varValue.cVal, pnValue) );

	case VT_I2:
		*pnValue = varValue.iVal;
		return TRUE;

	case VT_I4:
		return SUCCEEDED( VarI2FromI4(varValue.lVal, pnValue) );

	case VT_INT:
		return SUCCEEDED( VarI2FromInt(varValue.intVal, pnValue) );

	case VT_R4:
		return SUCCEEDED( VarI2FromR4(varValue.fltVal, pnValue) );

	case VT_R8:
		return SUCCEEDED( VarI2FromR8(varValue.dblVal, pnValue) );

	case VT_BSTR:
		return SUCCEEDED( VarI2FromStr(varValue.bstrVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pnValue) );

	case VT_UI1:
		return SUCCEEDED( VarI2FromUI1(varValue.bVal, pnValue) );

	case VT_UI2:
		return SUCCEEDED( VarI2FromUI2(varValue.uiVal, pnValue) );

	case VT_UI4:
		return SUCCEEDED( VarI2FromUI4(varValue.ulVal, pnValue) );

	default:
		return FALSE;
	}
}

BOOL CADOUtill::GetVariantValue(VARIANT varValue, float* pfValue)
{
	switch(varValue.vt)
	{
	case VT_BOOL:
		return SUCCEEDED( VarR4FromBool(varValue.boolVal, pfValue) );

	case VT_CY:
		return SUCCEEDED( VarR4FromCy(varValue.cyVal, pfValue) );

	case VT_DATE:
		return SUCCEEDED( VarR4FromDate(varValue.date, pfValue) );

	case VT_DECIMAL:
		return SUCCEEDED( VarR4FromDec(&varValue.decVal, pfValue) );

	case VT_DISPATCH:
		return SUCCEEDED( VarR4FromDisp(varValue.pdispVal, LOCAL_LCID, pfValue) );

	case VT_I1:
		return SUCCEEDED( VarR4FromI1(varValue.cVal, pfValue) );

	case VT_I2:
		return SUCCEEDED( VarR4FromI2(varValue.iVal, pfValue) );

	case VT_I4:
		return SUCCEEDED( VarR4FromI4(varValue.lVal, pfValue) );

	case VT_R4:
		*pfValue = varValue.fltVal;
		return TRUE;

	case VT_R8:
		return SUCCEEDED( VarR4FromR8(varValue.dblVal, pfValue) );

	case VT_BSTR:
		return SUCCEEDED( VarR4FromStr(varValue.bstrVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pfValue) );

	case VT_UI1:
		return SUCCEEDED( VarR4FromUI1(varValue.bVal, pfValue) );

	case VT_UI2:
		return SUCCEEDED( VarR4FromUI2(varValue.uiVal, pfValue) );

	case VT_UI4:
		return SUCCEEDED( VarR4FromUI4(varValue.ulVal, pfValue) );

	default:
		return FALSE;
	}
}

BOOL CADOUtill::GetVariantValue(VARIANT varValue, double* pdblValue)
{
	switch(varValue.vt)
	{
	case VT_BOOL:
		return SUCCEEDED( VarR8FromBool(varValue.boolVal, pdblValue) );

	case VT_CY:
		return SUCCEEDED( VarR8FromCy(varValue.cyVal, pdblValue) );

	case VT_DATE:
		return SUCCEEDED( VarR8FromDate(varValue.date, pdblValue) );

	case VT_DECIMAL:
		return SUCCEEDED( VarR8FromDec(&varValue.decVal, pdblValue) );

	case VT_DISPATCH:
		return SUCCEEDED( VarR8FromDisp(varValue.pdispVal, LOCAL_LCID, pdblValue) );

	case VT_I1:
		return SUCCEEDED( VarR8FromI1(varValue.cVal, pdblValue) );

	case VT_I2:
		return SUCCEEDED( VarR8FromI2(varValue.iVal, pdblValue) );

	case VT_I4:
		return SUCCEEDED( VarR8FromI4(varValue.lVal, pdblValue) );

	case VT_R4:
		return SUCCEEDED( VarR8FromR4(varValue.fltVal, pdblValue) );

	case VT_R8:
		*pdblValue = varValue.dblVal;
		return TRUE;

	case VT_BSTR:
		return SUCCEEDED( VarR8FromStr(varValue.bstrVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pdblValue) );

	case VT_UI1:
		return SUCCEEDED( VarR8FromUI1(varValue.bVal, pdblValue) );

	case VT_UI2:
		return SUCCEEDED( VarR8FromUI2(varValue.uiVal, pdblValue) );

	case VT_UI4:
		return SUCCEEDED( VarR8FromUI4(varValue.ulVal, pdblValue) );

	default:
		return FALSE;
	}
}

BOOL CADOUtill::GetVariantValue(VARIANT varValue, BOOL* pbValue)
{
	VARIANT_BOOL* pvbValue = reinterpret_cast<VARIANT_BOOL*>(pbValue);
	switch(varValue.vt)
	{
	case VT_BOOL:
		*pbValue = (varValue.boolVal == VARIANT_TRUE);
		return TRUE;

	case VT_CY:
		return SUCCEEDED( VarBoolFromCy(varValue.cyVal, pvbValue) );

	case VT_DATE:
		return SUCCEEDED( VarBoolFromDate(varValue.date, pvbValue) );

	case VT_DECIMAL:
		return SUCCEEDED( VarBoolFromDec(&varValue.decVal, pvbValue) );

	case VT_DISPATCH:
		return SUCCEEDED( VarBoolFromDisp(varValue.pdispVal, LOCAL_LCID, pvbValue) );

	case VT_I1:
		return SUCCEEDED( VarBoolFromI1(varValue.cVal, pvbValue) );

	case VT_I2:
		return SUCCEEDED( VarBoolFromI2(varValue.iVal, pvbValue) );

	case VT_I4:
		return SUCCEEDED( VarBoolFromI4(varValue.lVal, pvbValue) );

	case VT_R4:
		return SUCCEEDED( VarBoolFromR4(varValue.fltVal, pvbValue) );

	case VT_R8:
		return SUCCEEDED( VarBoolFromR8(varValue.dblVal, pvbValue) );

	case VT_BSTR:
		return SUCCEEDED( VarBoolFromStr(varValue.bstrVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pvbValue) );

	case VT_UI1:
		return SUCCEEDED( VarBoolFromUI1(varValue.bVal, pvbValue) );

	case VT_UI2:
		return SUCCEEDED( VarBoolFromUI2(varValue.uiVal, pvbValue) );

	case VT_UI4:
		return SUCCEEDED( VarBoolFromUI4(varValue.ulVal, pvbValue) );

	default:
		return FALSE;
	}
}

BOOL CADOUtill::GetVariantValue(VARIANT varValue, SYSTEMTIME* pstValue)
{
	double dblTime;
	switch(varValue.vt)
	{
	case VT_BOOL:
		return SUCCEEDED(VarDateFromBool(varValue.boolVal, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_CY:
		return SUCCEEDED(VarDateFromCy(varValue.cyVal, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_DATE:
		{
			BOOL bReturnValue = VariantTimeToSystemTime(varValue.date, pstValue);

			//millisecond만 따로 얻어오는 부분
			//Edited by 이의균, 2003/11/21
			if(bReturnValue)
			{
				long milliseconds;
				double dOriginalValue = varValue.dblVal;
				double date_part;
				double time_part;
				double x;

				time_part = ::modf(dOriginalValue,&date_part);
				time_part *= 86400000.0F;
				x  = fmod(time_part,1000.0F);
				milliseconds = (long)x;
				x -= (double)milliseconds;
				if(x >= 0.50F)
				   milliseconds++;
				
				pstValue->wMilliseconds = milliseconds;
				
				//VariantTimeToSystemTime 은 milliseconds 없이 milliseconds를 반올림해 second에 반영한다.
				//milliseconds가 500이상일 경우 1초가 이미 더해진 상황이므로 1초를 빼주어야 한다.
				if(milliseconds>=500)
				{	
					pstValue->wSecond--;
					if(pstValue->wSecond == -1)
					{
						pstValue->wSecond = 59;
						pstValue->wMinute--;
						if(pstValue->wMinute == -1)
						{
							pstValue->wMinute = 59;
							pstValue->wHour--;
							if(pstValue->wHour == -1)
							{
								pstValue->wHour = 23;
								pstValue->wDay --;
								if(pstValue->wDay == 0)
								{
									//날짜가 0으로 되면 달을 한달 빼면서
									//달과 연 단위를 범위에 맞게 만든 다음
									//해당 현과 달에 맞추어 날짜의 최대값을 저장한다.
									pstValue->wMonth--;
									if(pstValue->wMonth == 0)
									{
										pstValue->wMonth = 12;
										pstValue->wYear--;
									}//월 범위 검사 끝

									pstValue->wDay = GetLastDayOfMonth(pstValue->wYear,pstValue->wMonth);
									
								}//일 범위 검사 끝
							}//시 범위 검사 끝
						}//분 범위 검사 끝
					}//초 범위 검사 끝
				}
			}
			return bReturnValue;
		}
		

	case VT_DECIMAL:
		return SUCCEEDED(VarDateFromDec(&varValue.decVal, &dblTime))&& VariantTimeToSystemTime(dblTime, pstValue);

	case VT_DISPATCH:
		return SUCCEEDED(VarDateFromDisp(varValue.pdispVal, LOCAL_LCID, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_I1:
		return SUCCEEDED(VarDateFromI1(varValue.cVal, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_I2:
		return SUCCEEDED(VarDateFromI2(varValue.iVal, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_I4:
		return SUCCEEDED(VarDateFromI4(varValue.lVal, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_R4:
		return SUCCEEDED(VarDateFromR4(varValue.fltVal, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_R8:
		return SUCCEEDED(VarDateFromR8(varValue.fltVal, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_BSTR:
		return SUCCEEDED(VarDateFromStr(varValue.bstrVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_UI1:
		return SUCCEEDED(VarDateFromUI1(varValue.bVal, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_UI2:
		return SUCCEEDED(VarDateFromUI2(varValue.uiVal, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	case VT_UI4:
		return SUCCEEDED(VarDateFromUI4(varValue.ulVal, &dblTime)) && VariantTimeToSystemTime(dblTime, pstValue);

	default:
		return FALSE;
	}
}

BOOL CADOUtill::GetVariantValue(VARIANT varValue, CHAR* pcValue)
{
	switch(varValue.vt)
	{
	case VT_BOOL:
		return SUCCEEDED( VarI1FromBool(varValue.boolVal, pcValue) );

	case VT_CY:
		return SUCCEEDED( VarI1FromCy(varValue.cyVal, pcValue) );

	case VT_DATE:
		return SUCCEEDED( VarI1FromDate(varValue.date, pcValue) );

	case VT_DECIMAL:
		return SUCCEEDED( VarI1FromDec(&varValue.decVal, pcValue) );

	case VT_DISPATCH:
		return SUCCEEDED( VarI1FromDisp(varValue.pdispVal, LOCAL_LCID, pcValue) );

	case VT_I1:
		*pcValue = varValue.cVal;
		return TRUE;

	case VT_I2:
		return SUCCEEDED( VarI1FromI2(varValue.iVal, pcValue) );

	case VT_I4:
		return SUCCEEDED( VarI1FromI4(varValue.lVal, pcValue) );

	case VT_R4:
		return SUCCEEDED( VarI1FromR4(varValue.fltVal, pcValue) );

	case VT_R8:
		return SUCCEEDED( VarI1FromR8(varValue.dblVal, pcValue) );

	case VT_BSTR:
		return SUCCEEDED( VarI1FromStr(varValue.bstrVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pcValue) );

	case VT_UI1:
		return SUCCEEDED( VarI1FromUI1(varValue.bVal, pcValue) );

	case VT_UI2:
		return SUCCEEDED( VarI1FromUI2(varValue.uiVal, pcValue) );

	case VT_UI4:
		return SUCCEEDED( VarI1FromUI4(varValue.ulVal, pcValue) );

	default:
		return FALSE;
	}
}

BOOL CADOUtill::GetVariantValue(VARIANT varValue, CY* pcyValue)
{
	switch(varValue.vt)
	{
	case VT_BOOL:
		return SUCCEEDED( VarCyFromBool(varValue.boolVal, pcyValue) );

	case VT_CY:
		*pcyValue = varValue.cyVal;
		return TRUE;

	case VT_DATE:
		return SUCCEEDED( VarCyFromDate(varValue.date, pcyValue) );

	case VT_DECIMAL:
		return SUCCEEDED( VarCyFromDec(&varValue.decVal, pcyValue) );

	case VT_DISPATCH:
		return SUCCEEDED( VarCyFromDisp(varValue.pdispVal, LOCAL_LCID, pcyValue) );

	case VT_I1:
		return SUCCEEDED( VarCyFromI1(varValue.cVal, pcyValue) );

	case VT_I2:
		return SUCCEEDED( VarCyFromI2(varValue.iVal, pcyValue) );

	case VT_I4:
		return SUCCEEDED( VarCyFromI4(varValue.lVal, pcyValue) );

	case VT_R4:
		return SUCCEEDED( VarCyFromR4(varValue.fltVal, pcyValue) );

	case VT_R8:
		return SUCCEEDED( VarCyFromR8(varValue.dblVal, pcyValue) );

	case VT_BSTR:
		return SUCCEEDED( VarCyFromStr(varValue.bstrVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pcyValue) );

	case VT_UI1:
		return SUCCEEDED( VarCyFromUI1(varValue.bVal, pcyValue) );

	case VT_UI2:
		return SUCCEEDED( VarCyFromUI2(varValue.uiVal, pcyValue) );

	case VT_UI4:
		return SUCCEEDED( VarCyFromUI4(varValue.ulVal, pcyValue) );

	default:
		return FALSE;
	}
}

BOOL CADOUtill::GetVariantValue(VARIANT varValue, DECIMAL* pdecValue)
{
	switch(varValue.vt)
	{
	case VT_BOOL:
		return SUCCEEDED( VarDecFromBool(varValue.boolVal, pdecValue) );

	case VT_CY:
		return SUCCEEDED( VarDecFromCy(varValue.cyVal, pdecValue) );

	case VT_DATE:
		return SUCCEEDED( VarDecFromDate(varValue.date, pdecValue) );

	case VT_DECIMAL:
		*pdecValue = varValue.decVal;
		return TRUE;

	case VT_DISPATCH:
		return SUCCEEDED( VarDecFromDisp(varValue.pdispVal, LOCAL_LCID, pdecValue) );

	case VT_I1:
		return SUCCEEDED( VarDecFromI1(varValue.cVal, pdecValue) );

	case VT_I2:
		return SUCCEEDED( VarDecFromI2(varValue.iVal, pdecValue) );

	case VT_I4:
		return SUCCEEDED( VarDecFromI4(varValue.lVal, pdecValue) );

	case VT_R4:
		return SUCCEEDED( VarDecFromR4(varValue.fltVal, pdecValue) );

	case VT_R8:
		return SUCCEEDED( VarDecFromR8(varValue.dblVal, pdecValue) );

	case VT_BSTR:
		return SUCCEEDED( VarDecFromStr(varValue.bstrVal, LOCAL_LCID, LOCALE_NOUSEROVERRIDE, pdecValue) );

	case VT_UI1:
		return SUCCEEDED( VarDecFromUI1(varValue.bVal, pdecValue) );

	case VT_UI2:
		return SUCCEEDED( VarDecFromUI2(varValue.uiVal, pdecValue) );

	case VT_UI4:
		return SUCCEEDED( VarDecFromUI4(varValue.ulVal, pdecValue) );

	default:
		return FALSE;
	}
}


//////////////////////////////////////////////////////////////////////
// CADOError class
CADOError::CADOError()
{
}

CADOError::CADOError(Error* pError)
{
	m_pobError = pError;
}

CADOError::~CADOError()
{
}

BOOL CADOError::GetDescription(CString* pstrDescription)
{
	// Description을 얻어옴
	CComBSTR bstrDescription;
	HRESULT hr = m_pobError->get_Description(&bstrDescription);
	if( SUCCEEDED(hr) )
	{
		USES_CONVERSION;
		*pstrDescription = OLE2CT(bstrDescription);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOError::GetHelpContext(long* plHelpContext)
{
	return SUCCEEDED( m_pobError->get_HelpContext(plHelpContext) );
}

BOOL CADOError::GetHelpFile(CString* pstrHelpFile)
{
	CComBSTR bstrHelpFile;
	HRESULT hr = m_pobError->get_HelpFile(&bstrHelpFile);
	if( SUCCEEDED(hr) )
	{
		USES_CONVERSION;
		*pstrHelpFile = OLE2CT(bstrHelpFile);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOError::GetNativeError(long* plNativeError)
{
	return SUCCEEDED( m_pobError->get_NativeError(plNativeError) );
}

BOOL CADOError::GetNumber(ErrorValueEnum *penErrorValue)
{
	return SUCCEEDED( m_pobError->get_Number(reinterpret_cast<long*>(penErrorValue)) );
}

BOOL CADOError::GetSource(CString* pstrSource)
{
	CComBSTR bstrSource;
	HRESULT hr = m_pobError->get_Source(&bstrSource);
	if( SUCCEEDED(hr) )
	{
		USES_CONVERSION;
		*pstrSource = OLE2CT(bstrSource);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOError::GetSQLState(CString* pstrSQLState)
{
	CComBSTR bstrSQLState;
	HRESULT hr = m_pobError->get_SQLState(&bstrSQLState);
	if( SUCCEEDED(hr) )
	{
		USES_CONVERSION;
		*pstrSQLState = OLE2CT(bstrSQLState);
		return TRUE;
	}
	else
		return FALSE;
}



//////////////////////////////////////////////////////////////////////
// CADOProperty class
CADOProperty::CADOProperty()
{
}

CADOProperty::~CADOProperty()
{
}

BOOL CADOProperty::GetAttributes(PropertyAttributesEnum* penPropertyAttributes)
{
	long lPropertyAttributes;
	if( SUCCEEDED(m_pobProperty->get_Attributes(&lPropertyAttributes)) )
	{
		*penPropertyAttributes = static_cast<PropertyAttributesEnum>(lPropertyAttributes);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOProperty::GetName(CString* pstrName)
{
	CComBSTR bstrName;
	HRESULT hr = m_pobProperty->get_Name(&bstrName);
	if( SUCCEEDED(hr) )
	{
		USES_CONVERSION;
		*pstrName = OLE2CT(bstrName);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOProperty::GetType(DataTypeEnum* penType)
{
	return SUCCEEDED( m_pobProperty->get_Type(penType) );
}

BOOL CADOProperty::GetValue(VARIANT *pvarValue)
{
	return SUCCEEDED( m_pobProperty->get_Value(pvarValue) );
}

BOOL CADOProperty::GetValue(long* plValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, plValue);
	else
		return FALSE;
}

BOOL CADOProperty::GetValue(short* pnValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pnValue);
	else
		return FALSE;
}

BOOL CADOProperty::GetValue(float* pfValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pfValue);
	else
		return FALSE;
}

BOOL CADOProperty::GetValue(double* pdblValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pdblValue);
	else
		return FALSE;
}

BOOL CADOProperty::GetValue(CString* pstrValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pstrValue);
	else
		return FALSE;
}

BOOL CADOProperty::GetValue(BOOL* pbValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pbValue);
	else
		return FALSE;
}

BOOL CADOProperty::GetValue(SYSTEMTIME* pstValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pstValue);
	else
		return FALSE;
}

BOOL CADOProperty::GetValue(CHAR* pcValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pcValue);
	else
		return FALSE;
}

BOOL CADOProperty::GetValue(CY* pcyValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pcyValue);
	else
		return FALSE;
}

BOOL CADOProperty::GetValue(DECIMAL* pdecValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pdecValue);
	else
		return FALSE;
}

BOOL CADOProperty::SetValue(VARIANT varValue)
{
	return SUCCEEDED( m_pobProperty->put_Value(varValue) );
}

BOOL CADOProperty::SetValue(long lValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_I4;
	varValue.lVal = lValue;
	return SetValue(varValue);
}

BOOL CADOProperty::SetValue(short nValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_I2;
	varValue.iVal = nValue;
	return SetValue(varValue);
}

BOOL CADOProperty::SetValue(float fValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_R4;
	varValue.fltVal = fValue;
	return SetValue(varValue);
}

BOOL CADOProperty::SetValue(double dblValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_R8;
	varValue.dblVal = dblValue;
	return SetValue(varValue);
}

BOOL CADOProperty::SetValue(LPCTSTR lpszValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_BSTR;
	varValue.bstrVal = T2BSTR(lpszValue);
	BOOL bResult = SetValue(varValue);
	::SysFreeString(varValue.bstrVal);
	return bResult;
}

BOOL CADOProperty::SetValue(BOOL bValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_BOOL;
	varValue.boolVal = static_cast<VARIANT_BOOL>(bValue);
	return SetValue(varValue);
}

BOOL CADOProperty::SetValue(SYSTEMTIME stValue)
{
	double dblValue;
	if(SystemTimeToVariantTime(&stValue, &dblValue))
	{
		CComVariant varValue;
		VariantInit(&varValue);
		varValue.vt = VT_DATE;
		varValue.date = dblValue;
		return SetValue(varValue);
	}
	else
		return FALSE;
}

BOOL CADOProperty::SetValue(CHAR cValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_I1;
	varValue.cVal = cValue;
	return SetValue(varValue);
}

BOOL CADOProperty::SetValue(CY cyValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_CY;
	varValue.cyVal = cyValue;
	return SetValue(varValue);
}

BOOL CADOProperty::SetValue(DECIMAL decValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_DECIMAL;
	varValue.decVal = decValue;
	return SetValue(varValue);
}



//////////////////////////////////////////////////////////////////////
// CADOField class
CADOField::CADOField()
{
}

CADOField::~CADOField()
{
}

BOOL CADOField::GetActualSize(long* plSize)
{
	return SUCCEEDED( m_pobField->get_ActualSize(plSize) );
}

BOOL CADOField::GetAttributes(FieldAttributeEnum* penFieldAttribute)
{
	return SUCCEEDED( m_pobField->get_Attributes(reinterpret_cast<long*>(penFieldAttribute)) );
}

BOOL CADOField::GetDefinedSize(long* plSize)
{
	return SUCCEEDED( m_pobField->get_DefinedSize(plSize) );
}

BOOL CADOField::GetName(CString* pstrName)
{
	CComBSTR bstrName;
	if( SUCCEEDED(m_pobField->get_Name(&bstrName)) )
	{
		USES_CONVERSION;
		*pstrName = OLE2CT(bstrName);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOField::GetNumericScale(BYTE* pbtNumericScale)
{	
	return SUCCEEDED(m_pobField->get_NumericScale(pbtNumericScale));
}

BOOL CADOField::SetNumericScale(BYTE btNumericScale)
{	
	return SUCCEEDED(m_pobField->put_NumericScale(btNumericScale));
}

BOOL CADOField::GetOriginalValue(VARIANT* pvarOriginalValue)
{
	return SUCCEEDED(m_pobField->get_OriginalValue(pvarOriginalValue));
}

BOOL CADOField::GetPrecision(BYTE* pbtPrecision)
{
	return SUCCEEDED(m_pobField->get_Precision(pbtPrecision));
}

BOOL CADOField::SetPrecision(BYTE btPrecision)
{
	return SUCCEEDED(m_pobField->put_Precision(btPrecision));
}

BOOL CADOField::GetPropertyCount(long* plPropertyCount)
{
	CComPtr<Properties> pProperties;
	HRESULT hr = m_pobField->get_Properties(&pProperties);
	if( FAILED(hr) )
		return FALSE;

	return SUCCEEDED( pProperties->get_Count(plPropertyCount) );
}

BOOL CADOField::GetProperty(long lIndex, CADOProperty* pobProperty)
{
	CComPtr<Properties> pProperties;
	HRESULT hr = m_pobField->get_Properties(&pProperties);
	if( FAILED(hr) )
		return FALSE;

	CComVariant varIndex;
	VariantInit(&varIndex);
	varIndex.vt = VT_I4;
	varIndex.lVal = lIndex;
	CComPtr<Property> pProperty;
	hr = pProperties->get_Item(varIndex, &pProperty);
	if( FAILED(hr) )
		return FALSE;
	
	pobProperty->m_pobProperty = pProperty;
	return TRUE;
}

BOOL CADOField::GetStatus(FieldStatusEnum* penFieldStatus)
{
	return SUCCEEDED( m_pobField->get_Status(reinterpret_cast<long*>(penFieldStatus)) );
}

BOOL CADOField::GetType(DataTypeEnum* penDataType)
{
	return SUCCEEDED( m_pobField->get_Type(penDataType) );
}

BOOL CADOField::SetType(DataTypeEnum enDataType)
{
	return SUCCEEDED( m_pobField->put_Type(enDataType) );
}

BOOL CADOField::GetUnderlyingValue(VARIANT* pvarUnderlyingValue)
{
	return SUCCEEDED( m_pobField->get_UnderlyingValue(pvarUnderlyingValue) );
}

BOOL CADOField::IsNull()
{
	CComVariant var;
	return (GetValue(&var) && var.vt == VT_NULL);
}

BOOL CADOField::GetValue(VARIANT *pvarValue)
{
	return SUCCEEDED( m_pobField->get_Value(pvarValue) );
}

BOOL CADOField::GetValue(long* plValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, plValue);
	else
		return FALSE;
}

BOOL CADOField::GetValue(short* pnValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pnValue);
	else
		return FALSE;
}

BOOL CADOField::GetValue(float* pfValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pfValue);
	else
		return FALSE;
}

BOOL CADOField::GetValue(double* pdblValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pdblValue);
	else
		return FALSE;
}

BOOL CADOField::GetValue(CString* pstrValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pstrValue);
	else
		return FALSE;
}

BOOL CADOField::GetValue(BOOL* pbValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pbValue);
	else
		return FALSE;
}

BOOL CADOField::GetValue(SYSTEMTIME* pstValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pstValue);
	else
		return FALSE;
}

BOOL CADOField::GetValue(CHAR* pcValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pcValue);
	else
		return FALSE;
}

BOOL CADOField::GetValue(CY* pcyValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pcyValue);
	else
		return FALSE;
}

BOOL CADOField::GetValue(DECIMAL* pdecValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pdecValue);
	else
		return FALSE;
}

BOOL CADOField::GetValue(BSTR *pbstrValue)
{
	CComVariant varValue;
	if( GetValue(&varValue) )
		return CADOUtill::GetVariantValue(varValue, pbstrValue);
	else
		return FALSE;
}

BOOL CADOField::SetValue(VARIANT varValue)
{
	return SUCCEEDED( m_pobField->put_Value(varValue) );
}

BOOL CADOField::SetValue(long lValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_I4;
	varValue.lVal = lValue;
	return SetValue(varValue);
}

BOOL CADOField::SetValue(short nValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_I2;
	varValue.iVal = nValue;
	return SetValue(varValue);
}

BOOL CADOField::SetValue(float fValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_R4;
	varValue.fltVal = fValue;
	return SetValue(varValue);
}

BOOL CADOField::SetValue(double dblValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_R8;
	varValue.dblVal = dblValue;
	return SetValue(varValue);
}

BOOL CADOField::SetValue(LPCTSTR lpszValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_BSTR;
	varValue.bstrVal = T2BSTR(lpszValue);
	return SetValue(varValue);
}

BOOL CADOField::SetValue(BOOL bValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_BOOL;
	varValue.boolVal = static_cast<VARIANT_BOOL>(bValue);
	return SetValue(varValue);
}

BOOL CADOField::SetValue(SYSTEMTIME stValue)
{
	double dblValue;
	if(SystemTimeToVariantTime(&stValue, &dblValue))
	{
		CComVariant varValue;
		VariantInit(&varValue);
		varValue.vt = VT_DATE;
		varValue.date = dblValue;
		return SetValue(varValue);
	}
	else
		return FALSE;
}

BOOL CADOField::SetValue(CHAR cValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_I1;
	varValue.cVal = cValue;
	return SetValue(varValue);
}

BOOL CADOField::SetValue(CY cyValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_CY;
	varValue.cyVal = cyValue;
	return SetValue(varValue);
}

BOOL CADOField::SetValue(DECIMAL decValue)
{
	CComVariant varValue;
	VariantInit(&varValue);
	varValue.vt = VT_DECIMAL;
	varValue.decVal = decValue;
	return SetValue(varValue);
}

BOOL CADOField::AppendChunk(VARIANT varData)
{
	return SUCCEEDED(m_pobField->AppendChunk(varData));
}

BOOL CADOField::GetChunk(long lLength, VARIANT* pvarData)
{
	return SUCCEEDED(m_pobField->GetChunk(lLength, pvarData));
}




//////////////////////////////////////////////////////////////////////
// CADOCommand class
CADOCommand::CADOCommand()
{

}

CADOCommand::CADOCommand(_Command* pCommand)
{
	m_pobCommand = pCommand;
}

CADOCommand::~CADOCommand()
{
}

BOOL CADOCommand::GetActiveConnection(CADOConnection *pobConnection)
{
	return SUCCEEDED( m_pobCommand->get_ActiveConnection(&pobConnection->m_pobConnection) );
}

BOOL CADOCommand::SetActiveConnection(LPCTSTR lpszConnStr)
{
	CComVariant varConnStr;
	VariantInit(&varConnStr);
	varConnStr.vt = VT_BSTR;
	varConnStr.bstrVal = T2BSTR(lpszConnStr);
	return SUCCEEDED( m_pobCommand->put_ActiveConnection(varConnStr) );
}

BOOL CADOCommand::SetActiveConnection(CADOConnection *pobConnection)
{
	CComVariant varConnection;
	VariantInit(&varConnection);
	varConnection.vt = VT_UNKNOWN;
	HRESULT hr = pobConnection->m_pobConnection->QueryInterface( &varConnection.punkVal );
	if( FAILED(hr) )
		return FALSE;
	
	return SUCCEEDED( m_pobCommand->put_ActiveConnection(varConnection) );
}

BOOL CADOCommand::GetCommandStream(IStream* pStream)
{
	CComVariant varStream;
	VariantInit(&varStream);
	HRESULT hr = SUCCEEDED( m_pobCommand->get_CommandStream(&varStream) );
	if(FAILED(hr))
		return hr;
	else
		return varStream.punkVal->QueryInterface(&pStream);
}

BOOL CADOCommand::GetCommandText(CString* pstrCommand)
{
	CComBSTR bstrCommand;
	HRESULT hr = m_pobCommand->get_CommandText(&bstrCommand);
	if( FAILED(hr) )
		return FALSE;

	USES_CONVERSION;
	*pstrCommand = OLE2CT(bstrCommand);
	return TRUE;
}

BOOL CADOCommand::SetCommandText(LPCTSTR lpszCommand)
{
	USES_CONVERSION;
	CComBSTR bstrCommand = T2BSTR(lpszCommand);
	HRESULT hr = m_pobCommand->put_CommandText(bstrCommand);
	return SUCCEEDED(hr);
}

BOOL CADOCommand::GetCommandTimeout(long* plSeconds)
{
	return SUCCEEDED(m_pobCommand->get_CommandTimeout(plSeconds));
}

BOOL CADOCommand::SetCommandTimeout(long lSeconds)
{
	return SUCCEEDED(m_pobCommand->put_CommandTimeout(lSeconds));
}

BOOL CADOCommand::GetCommandTypeEnum(CommandTypeEnum* penType)
{
	return SUCCEEDED(m_pobCommand->get_CommandType(penType));
}

BOOL CADOCommand::SetCommandTypeEnum(CommandTypeEnum enType)
{
	return SUCCEEDED(m_pobCommand->put_CommandType(enType));
}

BOOL CADOCommand::GetDialect(CString* pstrDialect)
{
	CComBSTR bstrDialect;
	HRESULT hr = m_pobCommand->get_Dialect(&bstrDialect);
	if( SUCCEEDED(hr) )
	{
		USES_CONVERSION;
		*pstrDialect = OLE2CT(bstrDialect);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOCommand::SetDialect(LPCTSTR lpszDialect)
{
	USES_CONVERSION;
	CComBSTR bstrDialect = lpszDialect;
	HRESULT hr = m_pobCommand->put_Dialect(bstrDialect);
	return SUCCEEDED(hr);
}

BOOL CADOCommand::GetName(CString* pstrName)
{
	CComBSTR bstrName;
	HRESULT hr = m_pobCommand->get_Name(&bstrName);
	if(SUCCEEDED(hr))
	{
		USES_CONVERSION;
		*pstrName = OLE2CT(bstrName);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOCommand::SetName(LPCTSTR lpszName)
{
	USES_CONVERSION;
	CComBSTR bstrName = T2BSTR(lpszName);
	return SUCCEEDED( m_pobCommand->put_Name(bstrName) );
}

BOOL CADOCommand::GetNamedParameters(BOOL* pbNamed)
{
	return SUCCEEDED( m_pobCommand->get_NamedParameters(reinterpret_cast<VARIANT_BOOL*>(pbNamed)) );
}

BOOL CADOCommand::SetNamedParameters(BOOL bNamed)
{
	return SUCCEEDED( m_pobCommand->put_NamedParameters(static_cast<VARIANT_BOOL>(bNamed)) );
}

BOOL CADOCommand::GetParameterCount(long *plCount)
{
	CComPtr<Parameters> pParameters;
	HRESULT hr = m_pobCommand->get_Parameters(&pParameters);
	if( FAILED(hr) )
		return FALSE;
	else
		return SUCCEEDED( pParameters->get_Count(plCount) );
}

BOOL CADOCommand::GetParameter(long lIndex, CADOParameter* pobParameter)
{
	CComPtr<Parameters> pParameters;
	HRESULT hr = m_pobCommand->get_Parameters(&pParameters);
	if( FAILED(hr) )
		return FALSE;

	CComVariant varIndex;
	VariantInit(&varIndex);
	varIndex.vt = VT_I4;
	varIndex.lVal = lIndex;
	CComPtr<_Parameter> pParameter;
	hr = pParameters->get_Item(varIndex, &pParameter);
	if( FAILED(hr) )
		return FALSE;
	
	pobParameter->m_pobParameter = pParameter;
	return TRUE;
}

BOOL CADOCommand::GetPrepared(BOOL* pbPrepared)
{
	return SUCCEEDED( m_pobCommand->get_Prepared(reinterpret_cast<VARIANT_BOOL*>(pbPrepared)) );
}

BOOL CADOCommand::SetPrepared(BOOL bPrepared)
{
	return SUCCEEDED( m_pobCommand->put_Prepared(static_cast<VARIANT_BOOL>(bPrepared)) );
}

BOOL CADOCommand::GetPropertiesCount(long *plCount)
{	
	CComPtr<Properties> pProperties;
	HRESULT hr = m_pobCommand->get_Properties(&pProperties);
	if( FAILED(hr) )
		return FALSE;

	return SUCCEEDED( pProperties->get_Count(plCount) );
}

BOOL CADOCommand::GetProperty(long lIndex, CADOProperty* pobProperty)
{
	CComPtr<Properties> pProperties;
	HRESULT hr = m_pobCommand->get_Properties(&pProperties);
	if( FAILED(hr) )
		return FALSE;

	CComVariant varIndex;
	VariantInit(&varIndex);
	varIndex.vt = VT_I4;
	varIndex.lVal = lIndex;
	CComPtr<Property> pProperty;
	hr = pProperties->get_Item(varIndex, &pProperty);
	if( FAILED(hr) )
		return FALSE;

	pobProperty->m_pobProperty = pProperty;
	return TRUE;
}

BOOL CADOCommand::GetState(ObjectStateEnum* penState)
{
	return SUCCEEDED( m_pobCommand->get_State(reinterpret_cast<long*>(penState)) );
}

BOOL CADOCommand::Cancel()
{	
	return SUCCEEDED(m_pobCommand->Cancel());
}

BOOL CADOCommand::CreateParameter(LPCTSTR lpszName, DataTypeEnum enType, ParameterDirectionEnum enDirection, long lSize, VARIANT varValue, CADOParameter* pParameter)
{
	USES_CONVERSION;
	CComBSTR bstrName = T2BSTR(lpszName);
	return SUCCEEDED( m_pobCommand->CreateParameter(bstrName, enType, enDirection, lSize, varValue, &pParameter->m_pobParameter) );
}

BOOL CADOCommand::Execute(long* plRecordsAffected, VARIANT* pvarParameters, long lOptions, CADORecordset* pRecordset)
{
	CComVariant varRecordsAffected;
	if( SUCCEEDED(m_pobCommand->Execute(&varRecordsAffected, pvarParameters, lOptions, &pRecordset->m_pobRecordset)) )
	{
		if(varRecordsAffected.vt = VT_I4)
			*plRecordsAffected = varRecordsAffected.lVal;
		return TRUE;
	}
	else
		return FALSE;
}


//////////////////////////////////////////////////////////////////////
// CADORecord class
CADORecord::CADORecord()
{
}

CADORecord::CADORecord(_Record* pRecord)
{
	m_pobRecord = pRecord;
}

CADORecord::~CADORecord()
{
}

BOOL CADORecord::GetActiveConnection(CADOConnection* pobDbConn)
{
	CComVariant varConnection;	
	if( SUCCEEDED(m_pobRecord->get_ActiveConnection(&varConnection)) && varConnection.vt == VT_UNKNOWN )
	{
		if( SUCCEEDED(varConnection.punkVal->QueryInterface(&pobDbConn->m_pobConnection)) )
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}

BOOL CADORecord::SetActiveConnection(LPCTSTR lpszConnectionStr)
{
	return SUCCEEDED(m_pobRecord->put_ActiveConnection(CComBSTR(lpszConnectionStr)));
}

BOOL CADORecord::GetFieldCount(long *plCount)
{
	CComPtr<Fields> pFields;
	HRESULT hr = m_pobRecord->get_Fields(&pFields);
	if( FAILED(hr) )
		return FALSE;

	return SUCCEEDED( pFields->get_Count(plCount) );
}

BOOL CADORecord::GetField(long lIndex, CADOField* pobField)
{
	CComPtr<Fields> pFields;
	HRESULT hr = m_pobRecord->get_Fields(&pFields);
	if( FAILED(hr) )
		return FALSE;

	CComVariant varIndex;
	VariantInit(&varIndex);
	varIndex.vt = VT_I4;
	varIndex.lVal = lIndex;
	CComPtr<Field> pField;
	hr = pFields->get_Item(varIndex, &pField);
	if( FAILED(hr) )
		return FALSE;

	pobField->m_pobField = pField;
	return TRUE;
}

BOOL CADORecord::GetMode(ConnectModeEnum* penMode)
{
	return SUCCEEDED(m_pobRecord->get_Mode(penMode));
}

BOOL CADORecord::SetMode(ConnectModeEnum enMode)
{
	return SUCCEEDED(m_pobRecord->put_Mode(enMode));
}

BOOL CADORecord::GetParentURL(CString* pstrParentURL)
{
	CComBSTR bstrParentURL;
	HRESULT hr = m_pobRecord->get_ParentURL(&bstrParentURL);	
	if(SUCCEEDED(hr))
	{
		USES_CONVERSION;
		*pstrParentURL = OLE2CT(bstrParentURL);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecord::GetPropertyCount(long *plCount)
{
	CComPtr<Properties> pProperties;
	HRESULT hr = m_pobRecord->get_Properties(&pProperties);
	if( FAILED(hr) )
		return FALSE;

	return SUCCEEDED( pProperties->get_Count(plCount) );
}

BOOL CADORecord::GetProperty(long lIndex, CADOProperty* pobProperty)
{
	CComPtr<Properties> pProperties;
	HRESULT hr = m_pobRecord->get_Properties(&pProperties);
	if( FAILED(hr) )
		return FALSE;

	CComVariant varIndex;
	VariantInit(&varIndex);
	varIndex.vt = VT_I4;
	varIndex.lVal = lIndex;
	CComPtr<Property> pProperty;
	hr = pProperties->get_Item(varIndex, &pProperty);
	if( FAILED(hr) )
		return FALSE;

	pobProperty->m_pobProperty = pProperty;
	return TRUE;
}

BOOL CADORecord::GetRecordType(RecordTypeEnum* penRecordType)
{
	return SUCCEEDED(m_pobRecord->get_RecordType(penRecordType));
}

BOOL CADORecord::GetSource(VARIANT* pvarSource)
{
	return SUCCEEDED(m_pobRecord->get_Source(pvarSource));
}

BOOL CADORecord::SetSource(LPCTSTR lpszSource)
{
	return SUCCEEDED(m_pobRecord->put_Source(CComBSTR(lpszSource)));
}

BOOL CADORecord::GetState(ObjectStateEnum* penState)
{
	return SUCCEEDED(m_pobRecord->get_State(penState));
}

BOOL CADORecord::Cancel()
{
	return SUCCEEDED(m_pobRecord->Cancel());
}

BOOL CADORecord::Close()
{
	return SUCCEEDED(m_pobRecord->Close());
}

BOOL CADORecord::CopyRecord(CString strSource, CString strDestination, CString strUserName, CString strPassword, CopyRecordOptionsEnum enOptions, BOOL bAsync, CString* pstrNewURL)
{	
    BSTR bstrSource = strSource.AllocSysString();
    BSTR bstrDestination = strDestination.AllocSysString();
    BSTR bstrUserName = strUserName.AllocSysString();
    BSTR bstrPassword = strPassword.AllocSysString();
    BSTR bstrNewURL;
	HRESULT hr = m_pobRecord->CopyRecord(bstrSource, bstrDestination, bstrUserName, bstrPassword, enOptions, bAsync, &bstrNewURL);
	::SysFreeString(bstrSource);
	::SysFreeString(bstrDestination);
	::SysFreeString(bstrUserName);
	::SysFreeString(bstrPassword);
	if(SUCCEEDED(hr))
	{
		USES_CONVERSION;
		*pstrNewURL = OLE2CT(bstrNewURL);
		::SysFreeString(bstrNewURL);
		return TRUE;
	}
	else
		return FALSE;

}

BOOL CADORecord::DeleteRecord(CString strSource, BOOL bAsync)
{
	return SUCCEEDED(m_pobRecord->DeleteRecord(CComBSTR(strSource), static_cast<VARIANT_BOOL>(bAsync)));
}

BOOL CADORecord::GetChildren(CADORecordset* pobRecordset)
{
	return SUCCEEDED(m_pobRecord->GetChildren(&pobRecordset->m_pobRecordset));
}

BOOL CADORecord::MoveRecord(CString strSource, CString strDestination, CString strUserName, CString strPassword, MoveRecordOptionsEnum enRecordOptions, BOOL bAsync, CString* pstrNewURL)
{
	CComBSTR bstrNewURL;
	HRESULT hr = m_pobRecord->MoveRecord(CComBSTR(strSource), CComBSTR(strDestination), CComBSTR(strUserName), CComBSTR(strPassword), enRecordOptions, static_cast<VARIANT_BOOL>(bAsync), &bstrNewURL);
	if(SUCCEEDED(hr))
	{
		USES_CONVERSION;
		*pstrNewURL = OLE2CT(bstrNewURL);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecord::Open(VARIANT varSource, VARIANT varActiveConnection, ConnectModeEnum enMode, RecordCreateOptionsEnum enCreateOptions, RecordOpenOptionsEnum enOpenOptions, CString strUserName, CString strPassword)
{
	return SUCCEEDED(m_pobRecord->Open(varSource, varActiveConnection, enMode, enCreateOptions, enOpenOptions, CComBSTR(strUserName), CComBSTR(strPassword)));
}

BOOL CADORecord::Open(CString strSource, CString strConnectionStr, ConnectModeEnum enMode, RecordCreateOptionsEnum enCreateOptions, RecordOpenOptionsEnum enOpenOptions, CString strUserName, CString strPassword)
{
	CComVariant varSource;
	VariantInit(&varSource);
	varSource.vt = VT_BSTR;
	varSource.bstrVal = strSource.AllocSysString();

	CComVariant varConnectionStr;
	VariantInit(&varConnectionStr);
	varConnectionStr.vt = VT_BSTR;
	varConnectionStr.bstrVal = strConnectionStr.AllocSysString();

	return Open(varSource, varConnectionStr, enMode, enCreateOptions, enOpenOptions, strUserName, strPassword);
}

BOOL CADORecord::Open(CString strSource, CADOConnection* pobDbConn, ConnectModeEnum enMode, RecordCreateOptionsEnum enCreateOptions, RecordOpenOptionsEnum enOpenOptions, CString strUserName, CString strPassword)
{
	CComVariant varSource;
	VariantInit(&varSource);
	varSource.vt = VT_BSTR;
	varSource.bstrVal = strSource.AllocSysString();

	CComVariant varConnectionStr;
	VariantInit(&varConnectionStr);
	varConnectionStr.vt = VT_UNKNOWN;
	varConnectionStr.punkVal = pobDbConn->m_pobConnection;

	return Open(varSource, varConnectionStr, enMode, enCreateOptions, enOpenOptions, strUserName, strPassword);
}

BOOL CADORecord::Open(CADOCommand* pobCommand, CString strConnectionStr, ConnectModeEnum enMode, RecordCreateOptionsEnum enCreateOptions, RecordOpenOptionsEnum enOpenOptions, CString strUserName, CString strPassword)
{
	CComVariant varSource;
	VariantInit(&varSource);
	varSource.vt = VT_UNKNOWN;
	varSource.punkVal = pobCommand->m_pobCommand;

	CComVariant varConnectionStr;
	VariantInit(&varConnectionStr);
	varConnectionStr.vt = VT_BSTR;
	varConnectionStr.bstrVal = strConnectionStr.AllocSysString();

	return Open(varSource, varConnectionStr, enMode, enCreateOptions, enOpenOptions, strUserName, strPassword);
}

BOOL CADORecord::Open(CADOCommand* pobCommand, CADOConnection* pobDbConn, ConnectModeEnum enMode, RecordCreateOptionsEnum enCreateOptions, RecordOpenOptionsEnum enOpenOptions, CString strUserName, CString strPassword)
{
	CComVariant varSource;
	VariantInit(&varSource);
	varSource.vt = VT_UNKNOWN;
	varSource.punkVal = pobCommand->m_pobCommand;

	CComVariant varConnectionStr;
	VariantInit(&varConnectionStr);
	varConnectionStr.vt = VT_UNKNOWN;
	varConnectionStr.punkVal = pobDbConn->m_pobConnection;

	return Open(varSource, varConnectionStr, enMode, enCreateOptions, enOpenOptions, strUserName, strPassword);
}



//////////////////////////////////////////////////////////////////////
// CADORecordset class
CADORecordset::CADORecordset()
{
	m_pobRecordset.CoCreateInstance(__uuidof(Recordset));
}

CADORecordset::CADORecordset(_Recordset *pRecordset)
{
	ATLASSERT(m_pobRecordset == NULL);
	m_pobRecordset = pRecordset;
}

CADORecordset::~CADORecordset()
{
	if(m_pobRecordset != NULL && IsOpen())
		Close();
}

void CADORecordset::operator=(CADORecordset& obRecordset)
{
	if(m_pobRecordset)
		m_pobRecordset.Release();
	
	HRESULT hr = obRecordset.m_pobRecordset.CopyTo(&m_pobRecordset);
	ATLASSERT( SUCCEEDED(hr) );
}


BOOL CADORecordset::GetAbsolutePage(PositionEnum* penPos)
{
	return SUCCEEDED( m_pobRecordset->get_AbsolutePage(penPos) );
}

BOOL CADORecordset::SetAbsolutePage(PositionEnum enPos)
{
	return SUCCEEDED( m_pobRecordset->put_AbsolutePage(enPos) );
}

BOOL CADORecordset::GetAbsolutePosition(PositionEnum* penPos)
{
	return SUCCEEDED( m_pobRecordset->get_AbsolutePosition(penPos) );
}	

BOOL CADORecordset::SetAbsolutePosition(PositionEnum enPos)
{
	return SUCCEEDED( m_pobRecordset->put_AbsolutePosition(enPos) );
}

BOOL CADORecordset::GetActiveCommand(CADOCommand *pobCommand)
{
	IDispatch* piDispatch = NULL;
	HRESULT hr = pobCommand->m_pobCommand->QueryInterface( __uuidof(IDispatch), reinterpret_cast<void**>(&piDispatch) );
	if( FAILED(hr) )
		return FALSE;
	
	hr = m_pobRecordset->get_ActiveCommand(&piDispatch);
	if( FAILED(hr) )
		return FALSE;

	return TRUE;
}

BOOL CADORecordset::GetActiveConnection(VARIANT* pvarConnection)
{
	/*
		이 함수는 Connection 상태에서는 Connection 객체를,
		Close 상태에서는 Connection String을 전달하므로 Variant를 사용함
	*/

	return SUCCEEDED( m_pobRecordset->get_ActiveConnection(pvarConnection) );
}

BOOL CADORecordset::GetActiveConnection(CString* pstrConnection)
{
	CComVariant varConnectionStr;
	if( GetActiveConnection(&varConnectionStr) && varConnectionStr.vt == VT_BSTR )
	{
		USES_CONVERSION;
		*pstrConnection = OLE2CT(varConnectionStr.bstrVal);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::GetActiveConnection(CADOConnection* pDbConn)
{
	if(pDbConn->m_pobConnection)
		pDbConn->m_pobConnection.Release();

	CComVariant varConnection;
	if( GetActiveConnection(&varConnection) && varConnection.vt == VT_DISPATCH )
		return SUCCEEDED( varConnection.pdispVal->QueryInterface(&pDbConn->m_pobConnection) );
	else
		return FALSE;
}

BOOL CADORecordset::SetActiveConnection(VARIANT varConnection)
{
	/*
		이 함수는 Connection 상태에서는 Connection 객체를,
		Close 상태에서는 Connection String을 전달하므로 Variant를 사용함
	*/

	return SUCCEEDED( m_pobRecordset->put_ActiveConnection(varConnection) );
}

BOOL CADORecordset::SetActiveConnection(CString strConnection)
{
	CComVariant varConnection;
	VariantInit(&varConnection);
	varConnection.vt = VT_BSTR;
	varConnection.bstrVal = strConnection.AllocSysString();
	return SetActiveConnection(varConnection);
}

BOOL CADORecordset::SetActiveConnection(CADOConnection *pDbConn)
{
	CComVariant varConnection;
	VariantInit(&varConnection);
	varConnection.vt = VT_UNKNOWN;
	return SUCCEEDED(pDbConn->m_pobConnection->QueryInterface(&varConnection.punkVal));
}

BOOL CADORecordset::IsEOF()
{	
	VARIANT_BOOL vbEOF;
	if( FAILED(m_pobRecordset->get_EOF(&vbEOF)) )
		return TRUE;

	return (vbEOF == VARIANT_TRUE);
}

BOOL CADORecordset::IsBOF()
{
	VARIANT_BOOL vbBOF;
	if( FAILED(m_pobRecordset->get_BOF(&vbBOF)) )
		return TRUE;

	return (vbBOF == VARIANT_TRUE);
}

BOOL CADORecordset::IsOpen()
{
	BOOL bOpen;
	if( IsOpen(&bOpen) && bOpen )
		return TRUE;
	else
		return FALSE;
}

BOOL CADORecordset::GetBookmark(VARIANT* pvarBookmark)
{
	return SUCCEEDED( m_pobRecordset->get_Bookmark(pvarBookmark) );
}

BOOL CADORecordset::SetBookmark(VARIANT varBookmark)
{
	return SUCCEEDED( m_pobRecordset->put_Bookmark(varBookmark) );
}

BOOL CADORecordset::GetCacheSize(long* plSize)
{
	return SUCCEEDED( m_pobRecordset->get_CacheSize(plSize) );
}

BOOL CADORecordset::SetCacheSize(long lSize)
{
	return SUCCEEDED( m_pobRecordset->put_CacheSize(lSize) );
}

BOOL CADORecordset::GetCursorLocation(CursorLocationEnum* penLoc)
{
	return SUCCEEDED( m_pobRecordset->get_CursorLocation(penLoc) );
}

BOOL CADORecordset::SetCursorLocation(CursorLocationEnum enLoc)
{
	return SUCCEEDED( m_pobRecordset->put_CursorLocation(enLoc) );
}

BOOL CADORecordset::GetCursorType(CursorTypeEnum* penType)
{
	return SUCCEEDED( m_pobRecordset->get_CursorType(penType) );
}

BOOL CADORecordset::SetCursorType(CursorTypeEnum enType)
{
	return SUCCEEDED( m_pobRecordset->put_CursorType(enType) );
}

BOOL CADORecordset::GetDataMember(CString* pstrDataMember)
{
	CComBSTR bstrDataMember;
	HRESULT hr = m_pobRecordset->get_DataMember(&bstrDataMember);
	if( FAILED(hr) )
		return FALSE;
	else
	{
		USES_CONVERSION;
		*pstrDataMember = OLE2CT(bstrDataMember);
		return TRUE;
	}
}

BOOL CADORecordset::SetDataMember(CString strDataMember)
{
	return SUCCEEDED(m_pobRecordset->put_DataMember(CComBSTR(strDataMember)));
}

BOOL CADORecordset::GetDataSource(IUnknown **ppUnkn)
{
	return SUCCEEDED( m_pobRecordset->get_DataSource(ppUnkn) );
}

BOOL CADORecordset::GetEditMode(EditModeEnum* penMode)
{
	return SUCCEEDED( m_pobRecordset->get_EditMode(penMode) );
}

BOOL CADORecordset::IsEditInProgress(BOOL* pbResult)
{
	EditModeEnum enMode;
	return GetEditMode(&enMode) && (enMode == adEditInProgress);
}

BOOL CADORecordset::IsEditAdd(BOOL* pbResult)
{
	EditModeEnum enMode;
	return GetEditMode(&enMode) && (enMode == adEditAdd);
}

BOOL CADORecordset::IsEditDelete(BOOL* pbResult)
{
	EditModeEnum enMode;
	return GetEditMode(&enMode) && (enMode == adEditDelete);
}

BOOL CADORecordset::IsEditNone(BOOL* pbResult)
{
	EditModeEnum enMode;
	return GetEditMode(&enMode) && (enMode == adEditNone);
}

BOOL CADORecordset::IsFieldExist(long lIndex)
{
	CComVariant varVal;
	if( GetFieldValue(lIndex, &varVal) )
		return TRUE;
	else
		return FALSE;
}

BOOL CADORecordset::IsFieldNULL(long lIndex)
{
	CComVariant varVal;
	if( GetFieldValue(lIndex, &varVal) && varVal.vt == VT_NULL )
		return TRUE;
	else
		return FALSE;
}

BOOL CADORecordset::IsFieldExist(LPCTSTR lpszFieldName)
{
	CComVariant varVal;
	if( GetFieldValue(lpszFieldName, &varVal) )
		return TRUE;
	else
		return FALSE;
}

BOOL CADORecordset::IsFieldNULL(LPCTSTR lpszFieldName)
{
	CComVariant varVal;
	if( GetFieldValue(lpszFieldName, &varVal) && varVal.vt == VT_NULL )
		return TRUE;
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldCount(long *plCount)
{
	CComPtr<Fields> pFields;
	HRESULT hr = m_pobRecordset->get_Fields(&pFields);
	if( FAILED(hr) )
		return FALSE;

	return SUCCEEDED( pFields->get_Count(plCount) );
}

BOOL CADORecordset::GetField(long lIndex, CADOField* pobField)
{
	CComPtr<Fields> pFields;
	HRESULT hr = m_pobRecordset->get_Fields(&pFields);
	if( FAILED(hr) )
		return FALSE;

	CComVariant varIndex;
	VariantInit(&varIndex);

	varIndex.vt = VT_I4;
	varIndex.lVal = lIndex;
	
	CComPtr<Field> pField;
	hr = pFields->get_Item(varIndex, &pField);
	if( FAILED(hr) )
		return FALSE;	
	
	pobField->m_pobField = pField;
	return TRUE;
}

BOOL CADORecordset::GetField(LPCTSTR lpszFieldName, CADOField* pobField)
{
	CComPtr<Fields> pFields;
	HRESULT hr = m_pobRecordset->get_Fields(&pFields);
	if( FAILED(hr) )
		return FALSE;

	CComVariant varIndex;
	VariantInit(&varIndex);

	varIndex.vt = VT_BSTR;
	varIndex.bstrVal = T2BSTR(lpszFieldName);

	CComPtr<Field> pField;
	hr = pFields->get_Item(varIndex, &pField);
	::SysFreeString(varIndex.bstrVal);
	if( FAILED(hr) )
		return FALSE;
	
	pobField->m_pobField = pField;
	return TRUE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, VARIANT* pvarValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pvarValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, long* plValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(plValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, short* pnValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pnValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, float* pfValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pfValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, double* pdblValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pdblValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, CString* pstrValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pstrValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, BOOL* pbValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pbValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, SYSTEMTIME* pstValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pstValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, CHAR* pcValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pcValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, CY* pcyValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pcyValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, DECIMAL* pdecValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pdecValue);
	else
		return FALSE;
}


BOOL CADORecordset::GetFieldValue(long lIndex, __int64* pwnValue)
{
	DECIMAL dec;
	if( GetFieldValue(lIndex, &dec) )
	{
		*pwnValue = static_cast<__int64>(dec.Lo64);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(long lIndex, BSTR* pbstrValue)
{
	CADOField obADOField;
	if( GetField(lIndex, &obADOField) )
		return obADOField.GetValue(pbstrValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, VARIANT* pvarValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pvarValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, long* plValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(plValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, short* pnValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pnValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, float* pfValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pfValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, double* pdblValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pdblValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, CString* pstrValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pstrValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, BOOL* pbValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pbValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, SYSTEMTIME* pstValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pstValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, CHAR* pcValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pcValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, CY* pcyValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pcyValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, DECIMAL* pdecValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pdecValue);
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, __int64* pwnValue)
{
	DECIMAL dec;
	if( GetFieldValue(lpszFieldName, &dec) )
	{
		*pwnValue = (static_cast<__int64>(dec.Lo64));
		if (dec.sign) *pwnValue = *pwnValue * (-1);			// 부호 버그 수정 2006.06.18 김동수
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpszFieldName, BSTR* pbstrValue)
{
	CADOField obADOField;
	if( GetField(lpszFieldName, &obADOField) )
		return obADOField.GetValue(pbstrValue);
	else
		return FALSE;
}

CString CADORecordset::GetFieldValueStr(LPCTSTR lpszFieldName)
{
	CString sValue;
	GetFieldValue(lpszFieldName, &sValue);
	return sValue;
}

CString CADORecordset::GetFieldValueStr(long lIndex)
{
	CString sValue;
	GetFieldValue(lIndex, &sValue);
	return sValue;
}

BOOL CADORecordset::GetBinaryFieldSize(long lIndex, long* plSize)
{
	CADOField obField;
	if( GetField(lIndex, &obField) )
		return obField.GetActualSize(plSize);
	else
		return FALSE;
}

BOOL CADORecordset::GetBinaryFieldSize(LPCTSTR lpszFieldName, long* plSize)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.GetActualSize(plSize);
	else
		return FALSE;
}

BOOL CADORecordset::GetBinaryFieldValue(long lIndex, BYTE* pbtValue, long lDataSize)
{
	CADOField obField;
	if( GetField(lIndex, &obField) )
	{
		CComVariant varChunk;
		if(obField.GetChunk(lDataSize, &varChunk))
		{
			memcpy(pbtValue, varChunk.parray[0].pvData, lDataSize);
			return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::GetBinaryFieldValue(LPCTSTR lpszFieldName, BYTE* pbtValue, long lDataSize)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
	{
		CComVariant varChunk;
		if(obField.GetChunk(lDataSize, &varChunk))
		{
			memcpy(pbtValue, varChunk.parray[0].pvData, lDataSize);
			return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::SetBinaryFieldValue(long lIndex, BYTE* pbtValue, long lSize)
{
	CADOField obField;
	if( GetField(lIndex, &obField) )
	{
		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = lSize;

		CComVariant varChunk;
		VariantInit(&varChunk);
		varChunk.vt = VT_ARRAY | VT_UI1;
		varChunk.parray = SafeArrayCreate(VT_UI1, 1 ,rgsabound);
		memcpy(varChunk.parray[0].pvData, pbtValue, lSize);
		obField.AppendChunk(varChunk);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::SetBinaryFieldValue(LPCTSTR lpszFieldName, BYTE* pbtValue, long lSize)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
	{
		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = lSize;

		CComVariant varChunk;
		VariantInit(&varChunk);
		varChunk.vt = VT_ARRAY | VT_UI1;
		varChunk.parray = SafeArrayCreate(VT_UI1, 1 ,rgsabound);
		memcpy(varChunk.parray[0].pvData, pbtValue, lSize);
		obField.AppendChunk(varChunk);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::GetBinaryFieldToFile(long lIndex, LPCTSTR lpszFileName)
{
	CADOField obField;
	if( !GetField(lIndex, &obField) )
		return FALSE;

	long lSize;
	if( !GetBinaryFieldSize(lIndex, &lSize) )
		return FALSE;

	HANDLE hFile = ::CreateFile(lpszFileName,
								GENERIC_WRITE,
								0,
								NULL,
								CREATE_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	BYTE* pBuff = new BYTE[lSize];
	if( !GetBinaryFieldValue(lIndex, pBuff, lSize) )
	{
		::CloseHandle(hFile);
		delete [] pBuff;
		return FALSE;
	}
	DWORD dwWritten;
	if( !::WriteFile(hFile, pBuff, lSize, &dwWritten, NULL) )
	{
		::CloseHandle(hFile);
		delete [] pBuff;
		return FALSE;
	}
	::CloseHandle(hFile);
	delete [] pBuff;
	return TRUE;
}

BOOL CADORecordset::SetBinaryFieldFromFile(long lIndex, LPCTSTR lpszFileName)
{
	CADOField obField;
	if( !GetField(lIndex, &obField) )
		return FALSE;

	HANDLE hFile = ::CreateFile(lpszFileName,
								GENERIC_READ,
								0,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD dwHi;
	DWORD dwLo = ::GetFileSize(hFile, &dwHi);
	BYTE* pBuff = new BYTE[dwLo];
	DWORD dwRead;
	if(!::ReadFile(hFile, pBuff, dwLo, &dwRead, NULL))
	{
		::CloseHandle(hFile);
		delete [] pBuff;
		return FALSE;
	}

	if(!SetBinaryFieldValue(lIndex, pBuff, dwLo))
	{
		::CloseHandle(hFile);
		delete [] pBuff;
		return FALSE;
	}

	::CloseHandle(hFile);
	delete [] pBuff;
	return TRUE;
}

BOOL CADORecordset::GetBinaryFieldToFile(LPCTSTR lpszFieldName, LPCTSTR lpszFileName)
{
	CADOField obField;
	if( !GetField(lpszFieldName, &obField) )
		return FALSE;

	long lSize;
	if( !GetBinaryFieldSize(lpszFieldName, &lSize) )
		return FALSE;

	HANDLE hFile = ::CreateFile(lpszFileName,
								GENERIC_WRITE,
								0,
								NULL,
								CREATE_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	BYTE* pBuff = new BYTE[lSize];
	if( !GetBinaryFieldValue(lpszFieldName, pBuff, lSize) )
	{
		::CloseHandle(hFile);
		delete [] pBuff;
		return FALSE;
	}
	DWORD dwWritten;
	if( !::WriteFile(hFile, pBuff, lSize, &dwWritten, NULL) )
	{
		::CloseHandle(hFile);
		delete [] pBuff;
		return FALSE;
	}
	::CloseHandle(hFile);
	delete [] pBuff;
	return TRUE;
}

BOOL CADORecordset::SetBinaryFieldFromFile(LPCTSTR lpszFieldName, LPCTSTR lpszFileName)
{
	CADOField obField;
	if( !GetField(lpszFieldName, &obField) )
		return FALSE;

	HANDLE hFile = ::CreateFile(lpszFileName,
								GENERIC_READ,
								0,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD dwHi;
	DWORD dwLo = ::GetFileSize(hFile, &dwHi);
	BYTE* pBuff = new BYTE[dwLo];
	DWORD dwRead;
	if(!::ReadFile(hFile, pBuff, dwLo, &dwRead, NULL))
	{
		::CloseHandle(hFile);
		delete [] pBuff;
		return FALSE;
	}

	if(!SetBinaryFieldValue(lpszFieldName, pBuff, dwLo))
	{
		::CloseHandle(hFile);
		delete [] pBuff;
		return FALSE;
	}

	::CloseHandle(hFile);
	delete [] pBuff;
	return TRUE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, VARIANT varValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue(varValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, long lValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue((long)lValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, short nValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue((short)nValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, float fValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue((float)fValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, double dblValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue((double)dblValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, CString strValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue(strValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, BOOL bValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue((BOOL)bValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, SYSTEMTIME stValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue((SYSTEMTIME)stValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, CHAR cValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue((CHAR)cValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, CY cyValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue((CY)cyValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, DECIMAL decValue)
{
	CADOField obField;
	if( GetField((long)lIndex, &obField) )
		return obField.SetValue((DECIMAL)decValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(long lIndex, __int64 wnValue)
{
	DECIMAL dec;
	dec.Lo64 = wnValue;
	return SetFieldValue((long)lIndex, dec);
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, VARIANT varValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue(varValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, long lValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue((long)lValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, short nValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue((short)nValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, float fValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue((float)fValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, double dblValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue((double)dblValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, CString strValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue(strValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, BOOL bValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue((BOOL)bValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, SYSTEMTIME stValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue((SYSTEMTIME)stValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, CHAR cValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue((CHAR)cValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, CY cyValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue((CY)cyValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, DECIMAL decValue)
{
	CADOField obField;
	if( GetField(lpszFieldName, &obField) )
		return obField.SetValue((DECIMAL)decValue);
	else
		return FALSE;
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpszFieldName, __int64 wnValue)
{
	DECIMAL dec;
	dec.Lo64 = wnValue;
	return SetFieldValue(lpszFieldName, dec);
}

BOOL CADORecordset::SetFieldValueNull(long lIndex)
{
	CComVariant v;
	v.vt = VT_NULL;
	return SetFieldValue(lIndex, v);
}

BOOL CADORecordset::SetFieldValueNull(LPCTSTR lpszFieldName)
{
	CComVariant v;
	v.vt = VT_NULL;
	return SetFieldValue(lpszFieldName, v);
}

BOOL CADORecordset::GetFilter(VARIANT* pvarFilter)
{
	/*
		Filter 값에는 다음의 세 값중 하나가 올 수 있다. (MDSN 참조)

		Criteria string - a string made up of one or more individual clauses concatenated with AND or OR operators. 
		Array of bookmarks - an array of unique bookmark values that point to records in the Recordset object. 
		A FilterGroupEnum value. 
	*/
	return SUCCEEDED( m_pobRecordset->get_Filter(pvarFilter) );
}

BOOL CADORecordset::SetFilter(VARIANT varFilter)
{
	return SUCCEEDED( m_pobRecordset->put_Filter(varFilter) );
}

BOOL CADORecordset::GetIndex(CString* pstrIndex)
{
	CComBSTR bstrIndex;
	HRESULT hr = m_pobRecordset->get_Index(&bstrIndex);
	if( FAILED(hr) )
		return FALSE;

	USES_CONVERSION;
	*pstrIndex = OLE2CT(bstrIndex);
	return TRUE;
}

BOOL CADORecordset::SetIndex(CString strIndex)
{
	return SUCCEEDED(m_pobRecordset->put_Index(CComBSTR(strIndex)));
}

BOOL CADORecordset::GetLockType(LockTypeEnum *penLockType)
{
	return SUCCEEDED( m_pobRecordset->get_LockType(penLockType) );
}

BOOL CADORecordset::SetLockType(LockTypeEnum enLockType)
{
	return SUCCEEDED( m_pobRecordset->put_LockType(enLockType) );
}

BOOL CADORecordset::GetMarshalOptions(MarshalOptionsEnum* penMarshalOptions)
{
	return SUCCEEDED( m_pobRecordset->get_MarshalOptions(penMarshalOptions) );
}

BOOL CADORecordset::SetMarshalOptions(MarshalOptionsEnum enMarshalOptions)
{
	return SUCCEEDED( m_pobRecordset->put_MarshalOptions(enMarshalOptions) );
}

BOOL CADORecordset::GetMaxRecords(long *plCount)
{
	return SUCCEEDED( m_pobRecordset->get_MaxRecords(plCount) );
}

BOOL CADORecordset::SetMaxRecords(long lCount)
{
	return SUCCEEDED( m_pobRecordset->put_MaxRecords(lCount) );
}

BOOL CADORecordset::GetPageCount(long *plCount)
{
	return SUCCEEDED( m_pobRecordset->get_PageCount(plCount) );
}

BOOL CADORecordset::GetPageSize(long *plSize)
{
	return SUCCEEDED( m_pobRecordset->get_PageSize(plSize) );
}

BOOL CADORecordset::SetPageSize(long lSize)
{
	return SUCCEEDED( m_pobRecordset->put_PageSize(lSize) );
}

BOOL CADORecordset::GetPropertyCount(long* plCount)
{
	CComPtr<Properties> pProperties;
	HRESULT hr = m_pobRecordset->get_Properties(&pProperties);
	if( FAILED(hr) )
		return FALSE;

	return SUCCEEDED( pProperties->get_Count(plCount) );
}

BOOL CADORecordset::GetProperty(long lIndex, CADOProperty* pobProperty)
{
	CComPtr<Properties> pProperties;
	HRESULT hr = m_pobRecordset->get_Properties(&pProperties);
	if( FAILED(hr) )
		return FALSE;

	CComVariant varIndex;
	VariantInit(&varIndex);
	varIndex.vt = VT_I4;
	varIndex.lVal = lIndex;
	return SUCCEEDED( pProperties->get_Item(varIndex, &(pobProperty->m_pobProperty)) );
}

BOOL CADORecordset::GetRecordCount(long *plCount)
{
	return SUCCEEDED( m_pobRecordset->get_RecordCount(plCount) );
}

BOOL CADORecordset::GetSort(CString* pstrCriteria)
{
	CComBSTR bstrCriteria;
	HRESULT hr = m_pobRecordset->get_Sort(&bstrCriteria);
	if( FAILED(hr) )
		return FALSE;

	USES_CONVERSION;
	*pstrCriteria = OLE2CT(bstrCriteria);
	return TRUE;
}

BOOL CADORecordset::SetSort(CString strCriteria)
{
	return SUCCEEDED(m_pobRecordset->put_Sort(CComBSTR(strCriteria)));
}

BOOL CADORecordset::GetSource(CString *pstrSource)
{
	CComVariant varSource;
	VariantInit(&varSource);
	HRESULT hr = m_pobRecordset->get_Source(&varSource);
	if( FAILED(hr) )
		return FALSE;

	if( varSource.vt != VT_BSTR )
		return FALSE;

	USES_CONVERSION;
	*pstrSource = OLE2CT(varSource.bstrVal);
	return TRUE;
}

BOOL CADORecordset::SetSource(CString strSource)
{
	return SUCCEEDED(m_pobRecordset->put_Source(CComBSTR(strSource)));
}

BOOL CADORecordset::GetState(ObjectStateEnum *penState)
{
	long lState;
	HRESULT hr = m_pobRecordset->get_State(&lState);
	if( SUCCEEDED(hr) )
	{
		*penState = static_cast<ObjectStateEnum>( lState );
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::IsOpen(BOOL* pbOpen)
{
	ObjectStateEnum enState;
	if( GetState(&enState) )
	{
		*pbOpen = enState & adStateOpen;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::GetStatus(long *plStatus)
{
	return SUCCEEDED( m_pobRecordset->get_Status(plStatus) );
}

BOOL CADORecordset::GetStayInSync(BOOL *pbStay)
{
	VARIANT_BOOL vbVal;
	HRESULT hr = m_pobRecordset->get_StayInSync(&vbVal);
	if( FAILED(hr) )
		return FALSE;

	*pbStay = (vbVal == VARIANT_TRUE);
	return TRUE;
}

BOOL CADORecordset::SetStayInSync(BOOL bStay)
{
	return SUCCEEDED( m_pobRecordset->put_StayInSync(static_cast<VARIANT_BOOL>(bStay)) );
}

BOOL CADORecordset::AddNew(VARIANT FieldList, VARIANT Values)
{
	return SUCCEEDED( m_pobRecordset->AddNew(FieldList, Values) );
}

BOOL CADORecordset::Cancel()
{
	return SUCCEEDED( m_pobRecordset->Cancel() );
}

BOOL CADORecordset::CancelBatch(AffectEnum enAffectRecords)
{
	return SUCCEEDED( m_pobRecordset->CancelBatch(enAffectRecords) );
}

BOOL CADORecordset::CancelUpdate()
{
	return SUCCEEDED( m_pobRecordset->CancelUpdate() );
}

BOOL CADORecordset::Clone(LockTypeEnum enLockType, CADORecordset *pobRecordset)
{
	if(pobRecordset->m_pobRecordset)
		pobRecordset->m_pobRecordset.Release();
	return SUCCEEDED( m_pobRecordset->Clone(enLockType, &(pobRecordset->m_pobRecordset)) );
}

BOOL CADORecordset::Close()
{
	return SUCCEEDED( m_pobRecordset->Close() );
}

BOOL CADORecordset::CompareBookmarks(VARIANT varBookmark1, VARIANT varBookmark2, CompareEnum* penCompare)
{
	return SUCCEEDED( m_pobRecordset->CompareBookmarks(varBookmark1, varBookmark2, penCompare) );
}

BOOL CADORecordset::Delete(AffectEnum enAffectRecords)
{
	return SUCCEEDED( m_pobRecordset->Delete(enAffectRecords) );
}

BOOL CADORecordset::Find(CString strCriteria, long lSkipRecords, SearchDirectionEnum enSearchDirection, VARIANT varStart )
{
	return SUCCEEDED(m_pobRecordset->Find(CComBSTR(strCriteria), lSkipRecords, enSearchDirection, varStart));
}

BOOL CADORecordset::GetRows(long lRows, VARIANT varStart, VARIANT varFields, VARIANT *pvarArray)
{
	return SUCCEEDED( m_pobRecordset->GetRows(lRows, varStart, varFields, pvarArray) );
}

BOOL CADORecordset::GetString(StringFormatEnum enStringFormat, long lNumRows, CString strColumnDelimeter, CString strRowDelimeter, CString strNullExpr, CString* pstrRetString)
{
	CComBSTR bstrRetString;

	if( SUCCEEDED(m_pobRecordset->GetString(enStringFormat, lNumRows, CComBSTR(strColumnDelimeter), CComBSTR(strRowDelimeter), CComBSTR(strNullExpr), &bstrRetString)) )
	{
		USES_CONVERSION;
		*pstrRetString = OLE2CT(bstrRetString);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::Move(long lNumRecords, VARIANT varStart)
{
	return SUCCEEDED( m_pobRecordset->Move(lNumRecords, varStart) );
}

BOOL CADORecordset::MoveFirst()
{
	return SUCCEEDED( m_pobRecordset->MoveFirst() );
}

BOOL CADORecordset::MoveLast()
{
	return SUCCEEDED( m_pobRecordset->MoveLast() );
}

BOOL CADORecordset::MoveNext()
{
	return SUCCEEDED( m_pobRecordset->MoveNext() );
}

BOOL CADORecordset::MovePrevious()
{
	return SUCCEEDED( m_pobRecordset->MovePrevious() );
	CComPtr<_Recordset> p;		
}

BOOL CADORecordset::NextRecordset(long *plRecordsAffected, CADORecordset* pobRecordset)
{
	if(pobRecordset->m_pobRecordset)
		pobRecordset->m_pobRecordset.Release();

	CComVariant varRecordsAffected;
	VariantInit(&varRecordsAffected);
	HRESULT hr = m_pobRecordset->NextRecordset(&varRecordsAffected, &(pobRecordset->m_pobRecordset));
	if( FAILED(hr) )
		return FALSE;

	if( varRecordsAffected.vt != VT_I4 )
		return FALSE;

	if(pobRecordset->m_pobRecordset == NULL)
		return FALSE;

	*plRecordsAffected = varRecordsAffected.lVal;
	return TRUE;
}

BOOL CADORecordset::Reconnect()
{
	// Reconnect
	CADOConnection oConn;
	if(GetActiveConnection(&oConn))
		return oConn.Reconnect();
	else
		return FALSE;
}

BOOL CADORecordset::Open(VARIANT varSource, VARIANT varActiveConnection, CursorTypeEnum enCursorType, LockTypeEnum enLockType, long lOptions)
{
	/**********************************************************************************************
	if(IsOpen())
		Close();

	return SUCCEEDED( m_pobRecordset->Open(varSource, varActiveConnection, enCursorType, enLockType, lOptions) );
	**********************************************************************************************/

	m_pobRecordset->Close();

	HRESULT hr = m_pobRecordset->Open(varSource, varActiveConnection, enCursorType, enLockType, lOptions);
	if(hr == E_FAIL)
	{
		// Reconnect
		if(!Reconnect())
			return SUCCEEDED(hr);
		hr = m_pobRecordset->Open(varSource, varActiveConnection, enCursorType, enLockType, lOptions);
	}

	return SUCCEEDED(hr);
}

BOOL CADORecordset::Open(CString strSource, CADOConnection* pobConnection, CursorTypeEnum enCursorType, LockTypeEnum enLockType, long lOptions)
{
	CComVariant varSource;
	VariantInit(&varSource);
	varSource.vt = VT_BSTR;
	varSource.bstrVal = strSource.AllocSysString();

	CComVariant varActiveConnection;
	VariantInit(&varActiveConnection);
	varActiveConnection.vt = VT_UNKNOWN;
	HRESULT hr = pobConnection->m_pobConnection->QueryInterface(&varActiveConnection.punkVal);
	if( FAILED(hr) )
		return FALSE;
	else
		return Open(varSource, varActiveConnection, enCursorType, enLockType, lOptions);
}

BOOL CADORecordset::Open(CString strSource, CString strConnectionStr, CursorTypeEnum enCursorType, LockTypeEnum enLockType, long lOptions)
{
	CComVariant varSource;
	VariantInit(&varSource);
	varSource.vt = VT_BSTR;
	varSource.bstrVal = strSource.AllocSysString();

	CComVariant varActiveConnection;
	VariantInit(&varActiveConnection);
	varActiveConnection.vt = VT_BSTR;
	varActiveConnection.bstrVal = strConnectionStr.AllocSysString();

	return Open(varSource, varActiveConnection, enCursorType, enLockType, lOptions);
}

BOOL CADORecordset::Open(CADOCommand *pobCommand, CADOConnection *pobConnection, CursorTypeEnum enCursorType, LockTypeEnum enLockType, long lOptions)
{
	CComVariant varSource;
	VariantInit(&varSource);
	varSource.vt = VT_UNKNOWN;
	HRESULT hr = pobCommand->m_pobCommand->QueryInterface( &varSource.punkVal );
	if( FAILED(hr) )
		return FALSE;

	CComVariant varActiveConnection;
	VariantInit(&varActiveConnection);
	varActiveConnection.vt = VT_UNKNOWN;
	hr = pobConnection->m_pobConnection->QueryInterface(&varActiveConnection.punkVal);
	if( FAILED(hr) )
		return FALSE;
	else
		return Open(varSource, varActiveConnection, enCursorType, enLockType, lOptions);
}

BOOL CADORecordset::Open(CADOCommand *pobCommand, CString strConnectionStr, CursorTypeEnum enCursorType, LockTypeEnum enLockType, long lOptions)
{
	CComVariant varSource;
	VariantInit(&varSource);
	varSource.vt = VT_UNKNOWN;
	HRESULT hr = pobCommand->m_pobCommand->QueryInterface( &varSource.punkVal );
	if( FAILED(hr) )
		return FALSE;

	CComVariant varActiveConnection;
	VariantInit(&varActiveConnection);
	varActiveConnection.vt = VT_BSTR;
	varActiveConnection.bstrVal = strConnectionStr.AllocSysString();

	return Open(varSource, varActiveConnection, enCursorType, enLockType, lOptions);
}

BOOL CADORecordset::Requery(long lOptions)
{	
	return SUCCEEDED( m_pobRecordset->Requery(lOptions) );
}

BOOL CADORecordset::Resync(AffectEnum enAffectRecords, ResyncEnum enResyncValues)
{
	return SUCCEEDED( m_pobRecordset->Resync(enAffectRecords, enResyncValues) );
}

BOOL CADORecordset::Save(VARIANT varDestination, PersistFormatEnum enPersistFormat)
{
	return SUCCEEDED( m_pobRecordset->Save(varDestination, enPersistFormat) );
}

BOOL CADORecordset::Save(CString strDestination, PersistFormatEnum enPersistFormat)
{
	CComVariant varDestination;
	VariantInit(&varDestination);
	varDestination.vt = VT_BSTR;
	varDestination.bstrVal = strDestination.AllocSysString();
	return Save(varDestination, enPersistFormat);
}

BOOL CADORecordset::Save(IUnknown* pUnkn, PersistFormatEnum enPersistFormat)
{
	// 첫번째 파라미터는 Stream 객체의 IUnkown이어야 함
	CComVariant varDestination;
	VariantInit(&varDestination);
	varDestination.vt = VT_UNKNOWN;
	varDestination.punkVal = pUnkn;
	return Save(varDestination, enPersistFormat);
}

BOOL CADORecordset::Seek(VARIANT varKeyValues, SeekEnum enSeekOption)
{	
	return SUCCEEDED( m_pobRecordset->Seek(varKeyValues, enSeekOption) );
}

BOOL CADORecordset::Supports(CursorOptionEnum enCursorOptions, BOOL* pbSupport)
{
	VARIANT_BOOL vbSupport;
	if( SUCCEEDED(m_pobRecordset->Supports(enCursorOptions, &vbSupport)) )
	{
		 *pbSupport = (vbSupport == VARIANT_TRUE);
		 return TRUE;
	}
	else
		return FALSE;
}

BOOL CADORecordset::Update(VARIANT varFields, VARIANT varValues)
{	
	return SUCCEEDED( m_pobRecordset->Update(varFields, varValues) );
}

BOOL CADORecordset::UpdateBatch(AffectEnum enAffectRecords)
{
	return SUCCEEDED( m_pobRecordset->UpdateBatch(enAffectRecords) );
}



//////////////////////////////////////////////////////////////////////
// CADOParameter class
CADOParameter::CADOParameter()
{
}

CADOParameter::CADOParameter(_Parameter* pParam)
{
}

CADOParameter::~CADOParameter()
{
}

BOOL CADOParameter::GetAttributes(ParameterAttributesEnum* penAttributes)
{
	return SUCCEEDED( m_pobParameter->get_Attributes(reinterpret_cast<long*>(penAttributes)) );
}

BOOL CADOParameter::SetAttributes(ParameterAttributesEnum enAttributes)
{
	return SUCCEEDED( m_pobParameter->put_Attributes(static_cast<long>(enAttributes)) );
}

BOOL CADOParameter::GetDirection(ParameterDirectionEnum* penDirection)
{
	return SUCCEEDED(m_pobParameter->get_Direction(penDirection));
}

BOOL CADOParameter::SetDirection(ParameterDirectionEnum enDirection)
{
	return SUCCEEDED(m_pobParameter->put_Direction(enDirection));
}

BOOL CADOParameter::GetName(CString* pstrName)
{
	CComBSTR bstrName;
	if( SUCCEEDED(m_pobParameter->get_Name(&bstrName)) )
	{
		USES_CONVERSION;
		*pstrName = OLE2CT(bstrName);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOParameter::SetName(CString strName)
{
	return SUCCEEDED(m_pobParameter->put_Name(CComBSTR(strName)));
}

BOOL CADOParameter::GetNumericScale(BYTE* pbtNumericScale)
{
	return SUCCEEDED(m_pobParameter->get_NumericScale(pbtNumericScale));
}

BOOL CADOParameter::SetNumericScale(BYTE btNumericScale)
{
	return SUCCEEDED(m_pobParameter->put_NumericScale(btNumericScale));
}



//////////////////////////////////////////////////////////////////////
// CADOConnection class
inline void TESTHR(HRESULT x) {if FAILED(x) _com_issue_error(x);}

CADOConnection::CADOConnection()
{
	HRESULT hr = m_pobConnection.CoCreateInstance( __uuidof(Connection) );
	if( FAILED(hr) )
		SHOW_ADO_INSTALLATION_ERROR_MESSAGE;
}

CADOConnection::CADOConnection(IUnknown* pUnkn)
{
	CComPtr<IUnknown> p = pUnkn;
	p->QueryInterface(&m_pobConnection);
}

CADOConnection::CADOConnection(_Connection* pConn)
{
	m_pobConnection = pConn;
}

CADOConnection::~CADOConnection()
{
	if(m_pobConnection)
		m_pobConnection.Release();
}

IUnknown* CADOConnection::GetUnknown()
{
	IUnknown* pUnkn = NULL;
	HRESULT hr = m_pobConnection->QueryInterface(__uuidof(IUnknown), reinterpret_cast<void**>(&pUnkn));
	return pUnkn;
}

void CADOConnection::ShowErrorMessage(HWND hWndParent)
{
	ATLASSERT(m_pobConnection != NULL);

	long lErrCnt;
	if( !GetErrorCount(&lErrCnt) )
	{
		::MessageBox(hWndParent, _T("데이터베이스 작업 도중 알 수 없는 오류가 발생되었습니다.\n오류 지점은 다음과 같습니다.\n\nGetErrorCount 실패"), _T("오류"), MB_ICONSTOP);
		return;
	}

	for(long l=0; l<lErrCnt; ++l)
	{
		CADOError obError;
		if( !GetError(l, &obError) )
		{
			::MessageBox(hWndParent, _T("데이터베이스 작업 도중 알 수 없는 오류가 발생되었습니다.\n오류 지점은 다음과 같습니다.\n\nGetError 실패"), _T("오류"), MB_ICONSTOP);
			return;
		}
		else
		{
			CString strDescription;			
			if( !obError.GetDescription(&strDescription) )
			{
				::MessageBox(hWndParent, _T("데이터베이스 작업 도중 알 수 없는 오류가 발생되었습니다.\n오류 지점은 다음과 같습니다.\n\nGetError 실패"), _T("오류"), MB_ICONSTOP);
				return;
			}

			CString strMessage;
			strMessage.Format( _T("데이터베이스 작업 도중 다음과 같은 문제가 발생하였습니다.\n\n%s"), strDescription );
			::MessageBox(hWndParent, strMessage, _T("오류"), MB_ICONSTOP);
		}
	}
}

CString CADOConnection::GetErrorMessage()
{
	ATLASSERT(m_pobConnection != NULL);

	CString strMessage;

	long lErrCnt;
	if( !GetErrorCount(&lErrCnt) )
	{
		strMessage = "데이터베이스 작업 도중 알 수 없는 오류가 발생되었습니다. 오류 지점은 다음과 같습니다. GetErrorCount 실패";
	}
	else
	{
		for(long l=0; l<lErrCnt; ++l)
		{
			CADOError obError;
			if( !GetError(l, &obError) )
			{
				strMessage = "데이터베이스 작업 도중 알 수 없는 오류가 발생되었습니다. 오류 지점은 다음과 같습니다. GetError 실패";
			}
			else
			{
				CString strDescription;			
				if( !obError.GetDescription(&strDescription) )
				{
					strMessage = "데이터베이스 작업 도중 알 수 없는 오류가 발생되었습니다. 오류 지점은 다음과 같습니다. GetError 실패";
				}
				else
				{
					CString strTemp;
					strTemp.Format( _T("데이터베이스 작업 도중 다음과 같은 문제가 발생하였습니다. %s"), strDescription );
					strMessage += strTemp;
				}
			}
		}
	}

	return strMessage;
}

BOOL CADOConnection::Open(LPCTSTR lpszConnectionStr, LPCTSTR lpszUserID, LPCTSTR lpszPassword, ConnectOptionEnum enOption)
{
	return SUCCEEDED(m_pobConnection->Open(CComBSTR(lpszConnectionStr), CComBSTR(lpszUserID), CComBSTR(lpszPassword), enOption));
}

BOOL CADOConnection::Close()
{
	return SUCCEEDED( m_pobConnection->Close() );
}

BOOL CADOConnection::GetAttributes(long* plAttributes)
{
	return SUCCEEDED( m_pobConnection->get_Attributes(plAttributes) );
}

BOOL CADOConnection::SetAttributes(long lAttributes)
{
	return SUCCEEDED( m_pobConnection->put_Attributes(lAttributes) );
}

BOOL CADOConnection::GetCommandTimeout(long* plSeconds)
{
	return SUCCEEDED( m_pobConnection->get_CommandTimeout(plSeconds) );
}

BOOL CADOConnection::SetCommandTimeout(long lSeconds)
{
	return SUCCEEDED( m_pobConnection->put_CommandTimeout(lSeconds) );
}

BOOL CADOConnection::GetConnectionString(CString* pstrConnectionStr)
{
	CComBSTR bstrConnectionString;
	HRESULT hr = m_pobConnection->get_ConnectionString(&bstrConnectionString);
	if( SUCCEEDED(hr) )
	{
		USES_CONVERSION;
		*pstrConnectionStr = OLE2CT(bstrConnectionString);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOConnection::SetConnectionString(CString strConnectionStr)
{
	return SUCCEEDED(m_pobConnection->put_ConnectionString(CComBSTR(strConnectionStr)));
}

BOOL CADOConnection::GetConnectionTimeout(long* plSeconds)
{
	return SUCCEEDED( m_pobConnection->get_ConnectionTimeout(plSeconds) );
}

BOOL CADOConnection::SetConnectionTimeout(long lSeconds)
{
	return SUCCEEDED( m_pobConnection->put_ConnectionTimeout(lSeconds) );
}

BOOL CADOConnection::GetCursorLocation(CursorLocationEnum* penCurLoc)
{
	return SUCCEEDED( m_pobConnection->get_CursorLocation(penCurLoc) );
}

BOOL CADOConnection::SetCursorLocation(CursorLocationEnum enCurLoc)
{
	return SUCCEEDED( m_pobConnection->put_CursorLocation(enCurLoc) );
}

BOOL CADOConnection::GetDefaultDatabase(CString* pstrDatabase)
{
	CComBSTR bstrDatabase;
	HRESULT hr = m_pobConnection->get_DefaultDatabase(&bstrDatabase);
	if( SUCCEEDED(hr) )
	{
		USES_CONVERSION;
		*pstrDatabase = OLE2CT(bstrDatabase);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOConnection::SetDefaultDatabase(CString strDatabase)
{
	return SUCCEEDED(m_pobConnection->put_DefaultDatabase(CComBSTR(strDatabase)));
}

BOOL CADOConnection::GetIsolationLevel(IsolationLevelEnum* penLevel)
{
	return SUCCEEDED( m_pobConnection->get_IsolationLevel(penLevel) );
}

BOOL CADOConnection::SetIsolationLevel(IsolationLevelEnum enLevel)
{
	return SUCCEEDED( m_pobConnection->put_IsolationLevel(enLevel) );
}

BOOL CADOConnection::GetMode(ConnectModeEnum* penConnectMode)
{
	return SUCCEEDED( m_pobConnection->get_Mode(penConnectMode) );
}

BOOL CADOConnection::SetMode(ConnectModeEnum enConnectMode)
{
	return SUCCEEDED( m_pobConnection->put_Mode(enConnectMode) );
}

BOOL CADOConnection::GetProvider(CString* pstrProvider)
{
	CComBSTR bstrProvider;
	HRESULT hr = m_pobConnection->get_Provider(&bstrProvider);
	if( SUCCEEDED(hr) )
	{
		USES_CONVERSION;
		*pstrProvider = OLE2CT(bstrProvider);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOConnection::SetProvider(CString strProvider)
{
	return SUCCEEDED(m_pobConnection->put_Provider(CComBSTR(strProvider)));
}

BOOL CADOConnection::GetState(ObjectStateEnum *penState)
{
	long lState;
	HRESULT hr = m_pobConnection->get_State(&lState);
	if( SUCCEEDED(hr) )
	{
		*penState = static_cast<ObjectStateEnum>( lState );
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOConnection::GetErrorCount(long *plCount)
{
	CComPtr<Errors> pobErrors;
	HRESULT hr = m_pobConnection->get_Errors(&pobErrors);
	if( SUCCEEDED(hr) )
		return SUCCEEDED( pobErrors->get_Count(plCount) );
	else
		return FALSE;
}

BOOL CADOConnection::GetError(long lIndex, CADOError *pobError)
{
	CComPtr<Errors> pobErrors;
	HRESULT hr = m_pobConnection->get_Errors(&pobErrors);
	if( SUCCEEDED(hr) )
	{
		CComVariant varIndex;
		VariantInit(&varIndex);
		varIndex.vt = VT_I4;
		varIndex.lVal = lIndex;
		hr = pobErrors->get_Item(varIndex, &(pobError->m_pobError));
		return SUCCEEDED(hr);
	}
	else
		return FALSE;
}

BOOL CADOConnection::GetPropertyCount(long* plCount)
{
	CComPtr<Properties> pobProperties;
	HRESULT hr = m_pobConnection->get_Properties(&pobProperties);
	if( SUCCEEDED(hr) )
		return SUCCEEDED( pobProperties->get_Count(plCount) );
	else
		return FALSE;
}

BOOL CADOConnection::GetProperty(long lIndex, CADOProperty *pobProperty)
{
	CComPtr<Properties> pobProperties;
	HRESULT hr = m_pobConnection->get_Properties(&pobProperties);
	if( SUCCEEDED(hr) )
	{
		CComVariant varIndex;
		VariantInit(&varIndex);
		varIndex.vt = VT_I4;
		varIndex.lVal = lIndex;
		hr = pobProperties->get_Item(varIndex, &(pobProperty->m_pobProperty));
		return SUCCEEDED(hr);
	}
	else
		return FALSE;
}

BOOL CADOConnection::BeginTrans(long* plTransactionLevel)
{
	return SUCCEEDED( m_pobConnection->BeginTrans(plTransactionLevel) );
}

BOOL CADOConnection::RollbackTrans()
{
	return SUCCEEDED( m_pobConnection->RollbackTrans() );
}

BOOL CADOConnection::CommitTrans()
{
	return SUCCEEDED( m_pobConnection->CommitTrans() );
}

BOOL CADOConnection::Cancel()
{
	return SUCCEEDED( m_pobConnection->Cancel() );
}

BOOL CADOConnection::Execute(CString strCommandText, CADORecordset *pRs, long* plRecordsAffected, long lOptions)
{
	/**********************************************************************************************
	CComBSTR bstrCommandText = strCommandText;

	CComVariant varRecordsAffected;
	VariantInit(&varRecordsAffected);

	if(pRs && pRs->m_pobRecordset)
		pRs->m_pobRecordset.Release();

	HRESULT hr;
	if(pRs)
		hr = m_pobConnection->Execute(bstrCommandText, &varRecordsAffected, lOptions, &(pRs->m_pobRecordset));
	else
		hr = m_pobConnection->Execute(bstrCommandText, &varRecordsAffected, lOptions, NULL);

	if(varRecordsAffected.vt == VT_I4 && plRecordsAffected != NULL)
		*plRecordsAffected = varRecordsAffected.lVal;

	return SUCCEEDED(hr);
	**********************************************************************************************/

	if(pRs && pRs->m_pobRecordset)
	{
		pRs->Close();
		pRs->m_pobRecordset.Release();
	}

	CComVariant varRecordsAffected;
	HRESULT hr = m_pobConnection->Execute(CComBSTR(strCommandText), &varRecordsAffected, lOptions, pRs == NULL ? NULL : &(pRs->m_pobRecordset));
	if(hr == E_FAIL)
	{
		if(!Reconnect())
			return SUCCEEDED(hr);

#ifdef _DEBUG
		::OutputDebugString(strCommandText);
#endif 
		hr = m_pobConnection->Execute(CComBSTR(strCommandText), &varRecordsAffected, lOptions, pRs == NULL ? NULL : &(pRs->m_pobRecordset));		
		if(FAILED(hr))
			return SUCCEEDED(hr);
	}

	if(varRecordsAffected.vt == VT_I4 && plRecordsAffected != NULL)
		*plRecordsAffected = varRecordsAffected.lVal;

	return SUCCEEDED(hr);
}

BOOL CADOConnection::OpenSchema(SchemaEnum enSchema, VARIANT varRestrictions, VARIANT varSchemaID, CADORecordset *pRs)
{
	return SUCCEEDED( m_pobConnection->OpenSchema(enSchema, varRestrictions, varSchemaID, &(pRs->m_pobRecordset)) );
}

BOOL CADOConnection::Advise(ConnectionEventsVt *pobConnectionEventsVt)
{
	BOOL bRet = FALSE;


	IConnectionPointContainer* pCPC = NULL;
	if( SUCCEEDED(m_pobConnection->QueryInterface(__uuidof(IConnectionPointContainer), (void **)&pCPC)) )
	{
		pCPC->AddRef();

		IConnectionPoint* pCP = NULL;
		if( SUCCEEDED(pCPC->FindConnectionPoint(__uuidof(ConnectionEvents), &pCP)) )
		{
			IUnknown* pUnk = NULL;
			if( SUCCEEDED(pobConnectionEventsVt->QueryInterface(__uuidof(IUnknown), (void **)&pUnk)) )
			{
				pUnk->AddRef();

				DWORD dwCookie;
				bRet = SUCCEEDED(pCP->Advise(pUnk, &dwCookie));

				m_obConnectionPointMap[pobConnectionEventsVt] = dwCookie;

				pUnk->Release();
			}

			pCP->Release();
		}

		pCPC->Release();
	}


	return bRet;
}

BOOL CADOConnection::Unadvise(ConnectionEventsVt *pobConnectionEventsVt)
{
	BOOL bRet = FALSE;


	IConnectionPointContainer* pCPC = NULL;
	if( SUCCEEDED(m_pobConnection->QueryInterface(__uuidof(IConnectionPointContainer), (void **)&pCPC)) )
	{
		pCPC->AddRef();

		IConnectionPoint* pCP = NULL;
		if( SUCCEEDED(pCPC->FindConnectionPoint(__uuidof(ConnectionEvents), &pCP)) )
		{
			IUnknown* pUnk = NULL;
			if( SUCCEEDED(pobConnectionEventsVt->QueryInterface(__uuidof(IUnknown), (void **)&pUnk)) )
			{
				pUnk->AddRef();

				std::map<ConnectionEventsVt*, DWORD>::iterator pos = m_obConnectionPointMap.find(pobConnectionEventsVt);
				if(pos != m_obConnectionPointMap.end())
				{
					DWORD dwCookie = pos->second;
					bRet = SUCCEEDED(pCP->Unadvise(dwCookie));
					m_obConnectionPointMap.erase(pos);
				}

				pUnk->Release();
			}

			pCP->Release();
		}

		pCPC->Release();
	}


	return bRet;
}

BOOL CADOConnection::Attach(_Connection* pConn)
{
	if(m_pobConnection)
		m_pobConnection.Release();

	m_pobConnection = pConn;
	return TRUE;
}

BOOL CADOConnection::Attach(IUnknown* pUnkn)
{
	if(m_pobConnection)
		m_pobConnection.Release();

	pUnkn->QueryInterface(&m_pobConnection);
	pUnkn->AddRef();
	return TRUE;
}

BOOL CADOConnection::Detach()
{
	if(m_pobConnection)
		m_pobConnection.Release();
	m_pobConnection = NULL;

	return TRUE;
}

void CADOConnection::operator=(CADOConnection& obDbConn)
{
	if(m_pobConnection)
		m_pobConnection.Release();
	
	HRESULT hr = obDbConn.m_pobConnection.CopyTo(&m_pobConnection);
	ATLASSERT( SUCCEEDED(hr) );
}

BOOL CADOConnection::IsOpen(BOOL* pbOpen)
{
	ObjectStateEnum enState;
	if( m_pobConnection && GetState(&enState) )
	{
		*pbOpen = enState & adStateOpen;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CADOConnection::IsOpen()
{
	BOOL bOpen;
	return IsOpen(&bOpen) && bOpen;
}

BOOL CADOConnection::IsClosed()
{
	ObjectStateEnum enState;
	return (GetState(&enState) && (enState == adStateClosed));
}

BOOL CADOConnection::IsConnecting()
{
	ObjectStateEnum enState;
	return (GetState(&enState) && (enState & adStateConnecting));
}

BOOL CADOConnection::IsExecuting()
{
	ObjectStateEnum enState;
	return (GetState(&enState) && (enState & adStateExecuting));
}

BOOL CADOConnection::IsFetching()
{
	ObjectStateEnum enState;
	return (GetState(&enState) && (enState & adStateFetching));
}

BOOL CADOConnection::ExecuteFile(LPCTSTR lpszFileName, BOOL bShowError)
{
	// Open File
	HANDLE hFile = ::CreateFile(lpszFileName,
								GENERIC_READ,                
								NULL,                 
								NULL,                         // no security 
								OPEN_EXISTING,               
								FILE_ATTRIBUTE_NORMAL,
								NULL);	
	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;


	// Get File Size
	DWORD dwHi;
	DWORD dwLo = ::GetFileSize(hFile, &dwHi);

	
	CString strText;
	LPTSTR pszBuffer = strText.GetBuffer(dwLo);


	DWORD dwRead;
	if(::ReadFile(hFile, pszBuffer, dwLo, &dwRead, NULL))
	{
		strText.ReleaseBuffer();
		strText.Replace(_T("#CONTINUE"), _T("GO"));
		strText.Replace(_T("#END"), _T("GO"));

		if(dwRead > 0)
		{
			CString strQuery;
			while(!strText.IsEmpty())
			{
				CString strTextUpper = strText;
				strTextUpper.MakeUpper();

				int nFind = strTextUpper.Find(_T("\nGO"));

				if(nFind != -1)
				{
					strQuery = strText.Left(nFind);
					strText = strText.Mid(nFind + 3);
				}
				else
				{
					strQuery = strText;
					strText.Empty();
				}

				strTextUpper = strText;

#ifdef _DEBUG
				OutputDebugString(CString(_T("▧[DB Log] ")) + strQuery + _T("\n"));
#endif //_DEBUG

				if(!Execute(strQuery) && bShowError)
					ShowErrorMessage();
			}
		}
	}
	else
		strText.ReleaseBuffer();


	::CloseHandle(hFile);
	return TRUE;
}

BOOL CADOConnection::Reconnect()
{
	CComPtr<Properties> pProperties;
	if( SUCCEEDED(m_pobConnection->get_Properties(&pProperties)) )
	{
		CComPtr<Property> pProperty;
		pProperties->get_Item(CComVariant("Current Catalog"), &pProperty);
			
		CComVariant vaDB;
		if(pProperty && SUCCEEDED(pProperty->get_Value(&vaDB)))
		{
			USES_CONVERSION;
			if (_tcsicmp(OLE2CT(vaDB.bstrVal), _T("H2")) == 0)
			{
				CRegKey reg;
				if (reg.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\OSSTEM\\hanaro\\Database")) == ERROR_SUCCESS)
				{
					TCHAR szConn[1024];

					DWORD dwCount = sizeof(szConn);

					if (reg.QueryStringValue(szConn, _T("ConnectionStatement"), &dwCount) == ERROR_SUCCESS)
					{
						BOOL bXact = SUCCEEDED(m_pobConnection->RollbackTrans());

						m_pobConnection->Close();
						HRESULT hr = m_pobConnection->Open(_bstr_t(szConn), _bstr_t(""), _bstr_t(""), adConnectUnspecified);
						if(SUCCEEDED(hr))
						{
							if(bXact)
							{
								long lLevel;
								m_pobConnection->BeginTrans(&lLevel);
							}

							CComVariant var;
							m_pobConnection->Execute(_bstr_t("select 1"), &var, adOptionUnspecified|adCmdUnspecified, NULL);
						}

						return SUCCEEDED(hr);
					}
				}
			}
			else if (_tcsicmp(OLE2CT(vaDB.bstrVal), _T("Hanaro")) == 0)
			{
				CRegKey reg;
				if(reg.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\OSSTEM\\hanarook\\Database")) == ERROR_SUCCESS)
				{
					TCHAR szConn[1024];

					DWORD dwCount = sizeof(szConn);
					if (reg.QueryStringValue(szConn, _T("ConnectionStatement"), &dwCount) == ERROR_SUCCESS)
					{
						BOOL bXact = SUCCEEDED(m_pobConnection->RollbackTrans());

						m_pobConnection->Close();
						HRESULT hr = m_pobConnection->Open(CComBSTR(szConn), CComBSTR("Hanaro3"), CComBSTR("osstem"), adConnectUnspecified);
						if(SUCCEEDED(hr))
						{
							if(bXact)
							{
								long lLevel;
								m_pobConnection->BeginTrans(&lLevel);
							}

							CComVariant var;
							m_pobConnection->Execute(_bstr_t("select 1"), &var, adOptionUnspecified|adCmdUnspecified, NULL);
						}

						return SUCCEEDED(hr);
					}
				}
			}
		}
	}

	return FALSE;
}



//////////////////////////////////////////////////////////////////////
// CADORecordsetEventsVt class
CADORecordsetEventsHandler::CADORecordsetEventsHandler()
{
	m_cRef = 0;
}

CADORecordsetEventsHandler::~CADORecordsetEventsHandler()
{
}

STDMETHODIMP CADORecordsetEventsHandler::WillChangeField(LONG cFields, VARIANT Fields, EventStatusEnum *adStatus, _Recordset *pRecordset) 
{ 
	*adStatus = adStatusUnwantedEvent;	
	return S_OK; 
}

STDMETHODIMP CADORecordsetEventsHandler::FieldChangeComplete(LONG cFields, VARIANT Fields, Error *pError, EventStatusEnum *adStatus, _Recordset *pRecordset)
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADORecordsetEventsHandler::WillChangeRecord(EventReasonEnum adReason, LONG cRecords, EventStatusEnum *adStatus, _Recordset *pRecordset) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADORecordsetEventsHandler::RecordChangeComplete(EventReasonEnum adReason, LONG cRecords, Error *pError, EventStatusEnum *adStatus, _Recordset *pRecordset) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADORecordsetEventsHandler::WillChangeRecordset(EventReasonEnum adReason, EventStatusEnum *adStatus, _Recordset *pRecordset) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADORecordsetEventsHandler::RecordsetChangeComplete(EventReasonEnum adReason, Error *pError, EventStatusEnum *adStatus, _Recordset *pRecordset) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADORecordsetEventsHandler::WillMove(EventReasonEnum adReason, EventStatusEnum *adStatus, _Recordset *pRecordset) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADORecordsetEventsHandler::MoveComplete(EventReasonEnum adReason, Error *pError, EventStatusEnum *adStatus, _Recordset *pRecordset) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADORecordsetEventsHandler::EndOfRecordset(VARIANT_BOOL *fMoreData, EventStatusEnum *adStatus, _Recordset *pRecordset) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADORecordsetEventsHandler::FetchProgress(long Progress, long MaxProgress, EventStatusEnum *adStatus, _Recordset *pRecordset) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADORecordsetEventsHandler::FetchComplete(Error *pError, EventStatusEnum *adStatus, _Recordset *pRecordset) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

ULONG STDMETHODCALLTYPE CADORecordsetEventsHandler::AddRef()
{
	return ++m_cRef;
}

ULONG STDMETHODCALLTYPE CADORecordsetEventsHandler::Release()
{
	if (0 != --m_cRef) 
		return m_cRef;
	
	delete this;
	return 0;
}

STDMETHODIMP CADORecordsetEventsHandler::QueryInterface(REFIID riid, void ** ppv) 
{
	*ppv = NULL;
	if(riid == __uuidof(IUnknown) || riid == __uuidof(ConnectionEventsVt)) 
		*ppv = this;
	
	if(*ppv == NULL)
		return ResultFromScode(E_NOINTERFACE);
	
	AddRef();
	return NOERROR;
}



//////////////////////////////////////////////////////////////////////
// CADOConnectionEventsVt class
CADOConnectionEventsHandler::CADOConnectionEventsHandler()
{
	m_cRef = 0;
}

CADOConnectionEventsHandler::~CADOConnectionEventsHandler()
{
}

STDMETHODIMP CADOConnectionEventsHandler::BeginTransComplete(LONG lTransactionLevel, Error *pError, EventStatusEnum *adStatus, _Connection *pConnection)
{
	CADOError obError(pError);
	CADOConnection obConnection(pConnection);
	return OnBeginTransComplete(lTransactionLevel, &obError, adStatus, &obConnection);
}

STDMETHODIMP CADOConnectionEventsHandler::CommitTransComplete(Error *pError, EventStatusEnum *adStatus, _Connection *pConnection)
{
	CADOError obError(pError);
	CADOConnection obConnection(pConnection);
	return OnCommitTransComplete(&obError, adStatus, &obConnection);
}

STDMETHODIMP CADOConnectionEventsHandler::RollbackTransComplete(Error *pError, EventStatusEnum *adStatus, _Connection *pConnection)
{
	CADOError obError(pError);
	CADOConnection obConnection(pConnection);
	return OnRollbackTransComplete(&obError, adStatus, &obConnection);
}

STDMETHODIMP CADOConnectionEventsHandler::ConnectComplete(Error *pError, EventStatusEnum *adStatus, _Connection *pConnection)
{
	CADOError obError(pError);
	CADOConnection obConnection(pConnection);
	return OnConnectComplete(&obError, adStatus, &obConnection);
}

STDMETHODIMP CADOConnectionEventsHandler::Disconnect(EventStatusEnum *adStatus, _Connection *pConnection)
{
	CADOConnection obConnection(pConnection);
	return OnDisconnect(adStatus, &obConnection);
}

STDMETHODIMP CADOConnectionEventsHandler::ExecuteComplete(LONG lRecordsAffected, Error *pError, EventStatusEnum *adStatus, _Command *pCommand, _Recordset *pRecordset, _Connection *pConnection)
{
	CADOError obError(pError);
	CADOCommand obCommand(pCommand);
	CADORecordset obRecordset(pRecordset);
	CADOConnection obConnection(pConnection);
	return OnExecuteComplete(lRecordsAffected, &obError, adStatus, &obCommand, &obRecordset, &obConnection);
}

STDMETHODIMP CADOConnectionEventsHandler::InfoMessage(Error *pError, EventStatusEnum *adStatus, _Connection *pConnection)
{
	CADOError obError(pError);
	CADOConnection obConnection(pConnection);
	return OnInfoMessage(&obError, adStatus, &obConnection);
}

STDMETHODIMP CADOConnectionEventsHandler::WillConnect(BSTR *ConnectionString, BSTR *UserID, BSTR *Password, LONG *plOptions, EventStatusEnum *adStatus, _Connection *pConnection)
{
	USES_CONVERSION;
	CString strConnStr = OLE2CT(*ConnectionString);
	CString strUserID = OLE2CT(*UserID);
	CString strPassword = OLE2CT(*Password);
	CADOConnection obConnection(pConnection);

	HRESULT hr = OnWillConnect(&strConnStr, &strUserID, &strPassword, plOptions, adStatus, &obConnection);
	
	*ConnectionString = T2BSTR(strConnStr);
	*UserID = T2BSTR(strUserID);
	*Password = T2BSTR(strPassword);
	return hr;
}

STDMETHODIMP CADOConnectionEventsHandler::WillExecute(BSTR *Source, CursorTypeEnum *CursorType, LockTypeEnum *LockType, LONG *plOptions, EventStatusEnum *adStatus, _Command *pCommand, _Recordset *pRecordset, _Connection *pConnection)
{
	*adStatus = adStatusUnwantedEvent; 	
/*	USES_CONVERSION;
	CString strSource = OLE2CT(*Source);
	CADOCommand obCommand(pCommand);
	CADORecordset obRecordset(pRecordset);
	CADOConnection obConnection(pConnection);

	HRESULT hr = OnWillExecute(&strSource, CursorType, LockType, plOptions, adStatus, &obCommand, &obRecordset, &obConnection);

	*Source = T2BSTR(strSource);
	return hr;
*/
	return S_OK;
}

STDMETHODIMP CADOConnectionEventsHandler::OnBeginTransComplete(LONG lTransactionLevel, CADOError *pError, EventStatusEnum *adStatus, CADOConnection *pConnection)
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADOConnectionEventsHandler::OnCommitTransComplete(CADOError *pError, EventStatusEnum *adStatus, CADOConnection *pConnection) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADOConnectionEventsHandler::OnRollbackTransComplete(CADOError *pError, EventStatusEnum *adStatus, CADOConnection *pConnection) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADOConnectionEventsHandler::OnConnectComplete(CADOError *pError, EventStatusEnum *adStatus, CADOConnection *pConnection) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADOConnectionEventsHandler::OnDisconnect(EventStatusEnum *adStatus, CADOConnection *pConnection) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADOConnectionEventsHandler::OnExecuteComplete(LONG lRecordsAffected, CADOError *pError, EventStatusEnum *adStatus, CADOCommand *pCommand, CADORecordset *pRecordset, CADOConnection *pConnection) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADOConnectionEventsHandler::OnInfoMessage(CADOError *pError, EventStatusEnum *adStatus, CADOConnection *pConnection) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADOConnectionEventsHandler::OnWillConnect(CString* pstrConnectionString, CString* pstrUserID, CString* pstrPassword, LONG *plOptions, EventStatusEnum *adStatus, CADOConnection *pConnection) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

STDMETHODIMP CADOConnectionEventsHandler::OnWillExecute(CString* pstrSource, CursorTypeEnum *CursorType, LockTypeEnum *LockType, LONG *plOptions, EventStatusEnum *adStatus, CADOCommand *pCommand, CADORecordset *pRecordset, CADOConnection *pConnection) 
{ 
	*adStatus = adStatusUnwantedEvent; 	
	return S_OK; 
}

ULONG STDMETHODCALLTYPE CADOConnectionEventsHandler::AddRef()
{
	return ++m_cRef;
}

ULONG STDMETHODCALLTYPE CADOConnectionEventsHandler::Release()
{
	if (0 != --m_cRef) 
		return m_cRef;
	
	delete this;
	return 0;
}

STDMETHODIMP CADOConnectionEventsHandler::QueryInterface(REFIID riid, void ** ppv) 
{
	*ppv = NULL;
	if(riid == __uuidof(IUnknown) || riid == __uuidof(ConnectionEventsVt)) 
		*ppv = this;
	
	if(*ppv == NULL)
		return ResultFromScode(E_NOINTERFACE);
	
	AddRef();
	return NOERROR;
}
