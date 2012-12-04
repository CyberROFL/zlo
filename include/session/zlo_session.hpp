#ifndef zlo_session_hpp__
#define zlo_session_hpp__

#include <zlo_types.hpp>
#include <zlo_exception.hpp>
#include <opc/zlo_opc_instances.hpp>

#include <windows.h>

namespace zlo {

// Keeps instance alive for session.

class session
{
public:
    session(
        const tstring& name,
        const tstring& hostName,
        const CLSID&   clsId );

public:
    const tstring& getName() const                  { return _name; };

    const opc::server_instance& getInstance() const { return _instance; };

private:
    tstring              _name;
    opc::server_instance _instance;
};

} // namespace zlo

#endif // zlo_session_hpp__
