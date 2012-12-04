#include <session/zlo_session.hpp>

namespace zlo {

session::session(
    const tstring& name,
    const tstring& hostName,
    const CLSID&   clsId ) :

    _name(name)
{
    if (!_instance.create( hostName, &IID_IOPCServer, clsId ))
        zlo_throw_exception( create_instance_failed );
}

} // namespace zlo
