// TreatBasicViewModule.h : Declaration of the CTreatBasicViewModule

#pragma once
#include "resource.h"       // main symbols



#include "TreatBasicSuga_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CTreatBasicViewModule

class ATL_NO_VTABLE CTreatBasicViewModule :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTreatBasicViewModule, &CLSID_TreatBasicViewModule>,
	public IDispatchImpl<ITreatBasicViewModule, &IID_ITreatBasicViewModule, &LIBID_TreatBasicSugaLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CTreatBasicViewModule() : m_lHospDiv(0), m_strStandDate(_T("20150101"))
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TREATBASICVIEWMODULE)


BEGIN_COM_MAP(CTreatBasicViewModule)
	COM_INTERFACE_ENTRY(ITreatBasicViewModule)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(ShowBasicView)(VARIANT_BOOL* vbResult);
	STDMETHOD(ChildDestroy)();

private:
	long	m_lHospDiv;
	CString m_strStandDate;
public:
	STDMETHOD(GetTreatEnvData)(LONG* plHospDiv, BSTR* pbstrStandDate);
};

OBJECT_ENTRY_AUTO(__uuidof(TreatBasicViewModule), CTreatBasicViewModule)
