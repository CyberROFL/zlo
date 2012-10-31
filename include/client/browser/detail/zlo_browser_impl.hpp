#ifndef zlo_browser_impl_hpp__
#define zlo_browser_impl_hpp__

#include <zlo_types.hpp>
#include <zlo_exception.hpp>
#include <client/browser/zlo_browser.hpp>

#include <opcda.h>

namespace zlo {

class client::browser::impl
{
public:
    zlo_decl_exception( browse_failed );

public:
    impl( session_ptr session_ );
    ~impl();

public:
    item_list browse(
        const filter_type& filter,
        item* const        node,
        const tstring&     criteria,
        const VARTYPE&     vt );

private:
    const bool browseTo( item* const node );

private:
    session_ptr                   _session;
    IOPCBrowseServerAddressSpace* _pOpcBrowse;
};

} // namespace zlo

#endif // zlo_browser_impl_hpp__
