// OutlookAddin.h: COutlookAddin 的声明

#pragma once
#include "resource.h"       // 主符号



#include "Outlooking_i.h"
#include "_IOutlookAddinEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// COutlookAddin

class ATL_NO_VTABLE COutlookAddin :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<COutlookAddin, &CLSID_OutlookAddin>,
    public ISupportErrorInfo,
    public IConnectionPointContainerImpl<COutlookAddin>,
    public CProxy_IOutlookAddinEvents<COutlookAddin>,
    public IDispatchImpl<IOutlookAddin, &IID_IOutlookAddin, &LIBID_OutlookingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IDispatchImpl<_IDTExtensibility2, &__uuidof(_IDTExtensibility2), &LIBID_AddInDesignerObjects, /* wMajor = */ 1>,
    public IDispatchImpl<IAddinDesigner, &__uuidof(IAddinDesigner), &LIBID_AddInDesignerObjects, /* wMajor = */ 1>,
    public IDispatchImpl<IAddinInstance, &__uuidof(IAddinInstance), &LIBID_AddInDesignerObjects, /* wMajor = */ 1>
{
public:
    COutlookAddin()
    {
        m_pUnkMarshaler = nullptr;
    }

    DECLARE_REGISTRY_RESOURCEID(106)


    BEGIN_COM_MAP(COutlookAddin)
        COM_INTERFACE_ENTRY(IOutlookAddin)
        COM_INTERFACE_ENTRY2(IDispatch, _IDTExtensibility2)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
        COM_INTERFACE_ENTRY(IConnectionPointContainer)
        COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
        COM_INTERFACE_ENTRY(_IDTExtensibility2)
        COM_INTERFACE_ENTRY(IAddinDesigner)
        COM_INTERFACE_ENTRY(IAddinInstance)
    END_COM_MAP()

    BEGIN_CONNECTION_POINT_MAP(COutlookAddin)
        CONNECTION_POINT_ENTRY(__uuidof(_IOutlookAddinEvents))
    END_CONNECTION_POINT_MAP()
    // ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


    DECLARE_PROTECT_FINAL_CONSTRUCT()
    DECLARE_GET_CONTROLLING_UNKNOWN()

    HRESULT FinalConstruct()
    {
        return CoCreateFreeThreadedMarshaler(
            GetControllingUnknown(), &m_pUnkMarshaler.p);
    }

    void FinalRelease()
    {
        m_pUnkMarshaler.Release();
    }

    CComPtr<IUnknown> m_pUnkMarshaler;
    bool shutdown_ = false;
    LONG_PTR original_window_proc_ = NULL;

public:




    // _IDTExtensibility2 Methods
public:
    STDMETHOD(OnConnection)(LPDISPATCH Application, ext_ConnectMode ConnectMode, LPDISPATCH AddInInst, SAFEARRAY * * custom);
    STDMETHOD(OnDisconnection)(ext_DisconnectMode RemoveMode, SAFEARRAY * * custom);

    STDMETHOD(OnAddInsUpdate)(SAFEARRAY * * custom)
    {
        return S_OK;
    }
    STDMETHOD(OnStartupComplete)(SAFEARRAY * * custom)
    {
        return S_OK;
    }
    STDMETHOD(OnBeginShutdown)(SAFEARRAY * * custom)
    {
        return S_OK;
    }

    // IAddinDesigner Methods
public:

    // IAddinInstance Methods
public:
};

OBJECT_ENTRY_AUTO(__uuidof(OutlookAddin), COutlookAddin)
