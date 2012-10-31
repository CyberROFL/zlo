#include <utils/rpc_ping/zlo_rpc_ping.hpp>
#include <utils/instance/zlo_instance.hpp>

#include <boost/thread.hpp>

#include <Unknwn.h>

namespace zlo {
namespace utils {

const obtained_return< bool > rpc_ping(
    const tstring& hostName,
    const int&     timeout )
{
    static struct
    {
        DWORD _return;

        void operator()(
            const tstring& hostName,
            const IID*     pIid,
            const CLSID&   clsId )
        {
            _return = 0x800706ba; // RPC server is unavailable.
            _return = instance<>().create( hostName, pIid, clsId ).id();
            // TODO: memory leak here
        };

    } worker;

    IUnknown* noSuchClass = nullptr;
    CLSID     noSuchClsid = { 0xf3839019, 0x166b, 0x4ec4, { 0x85, 0x6c, 0xcc, 0x68, 0x37, 0x1a, 0xc7, 0xb2 } };

    // Run thread and wait for 'timeout' time.
    boost::thread( boost::ref(worker), hostName, &(__uuidof(noSuchClass)), noSuchClsid ).
       timed_join( boost::posix_time::milliseconds(timeout) );

    // For a nonexistent class we must get REGDB_E_CLASSNOTREG error.
    // If so - it's ok.
    if (REGDB_E_CLASSNOTREG == worker._return)
        worker._return = S_OK;

    return obtain_return( (S_OK == worker._return), worker._return );
}

const void rpc_ping_async(
    const tstring& hostName,
    const int&     timeout,
    const boost::function< void(obtained_return< bool >) >& f )
{
    static struct
    {
        obtained_return< bool > _return;

        void operator()(
            const tstring& hostName,
            const int&     timeout,
            const boost::function< void(obtained_return< bool >) >& f )
        {
            f( rpc_ping( hostName, timeout ) );
        };

    } worker;

    boost::thread( boost::ref(worker), hostName, timeout, f );
}

} // namespace utils
} // namespace zlo
