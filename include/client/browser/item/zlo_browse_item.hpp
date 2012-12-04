#ifndef zlo_browse_item_hpp__
#define zlo_browse_item_hpp__

#include <zlo_types.hpp>
#include <client/browser/zlo_browser.hpp>

#include <list>

namespace zlo {

class client::browser::item
{
private:
    typedef boost::shared_ptr< item > item_ptr;
    typedef std::list< item_ptr >     item_list;

public:
    enum type {
         type_node,
         type_tag
    };

public:
    item( client* const client_ );

    item(
        const tstring& name,
        const type&    type_,
        item* const    parent );

public:
    const tstring& getName() const  { return _name; };

    const type& getItemType() const     { return _type; };

    item* const getParent() const   { return _parent; };

    client* const getClient() const { return _client; };

    bool isBrowsed() const          { return !_items.empty(); };

    tstring getFullPath() const;

    item_list browse(
        const filter_type& filter,
        const bool&        cache    = true,
        const tstring&     criteria = _T(""),
        const VARTYPE&     vt       = VT_EMPTY );

    void clearCache();

private:
    tstring   _name;
    type      _type;
    item*     _parent;
    client*   _client;
    item_list _items;
};

} // namespace zlo

#endif // zlo_browse_item_hpp__
