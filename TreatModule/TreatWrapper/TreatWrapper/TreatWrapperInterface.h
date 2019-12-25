// TreatWrapperInterface.h : Declaration of the CTreatWrapperInterface

#pragma once

#ifndef __TREATWRAPPER_INTERFACE_H_
#define __TREATWRAPPER_INTERFACE_H_

#include "resource.h"       // main symbols
#include "TreatWrapper_i.h"
#include "ADO.h"
#include "XmlBasicSugaParser.h"
#include "XmlBasicControlParser.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CTreatWrapperInterface

class ATL_NO_VTABLE CTreatWrapperInterface :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTreatWrapperInterface, &CLSID_TreatWrapperInterface>,
	public IDispatchImpl<ITreatWrapperInterface, &IID_ITreatWrapperInterface, &LIBID_TreatWrapperLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{

	//////////////////////////////////////////////////////////////////////////////////
	// 생성자 소멸자																	//
	//////////////////////////////////////////////////////////////////////////////////
public:
	CTreatWrapperInterface();
	~CTreatWrapperInterface();

	//////////////////////////////////////////////////////////////////////////////
	// COM Interface Map															//
	//////////////////////////////////////////////////////////////////////////////

DECLARE_REGISTRY_RESOURCEID(IDR_TREATWRAPPERINTERFACE)

BEGIN_COM_MAP(CTreatWrapperInterface)
	COM_INTERFACE_ENTRY(ITreatWrapperInterface)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

DECLARE_PROTECT_FINAL_CONSTRUCT()

public:
	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	//////////////////////////////////////////////////////////////////////////////
	// Message Handler															//
	//////////////////////////////////////////////////////////////////////////////
public:
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	//////////////////////////////////////////////////////////////////////////////////
	// Member Interface																//
	//////////////////////////////////////////////////////////////////////////////////
public:
	STDMETHOD(CreateModule)(IUnknown* pUnkn);
	STDMETHOD(ChildDestroy)();

	//////////////////////////////////////////////////////////////////////////////////
	// Member Functiion																//
	//////////////////////////////////////////////////////////////////////////////////
public:
	bool InitializeXML();



	//////////////////////////////////////////////////////////////////////////////////
	// Member Values																//
	//////////////////////////////////////////////////////////////////////////////////
private:
	CADOConnection m_obADOConnect;
	

public:
	// 기초수가 관련 인터페이스
	STDMETHOD(LoadBasicSuga)(long lHospDiv, BSTR bstrStandDate, BSTR* pvarCode, BSTR* pvarName, BSTR* pvarCost, short nCount, VARIANT_BOOL* pResult);
	STDMETHOD(GetStandDate)(long lHospDiv, BSTR* pbstrStandDate);
	
	// 기초수가 진찰료 관련 인터페이스
	STDMETHOD(GetTotalBasicContSize)(long* plDataSize);
	STDMETHOD(GetCurControlSize)(long lContIdx, long* plCurSize);
	STDMETHOD(GetCurData)(long lContIdx, BSTR* pbstrData);
	STDMETHOD(GetCurContRect)(long lContIdx, long* plLeft, long* plTop, long* plRight, long* plBottom);
	STDMETHOD(GetCurContStatic)(long lContIdx, BSTR* pbstrData);

	STDMETHOD(GetCurCode)(long lContIdx, BSTR* pbstrData);
};
#endif // __TREATWRAPPER_INTERFACE_H_

OBJECT_ENTRY_AUTO(__uuidof(TreatWrapperInterface), CTreatWrapperInterface)
