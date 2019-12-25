// dllmain.h : Declaration of module class.

class CTreatConsultModule : public ATL::CAtlDllModuleT< CTreatConsultModule >
{
public :
	DECLARE_LIBID(LIBID_TreatConsultLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TREATCONSULT, "{1D85405B-EA03-414A-82DD-AA8B85642AFC}")
};

extern class CTreatConsultModule _AtlModule;
