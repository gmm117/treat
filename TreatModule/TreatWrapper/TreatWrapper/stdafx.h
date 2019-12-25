// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED

#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

#include <atlwin.h>
#include <atlapp.h>
#include <atlmisc.h>

#include <msxml.h>
#include <msxml2.h>

#include <map>
#include <vector>

typedef struct _BASIC_CONTINFO
{
public:
	CRect rcRect;
	std::vector<CString> vecData;
	std::vector<CString> vecCode;
	int	  nCnt;
	CString strFormula;
	CString strStName;
	CString strHisCost;

// 持失切
	_BASIC_CONTINFO() : nCnt(0), strFormula(_T("")), strStName(_T("")), strHisCost(_T(""))
	{
		vecData.clear();
		vecCode.clear();
	}
} _S_BASIC_CONTINFO;


typedef struct _BASIC_SUGA
{
public:
	CString strCode;
	CString strName;
	CString strCost;

	// 持失切
	_BASIC_SUGA() : strCode(_T("")), strName(_T("")), strCost(_T("")) {}
} _S_BASIC_SUGA;
