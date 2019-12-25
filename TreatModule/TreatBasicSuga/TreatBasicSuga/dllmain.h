// dllmain.h : Declaration of module class.

class CTreatBasicSugaModule : public ATL::CAtlDllModuleT< CTreatBasicSugaModule >
{
public :
	DECLARE_LIBID(LIBID_TreatBasicSugaLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TREATBASICSUGA, "{26559EDE-1D64-4419-8B1A-B25AD4F68AD6}")
};

extern class CTreatBasicSugaModule _AtlModule;
