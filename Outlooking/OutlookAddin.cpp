// OutlookAddin.cpp: COutlookAddin 的实现

#include "stdafx.h"
#include "OutlookAddin.h"

static const TCHAR kWNDClass[] = L"rctrl_renwnd32";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (FALSE == ::IsWindow(hwnd)) return S_FALSE;
    if (msg == WM_CLOSE) {
        msg = WM_SYSCOMMAND;
        wparam = SC_MINIMIZE;
        lparam = NULL;
    }

    auto original_window_proc = ::GetWindowLongPtr(hwnd, GWLP_USERDATA);

    return CallWindowProc((WNDPROC)(original_window_proc), hwnd, msg, wparam, lparam);
}

// COutlookAddin

STDMETHODIMP COutlookAddin::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IOutlookAddin
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP COutlookAddin::OnConnection(LPDISPATCH Application, ext_ConnectMode ConnectMode, LPDISPATCH AddInInst, SAFEARRAY ** custom)
{
    // TODO: Outlook may have multiple window instance, there just only attach the firest window.
    auto outlook = FindWindowEx(NULL, NULL, kWNDClass, NULL);
    original_window_proc_ = ::GetWindowLongPtr(outlook, GWLP_WNDPROC);
    SetWindowLongPtr(outlook, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProc));
    SetWindowLongPtr(outlook, GWLP_USERDATA, original_window_proc_);
    return E_NOTIMPL;
}

STDMETHODIMP COutlookAddin::OnDisconnection(ext_DisconnectMode RemoveMode, SAFEARRAY ** custom)
{
    shutdown_ = RemoveMode == ext_dm_HostShutdown;
    return S_OK;
}
