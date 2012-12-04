#include <host/zlo_host.hpp>
#include <server/zlo_server.hpp>
#include <opc/zlo_opc_instances.hpp>
#include <utils/rpc_ping/zlo_rpc_ping.hpp>

#include <boost/make_shared.hpp>

#include <algorithm>

#include <windows.h>

namespace zlo {

host::host( const tstring& name ) :
    _name(name)
{
}

server_list host::browse()
{
    if (!ping())
        zlo_throw_exception( host_unreachable );

    opc::enum_instance opcEnum;

    if (!opcEnum.create( _name, &IID_IOPCServerList, CLSID_OpcServerList ))
        zlo_throw_exception( opc_enum_unavailable );

    // Filter
    CATID filter[] = { IID_CATID_OPCDAServer20 };

    IEnumCLSID* pEnumClsid;

    // Get enumerator
    HRESULT hResult = opcEnum->EnumClassesOfCategories(
        1, filter, 0, NULL, &pEnumClsid );

    if (FAILED(hResult) || !pEnumClsid)
        return server_list();

    GUID        guid;
    ULONG       celt = 0;
    server_list servers;

    // Enumerate
    while (S_OK == pEnumClsid->Next( 1, &guid, &celt ))
    {
        CLSID    clsId = guid;
        LPOLESTR progId;
        LPOLESTR name;

        // Get server info
        if (S_OK == opcEnum->GetClassDetails( clsId, &progId, &name ))
        {
            servers.push_back(
                boost::make_shared< server >(
                    shared_from_this(), clsId, progId, name
                )
            );
        }

        ::CoTaskMemFree( progId );
        ::CoTaskMemFree( name );
    }

    pEnumClsid->Release();

    return std::move( servers );
}

const bool host::ping() const
{
    return utils::rpc_ping( _name, 500 );
}

} // namespace zlo
