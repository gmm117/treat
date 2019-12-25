// dllmain.h : Declaration of module class.

class CTreatWebViewModule : public ATL::CAtlDllModuleT< CTreatWebViewModule >
{
public :
	DECLARE_LIBID(LIBID_TreatWebViewLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TREATWEBVIEW, "{301EDA0E-4F91-467A-BB1B-62BA99BD8651}")
};

extern class CTreatWebViewModule _AtlModule;
