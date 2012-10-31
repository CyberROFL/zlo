#include <client/browser/item/zlo_browse_item.hpp>

#include <algorithm>
#include <iterator>

namespace zlo {

client::browser::item::item( client* const client_ ) :
    _name  (_T("")),
    _type  (type_node),
    _parent(nullptr),
    _client(client_)
{
}

client::browser::item::item(
    const tstring& name,
    const type&    type_,
    item* const    parent ) :

    _name  (name),
    _type  (type_),
    _parent(parent),
    _client(parent->_client)
{
}

tstring client::browser::item::getFullPath() const
{
    tstring ret = _name;

    item* parent = _parent;

    while (parent && !parent->_name.empty())
    {
        ret = parent->_name + _T('.') + ret;

        parent = parent->_parent;
    }

    return ret;
}

client::browser::item_list client::browser::item::browse(
    const filter_type& filter,
    const bool&        cache,
    const tstring&     criteria,
    const VARTYPE&     vt )
{
    item_list items = _client->getBrowser()->browse( filter, this, criteria, vt );

    if (cache)
    {
        std::copy( items.begin(), items.end(), std::back_inserter(_items) );
    }

    return std::move( items );
}

void client::browser::item::clearCache()
{
    _items.clear();
}

} // namespace zlo
