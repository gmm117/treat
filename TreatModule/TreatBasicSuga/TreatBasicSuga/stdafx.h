// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

#include <atlapp.h>
#include <atldlgs.h>
#include <atlctrls.h>
#include <atlmisc.h>
#include <atlwin.h>

#include <msxml.h>
#include <msxml2.h>

#include <vector>
#include <map>


typedef struct _BASIC_SUGA
{
	CString strCode;
	CString strName;
	CString strCost;

} _S_BASIC_SUGA;

#define DEF_CLINIC_SUGA			0
#define DEF_HOSPCITY_SUGA		1
#define DEF_HOSPUBMYUN_SUGA		2
#define DEF_TOP_HOSPCITY_SUGA	3
#define DEF_TOP_HOSPUBMYUN_SUGA 4

