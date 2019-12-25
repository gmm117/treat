// dllmain.h : Declaration of module class.

class CTreatWrapperModule : public ATL::CAtlDllModuleT< CTreatWrapperModule >
{
public :
	DECLARE_LIBID(LIBID_TreatWrapperLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TREATWRAPPER, "{AB446EE5-318B-4359-9345-87625FD92BC2}")
};

extern class CTreatWrapperModule _AtlModule;
