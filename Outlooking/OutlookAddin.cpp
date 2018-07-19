// OutlookAddin.cpp: COutlookAddin 的实现

#include "stdafx.h"
#include "OutlookAddin.h"


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
