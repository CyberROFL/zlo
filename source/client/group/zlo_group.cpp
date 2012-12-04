#include <client/group/zlo_group.hpp>
#include <client/group/detail/zlo_group_impl.hpp>
#include <client/group/item/zlo_group_item.hpp>
#include <session/zlo_session.hpp>

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

#include <cassert>

namespace zlo {

client::group::group(
    const tstring& name,
    unsigned long& updateRate,
    session_ptr    session_,
    client* const  parent ) :

    _pImpl(
        boost::make_shared< impl >(
            name, updateRate, session_
        )
    ),
    _parent(parent)
{
    _pImpl->onItemChange( boost::bind( &group::onItemChangeInt, this, _1, _2, _3, _4 ) );
}

client::group::item* const client::group::addItem( const tstring& name )
{
    assert (!name.empty());

    item_ptr item_ = _pImpl->addItem( name, this );

    if (!item_)
        return nullptr;

    auto ret = _items.insert( item_map::value_type(name, item_) );

    assert (ret.second);

    return ret.first->second.get();
}

void client::group::removeItem( const tstring& name )
{
    assert (!name.empty());

    auto it = _items.find( name );

    if (_items.end() == it)
        return;

    _pImpl->removeItem( it->second );

    _items.erase( it );
}

bool client::group::writeItem(
    const tstring& name,
    const VARIANT& value,
    const WORD&    quality )
{
    assert (!name.empty());

    auto it = _items.find( name );

    if (_items.end() == it)
        return false;

    return _pImpl->writeItem( it->second, value, quality );
}

bool client::group::isItemExists( const tstring& name ) const
{
    return (_items.end() != _items.find( name ));
}

void client::group::onItemChangeInt(
    const tstring&  name,
    const VARIANT&  value,
    const WORD&     quality,
    const FILETIME& timestamp )
{
    auto it = _items.find( name );

    if (_items.end() == it)
        return;

    it->second->setValue    ( value );
    it->second->setQuality  ( quality );
    it->second->setTimestamp( timestamp );

    _onItemChange( it->second.get() );
}

} // namespace zlo
