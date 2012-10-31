#include <server/zlo_server.hpp>
#include <host/zlo_host.hpp>
#include <session/zlo_session.hpp>

#include <boost/make_shared.hpp>

namespace zlo {

server::server(
    host_ptr       host_,
    const CLSID&   clsId,
    const tstring& progId,
    const tstring& name ) :

    _host  (host_),
    _clsId (clsId),
    _progId(progId),
    _name  (name)
{
}

session_ptr server::connect()
{
    if (!_host->ping())
        zlo_throw_exception( host::host_unreachable );

    return boost::make_shared< session >(_name, _host->getName(), _clsId);
}

} // namespace zlo
