#ifndef zlo_types_hpp__
#define zlo_types_hpp__

#include <string>

namespace zlo {

// Define tstring
#if UNICODE
    typedef std::wstring tstring;
#   ifndef _T
#      define _T(x)      L ## x
#   endif
#else
    typedef std::string tstring;
#   ifndef _T
#      define _T(x)      x
#   endif
#endif

// helper
#define _TT(x) _T(x)

// File name
#define __TFILE__ _TT(__FILE__)

// Function name
#define __TFUNCTION__ _TT(__FUNCTION__)

} // namespace zlo

#endif // zlo_types_hpp__
