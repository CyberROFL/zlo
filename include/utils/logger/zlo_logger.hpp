#ifndef zlo_logger_hpp__
#define zlo_logger_hpp__

#include <zlo_types.hpp>

#include <boost/noncopyable.hpp>
#include <boost/format.hpp>

namespace zlo {
namespace utils {

class logger : public boost::noncopyable
{
public:
#ifdef UNICODE
    typedef boost::wformat tformat;
#else
    typedef boost::format tformat;
#endif

    enum log_level
    {
        success = 0,
        information,
        warning,
        error
    };

public:
    void log(
        const log_level& level,
        const tstring&   message );

    void log(
        const log_level& level,
        const tformat&   message );
};

} // namespace utils
} // namespace zlo

#endif // zlo_logger_hpp__
