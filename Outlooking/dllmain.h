// dllmain.h: 模块类的声明。

class COutlookingModule : public ATL::CAtlDllModuleT< COutlookingModule >
{
public :
	DECLARE_LIBID(LIBID_OutlookingLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_OUTLOOKING, "{1dc44e0a-22d9-4c7f-9a78-0d1df1b574ca}")
};

extern class COutlookingModule _AtlModule;
