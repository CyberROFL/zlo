#ifndef zlo_server_hpp__
#define zlo_server_hpp__

#include <zlo_types.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <windows.h>

namespace zlo {

// Forward declarations
class host;
typedef boost::shared_ptr< host > host_ptr;

class session;
typedef boost::shared_ptr< session > session_ptr;

class server : public boost::noncopyable
{
public:
    server(
        host_ptr       host_,
        const CLSID&   clsId,
        const tstring& progId,
        const tstring& name );

public:
    const host_ptr& getHost() const  { return _host; };

    const tstring& getProgId() const { return _progId; };

    const tstring& getName() const   { return _name; };

    session_ptr connect();

private:
    host_ptr _host;
    CLSID    _clsId;
    tstring  _progId;
    tstring  _name;
};

} // namespace zlo

#endif // zlo_server_hpp__
