#include <session/zlo_session.hpp>

namespace zlo {

session::session(
    const tstring& name,
    const tstring& hostName,
    const CLSID&   clsId ) :

    _name(name)
{
    _instance.create( hostName, &IID_IOPCServer, clsId );
}

} // namespace zlo
