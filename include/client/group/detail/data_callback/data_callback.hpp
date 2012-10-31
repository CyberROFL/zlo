#ifndef zlo_data_callback_hpp__
#define zlo_data_callback_hpp__

#include <client/group/detail/zlo_group_impl.hpp>

#include <boost/signals.hpp>

#include <OpcEnum.h>
#include <opcda.h>

namespace zlo {

class client::group::impl::data_callback : public IOPCDataCallback
{
public:
    data_callback();

public:
    STDMETHODIMP OnDataChange(
        DWORD      dwTransid, 
        OPCHANDLE  hGroup, 
        HRESULT    hrMasterquality,
        HRESULT    hrMastererror,
        DWORD      dwCount, 
        OPCHANDLE* phClientItems, 
        VARIANT*   pvValues, 
        WORD*      pwQualities,
        FILETIME*  pftTimeStamps,
        HRESULT*   pErrors );

    STDMETHODIMP OnReadComplete(
        DWORD      dwTransid,
        OPCHANDLE  hGroup,
        HRESULT    hrMasterquality,
        HRESULT    hrMastererror,
        DWORD      dwCount,
        OPCHANDLE* phClientItems,
        VARIANT*   pvValues,
        WORD*      pwQualities,
        FILETIME*  pftTimeStamps,
        HRESULT*   pErrors );

    STDMETHODIMP OnWriteComplete(
        DWORD      dwTransid,
        OPCHANDLE  hGroup,
        HRESULT    hrMastererr,
        DWORD      dwCount,
        OPCHANDLE* pClienthandles,
        HRESULT*   pErrors );

    STDMETHODIMP OnCancelComplete(
        DWORD      dwTransid,
        OPCHANDLE  hGroup );

    STDMETHODIMP QueryInterface(
        REFIID     iid,
        LPVOID*    ppInterface );

    STDMETHODIMP_(ULONG) AddRef();

    STDMETHODIMP_(ULONG) Release();

private:
    ULONG _ulRefs;

public:
    void onItemChange( const boost::function< void(const OPCHANDLE&,
                                                   const VARIANT&,
                                                   const WORD&,
                                                   const FILETIME&) >& f ) {
        _onItemChange.connect( f );
    };

private:
    boost::signal< void(const OPCHANDLE&,
                        const VARIANT&,
                        const WORD&,
                        const FILETIME&) > _onItemChange;
};

} // namespace zlo

#endif // zlo_data_callback_hpp__