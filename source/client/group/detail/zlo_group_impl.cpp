#include <client/group/detail/zlo_group_impl.hpp>
#include <client/group/detail/data_callback/data_callback.hpp>
#include <client/group/item/zlo_group_item.hpp>
#include <session/zlo_session.hpp>

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

namespace zlo {

client::group::impl::impl(
    const tstring& name,
    unsigned long& updateRate,
    session_ptr    session_ ) :

    _session         (session_),
    _handle          (0),
    _pOpcItemMgt     (nullptr),
    _pConnectionPoint(nullptr),
    _cookie          (0),
    _callback        (new data_callback),
    _pOpcSyncIo2     (nullptr),
    _pOpcSyncIo      (nullptr),
    _nItems          (0)
{
    // Add group
    HRESULT hResult = _session->getInstance()->AddGroup(
        name.c_str(),
        TRUE, // Group is to be created as active
        updateRate,
        NULL,
        NULL, // Group use the default system TimeBias
        NULL,
        LOCALE_SYSTEM_DEFAULT,
        &_handle,
        &updateRate,
        IID_IOPCItemMgt,
        (IUnknown**)&_pOpcItemMgt
    );

    if (FAILED(hResult))
        zlo_throw_exception( bad_group_name );

    // Set connection point
    IConnectionPointContainer* pCPÑ;
    hResult = _pOpcItemMgt->QueryInterface( IID_IConnectionPointContainer, (void**)&pCPÑ );

    if (FAILED(hResult))
        zlo_throw_exception( connection_point_not_supported );

    // Find data callback interface
    hResult = pCPÑ->FindConnectionPoint( IID_IOPCDataCallback, &_pConnectionPoint );

    if (FAILED(hResult))
        zlo_throw_exception( data_callback_not_supported );

    hResult = _pConnectionPoint->Advise( _callback, &_cookie );

    if (FAILED(hResult))
        zlo_throw_exception( data_callback_not_advised );

    _callback->onItemChange( boost::bind( &impl::onItemChangeInt, this, _1, _2, _3, _4 ) );

    hResult = _pOpcItemMgt->QueryInterface( IID_IOPCSyncIO2, (void**)&_pOpcSyncIo2 );

    if (FAILED(hResult))
    {
        hResult = _pOpcItemMgt->QueryInterface( IID_IOPCSyncIO, (void**)&_pOpcSyncIo );

        if (FAILED(hResult))
            zlo_throw_exception( io_not_supported );
    }
}

client::group::impl::~impl()
{
    if (_pConnectionPoint)
    {
        _pConnectionPoint->Unadvise( _cookie );
        while (_pConnectionPoint->Release());
    }

    if (_pOpcItemMgt)
        while (_pOpcItemMgt->Release());

    _session->getInstance()->RemoveGroup( _handle, TRUE );
}

client::group::item_ptr client::group::impl::addItem(
    const tstring& name,
    group* const   group_ )
{
    DWORD          dwCount  = 1;
    OPCITEMDEF*    pItem   = (OPCITEMDEF*)::CoTaskMemAlloc( dwCount * sizeof(OPCITEMDEF) );
    OPCITEMRESULT* pResult = NULL;
    HRESULT*       pError  = NULL;

    pItem[0].szItemID            = const_cast< LPTSTR >(name.c_str());
    pItem[0].szAccessPath        = NULL;
    pItem[0].bActive             = TRUE;
    pItem[0].hClient             = ++_nItems;
    pItem[0].vtRequestedDataType = VT_EMPTY;
    pItem[0].dwBlobSize          = 0;
    pItem[0].pBlob               = NULL;

    HRESULT hResult = _pOpcItemMgt->AddItems( dwCount, pItem, &pResult, &pError );

    if (FAILED(hResult))
        return item_ptr();

    // Do operations before freeing.
    _hash_map.insert( hash_map::value_type(pItem[0].hClient, name) );
    item_ptr ret = boost::make_shared< item >(name, pResult[0].hServer, group_);

    // Must always free the blob that the server may return.
    if (pResult[0].dwBlobSize > 0)
        ::CoTaskMemFree( pResult[0].pBlob );

    // Free other
    ::CoTaskMemFree( pItem );
    ::CoTaskMemFree( pResult );
    ::CoTaskMemFree( pError );

    return ret;
}

void client::group::impl::removeItem( const item_ptr& item_ )
{
    DWORD      dwCount  = 1;
    OPCHANDLE* phServer = (OPCHANDLE*)::CoTaskMemAlloc( dwCount * sizeof(OPCHANDLE) );
    HRESULT*   pErrors  = NULL;

    phServer[0] = item_->getHandle();

    HRESULT hResult = _pOpcItemMgt->RemoveItems( dwCount, phServer, &pErrors );

    if (FAILED(hResult))
        return;

    ::CoTaskMemFree( phServer );
    ::CoTaskMemFree( pErrors );
}

bool client::group::impl::writeItem(
    const item_ptr& item_,
    const VARIANT&  value,
    const WORD&     quality )
{
    DWORD       dwCount  = 1;
    OPCHANDLE*  phServer = (OPCHANDLE*)::CoTaskMemAlloc( dwCount * sizeof(OPCHANDLE) );
    OPCITEMVQT* pItemVQT = (OPCITEMVQT*)::CoTaskMemAlloc( dwCount * sizeof(OPCITEMVQT) );
    VARIANT*    pItem    = (VARIANT*)::CoTaskMemAlloc( dwCount * sizeof(VARIANT) );
    HRESULT*    pError   = NULL;

    phServer[0]                     = item_->getHandle();
    pItemVQT[0].vDataValue          = value;
    pItemVQT[0].wQuality            = quality;
    pItemVQT[0].bQualitySpecified   = TRUE;
    pItemVQT[0].bTimeStampSpecified = FALSE;
    pItem   [0]                     = value;

    HRESULT hResult;

    if (_pOpcSyncIo2)
        hResult = _pOpcSyncIo2->WriteVQT( dwCount, phServer, pItemVQT, &pError );
    else if (_pOpcSyncIo)
        hResult = _pOpcSyncIo->Write( dwCount, phServer, pItem, &pError );
    else
        return false;

    if (FAILED(hResult))
        return false;

    ::CoTaskMemFree( phServer );
    ::CoTaskMemFree( pItemVQT );
    ::CoTaskMemFree( pItem );
    ::CoTaskMemFree( pError );

    return true;
}

void client::group::impl::onItemChangeInt(
    const OPCHANDLE& hItem,
    const VARIANT&   value,
    const WORD&      quality,
    const FILETIME&  timestamp )
{
    auto it = _hash_map.find( hItem );

    if (_hash_map.end() == it)
        return;

    _onItemChange(
        it->second,
        value,
        quality,
        timestamp
    );
}

} // namespace zlo
