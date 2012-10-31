#include <client/browser/detail/zlo_browser_impl.hpp>
#include <session/zlo_session.hpp>
#include <client/browser/item/zlo_browse_item.hpp>

#include <boost/make_shared.hpp>

#include <algorithm>

namespace zlo {

client::browser::impl::impl( session_ptr session_ ) :
    _session   (session_),
    _pOpcBrowse(nullptr)
{
    HRESULT hResult = _session->getInstance()->QueryInterface(
        IID_IOPCBrowseServerAddressSpace,
        (void**)&_pOpcBrowse
    );

    if (FAILED(hResult))
        zlo_throw_exception( browse_failed );
}

client::browser::impl::~impl()
{
    if (_pOpcBrowse)
        _pOpcBrowse->Release();
}

client::browser::item_list client::browser::impl::browse(
    const filter_type& filter,
    item* const        node,
    const tstring&     criteria,
    const VARTYPE&     vt )
{
    // First, browse to parent branch
    if (!browseTo( node ))
        return item_list();

    OPCBROWSETYPE dwFilter;

    switch (filter)
    {
    case filter_node: dwFilter = OPC_BRANCH; break;
    case filter_tag:  dwFilter = OPC_LEAF;   break;
    }

    IEnumString* pEnumString;

    HRESULT hResult = _pOpcBrowse->BrowseOPCItemIDs(
        dwFilter,
        criteria.c_str(),
        vt,
        0,
        &pEnumString );

    if (FAILED(hResult))
        return item_list();

    LPOLESTR  name;
    ULONG     celt = 0;
    item_list items;

    while (S_OK == pEnumString->Next( 1, &name, &celt ))
    {
        if (filter_node == filter)
            items.push_back( boost::make_shared< item >(name, item::type_node, node) );
        else
            items.push_back( boost::make_shared< item >(name, item::type_tag,  node) );

        ::CoTaskMemFree( name );
    }

    pEnumString->Release();

    return std::move( items );
}

const bool client::browser::impl::browseTo( item* const node )
{
    HRESULT hResult = _pOpcBrowse->ChangeBrowsePosition(
        OPC_BROWSE_TO,
        node->getFullPath().c_str()
    );

    if (FAILED(hResult))
        return false;

    return true;
}

} // namespace zlo
