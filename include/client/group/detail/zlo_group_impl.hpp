#ifndef zlo_group_impl_hpp__
#define zlo_group_impl_hpp__

#include <zlo_types.hpp>
#include <zlo_exception.hpp>
#include <client/group/zlo_group.hpp>

#include <boost/unordered_map.hpp>
#include <boost/signals.hpp>

#include <opcda.h>

namespace zlo {

class client::group::impl
{
private:
    typedef boost::unordered_map< OPCHANDLE, tstring > hash_map;

public:
    zlo_decl_exception( bad_group_name );
    zlo_decl_exception( connection_point_not_supported );
    zlo_decl_exception( data_callback_not_supported );
    zlo_decl_exception( data_callback_not_advised );
    zlo_decl_exception( io_not_supported );

private:
    class data_callback;

public:
    impl(
        const tstring& name,
        unsigned long& updateRate,
        session_ptr    session_ );
    ~impl();

public:
    item_ptr addItem(
        const tstring& name,
        group* const   group_ );

    void removeItem( const item_ptr& item_ );

    bool writeItem(
        const item_ptr& item_,
        const VARIANT&  value,
        const WORD&     quality );

private:
    void onItemChangeInt(
        const OPCHANDLE& hItem,
        const VARIANT&   value,
        const WORD&      quality,
        const FILETIME&  timestamp );

private:
    session_ptr       _session;
    OPCHANDLE         _handle;
    IOPCItemMgt*      _pOpcItemMgt;
    IConnectionPoint* _pConnectionPoint;
    DWORD             _cookie;
    data_callback*    _callback;
    IOPCSyncIO2*      _pOpcSyncIo2;
    IOPCSyncIO*       _pOpcSyncIo;
    DWORD             _nItems;
    hash_map          _hash_map;

public:
    void onItemChange( const boost::function< void(const tstring&,
                                                   const VARIANT&,
                                                   const WORD&,
                                                   const FILETIME& ) >& f ) {
        _onItemChange.connect( f );
    };

private:
    boost::signal< void(const tstring&,
                        const VARIANT&,
                        const WORD&,
                        const FILETIME&) > _onItemChange;
};

} // namespace zlo

#endif // zlo_group_impl_hpp__
