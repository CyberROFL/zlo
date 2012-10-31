#include <utils/logger/zlo_logger.hpp>

#include <Windows.h>

namespace zlo {
namespace utils {

void logger::log(
    const log_level& level,
    const tstring&   message )
{
#ifndef _DEBUG
    if (level > information)
#endif
    ::OutputDebugString( (message + _T('\n')).c_str() );
}

void logger::log(
    const log_level& level,
    const tformat&   message )
{
    tstring message_ = str( message );

#ifndef _DEBUG
    if (level > information)
#endif
    ::OutputDebugString( (message_ + _T('\n')).c_str() );
}

} // namespace utils
} // namespace zlo
