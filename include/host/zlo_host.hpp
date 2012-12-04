#ifndef zlo_host_hpp__
#define zlo_host_hpp__

#include <zlo_types.hpp>
#include <zlo_exception.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <list>

namespace zlo {

// Forward declarations
class host;
typedef boost::shared_ptr< host >   host_ptr;
typedef std::list< host_ptr >       host_list;

class server;
typedef boost::shared_ptr< server > server_ptr;
typedef std::list< server_ptr >     server_list;

class host :
    public boost::noncopyable,
    public boost::enable_shared_from_this< host >
{
public:
    zlo_decl_exception( host_unreachable );
    zlo_decl_exception( opc_enum_unavailable );

public:
    host( const tstring& name );

public:
    const tstring& getName() const { return _name; };

    server_list browse();

    const bool ping() const;

private:
    tstring _name;
};

} // namespace zlo

#endif // zlo_host_hpp__
