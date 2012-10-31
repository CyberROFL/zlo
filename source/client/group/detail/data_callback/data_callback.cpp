#include <client/group/detail/data_callback/data_callback.hpp>

namespace zlo {

client::group::impl::data_callback::data_callback() : _ulRefs(0)
{
}

STDMETHODIMP client::group::impl::data_callback::OnDataChange(
    DWORD      dwTransid,
    OPCHANDLE  hGroup,
    HRESULT    hrMasterquality,
    HRESULT    hrMastererror,
    DWORD      dwCount,
    OPCHANDLE* phClientItems,
    VARIANT*   pvValues,
    WORD*      pwQualities,
    FILETIME*  pftTimeStamps,
    HRESULT*   pErrors )
{
    for (DWORD ii = 0; ii < dwCount; ++ii)
    {
        _onItemChange(
            phClientItems[ii],
            pvValues[ii],
            pwQualities[ii],
            pftTimeStamps[ii]
        );
    }

    return S_OK;
}

STDMETHODIMP client::group::impl::data_callback::OnReadComplete(
    DWORD      dwTransid,
    OPCHANDLE  hGroup,
    HRESULT    hrMasterquality,
    HRESULT    hrMastererror,
    DWORD      dwCount,
    OPCHANDLE* phClientItems,
    VARIANT*   pvValues,
    WORD*      pwQualities,
    FILETIME*  pftTimeStamps,
    HRESULT*   pErrors )
{
    return S_OK;
}

STDMETHODIMP client::group::impl::data_callback::OnWriteComplete(
    DWORD      dwTransid,
    OPCHANDLE  hGroup,
    HRESULT    hrMastererr,
    DWORD      dwCount,
    OPCHANDLE* pClienthandles,
    HRESULT*   pErrors )
{
    return S_OK;
}

STDMETHODIMP client::group::impl::data_callback::OnCancelComplete(
    DWORD     dwTransid,
    OPCHANDLE hGroup )
{
    return S_OK;
}

STDMETHODIMP client::group::impl::data_callback::QueryInterface(
    REFIID  iid,
    LPVOID* ppInterface )
{
    if (NULL == ppInterface)
    {
        return E_INVALIDARG;
    }

    if (IID_IUnknown == iid)
    {
        *ppInterface = dynamic_cast< IUnknown* >(this);
        AddRef();

        return S_OK;
    }

    if (IID_IOPCDataCallback == iid)
    {
        *ppInterface = dynamic_cast< IOPCDataCallback* >(this);
        AddRef();

        return S_OK;
    }

    if (IID_IOPCShutdown == iid)
    {
        *ppInterface = dynamic_cast< IOPCShutdown* >(this);
        AddRef();

        return S_OK;
    }

    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) client::group::impl::data_callback::AddRef()
{
    return InterlockedIncrement( (LONG*)&_ulRefs ); 
}

STDMETHODIMP_(ULONG) client::group::impl::data_callback::Release()
{
    ULONG ulRefs = InterlockedDecrement( (LONG*)&_ulRefs ); 

    if (0 == ulRefs) 
    { 
        delete this; 
        return 0; 
    } 

    return ulRefs;
}

} // namespace zlo
