#ifndef zlo_rpc_ping_hpp__
#define zlo_rpc_ping_hpp__

#include <zlo_types.hpp>
#include <utils/error_obtainer/error_obtainer.hpp>

#include <boost/function.hpp>

namespace zlo {
namespace utils {

// Checks the availability of DCOM on host 'hostName' synchronously.
//
// Return: true - if ping successfull, false - otherwise.

const obtained_return< bool > rpc_ping(
    const tstring& hostName,
    const int&     timeout );

// Checks the availability of DCOM on host 'hostName' asynchronously.
//
// Result of ping will be passed to the callback function 'f'.

const void rpc_ping_async(
    const tstring& hostName,
    const int&     timeout,
    const boost::function< void(obtained_return< bool >) >& f );

} // namespace utils
} // namespace zlo

#endif // zlo_rpc_ping_hpp__
