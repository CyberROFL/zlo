#ifndef zlo_client_hpp__
#define zlo_client_hpp__

#include <zlo_types.hpp>

#include <boost/shared_ptr.hpp>

namespace zlo {

// Forward declarations
class client;
typedef boost::shared_ptr< client > client_ptr;

class session;
typedef boost::shared_ptr< session > session_ptr;

class client
{
public:
    class group;
    typedef boost::shared_ptr< group > group_ptr;

    class browser;
    typedef boost::shared_ptr< browser > browser_ptr;

public:
    client(
        session_ptr    session_,
        unsigned long& updateRate );

public:
    const tstring& getName() const;

    group* const getGroup();

    browser* const getBrowser();

private:
    session_ptr _session;
    group_ptr   _group;
    browser_ptr _browser;
};

} // namespace zlo

#endif // zlo_client_hpp__
