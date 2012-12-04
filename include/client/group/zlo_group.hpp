#ifndef zlo_group_hpp__
#define zlo_group_hpp__

#include <zlo_types.hpp>
#include <client/zlo_client.hpp>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/signals.hpp>

#include <windows.h>

namespace zlo {

class client::group : public boost::noncopyable
{
// Pointer to implementation
private:
    class impl;
    typedef boost::shared_ptr< impl > impl_ptr;
    impl_ptr _pImpl;

public:
    class item;
private:
    typedef boost::shared_ptr< item > item_ptr;
    typedef boost::unordered_map< tstring, item_ptr > item_map;

public:
    group(
        const tstring& name,
        unsigned long& updateRate,
        session_ptr    session_,
        client* const  parent );

public:
    client* const getClient() const { return _parent; };

    item* const addItem( const tstring& name );

    void removeItem( const tstring& name );

    bool writeItem(
        const tstring& name,
        const VARIANT& value,
        const WORD&    quality );

    bool isItemExists( const tstring& name ) const;

private:
    void onItemChangeInt(
        const tstring&  name,
        const VARIANT&  value,
        const WORD&     quality,
        const FILETIME& timestamp );

private:
    client*  _parent;
    item_map _items;

public:
    void onItemChange( const boost::function< void(item* const) >& f ) {
        _onItemChange.connect( f );
    };

private:
    boost::signal< void(item* const) > _onItemChange;
};

} // namespace zlo

#endif // zlo_group_hpp__
