#ifndef zlo_browser_hpp__
#define zlo_browser_hpp__

#include <zlo_types.hpp>
#include <client/zlo_client.hpp>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <list>

#include <windows.h>

namespace zlo {

class client::browser : public boost::noncopyable
{
// Pointer to implementation
private:
    class impl;
    typedef boost::shared_ptr< impl > impl_ptr;
    impl_ptr _pImpl;

public:
    class item;
    typedef boost::shared_ptr< item > item_ptr;
    typedef std::list< item_ptr >     item_list;

public:
    enum filter_type {
         filter_node,
         filter_tag
    };

public:
    browser(
        session_ptr session_,
        client*     client_ );

public:
    item_list browse(
        const filter_type& filter,
        item* const        node,
        const tstring&     criteria = _T(""),
        const VARTYPE&     vt       = VT_EMPTY );

    item* const getRoot() const { return _rootItem.get(); };

private:
    item_ptr _rootItem;
};

} // namespace zlo

#endif // zlo_browser_hpp__
