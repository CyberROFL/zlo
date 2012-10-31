#include <client/browser/zlo_browser.hpp>
#include <client/browser/detail/zlo_browser_impl.hpp>
#include <client/browser/item/zlo_browse_item.hpp>
#include <session/zlo_session.hpp>

#include <boost/make_shared.hpp>

#include <algorithm>

namespace zlo {

client::browser::browser(
    session_ptr session_,
    client*     client_ ) :

    _pImpl(boost::make_shared< impl >(session_))
{
    _rootItem = boost::make_shared< item >(client_);
}

client::browser::item_list client::browser::browse(
    const filter_type& filter,
    item* const        node,
    const tstring&     criteria,
    const VARTYPE&     vt )
{
    return std::move( _pImpl->browse( filter, node, criteria, vt ) );
}

} // namespace zlo
