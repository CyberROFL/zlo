#ifndef error_obtainer_hpp__
#define error_obtainer_hpp__

#include <zlo_types.hpp>

#include <windows.h>

namespace zlo {
namespace utils {

// Simple tuple with 3 arguments.
//  1. Return value.
//  2. Code of error.
//  3. String with description of error code.

template< typename T >
class obtained_return
{
public:
    obtained_return() :
        _return(0),
        _id    (0)
    {
    };

    obtained_return(
        const T&       return_,
        const DWORD&   id_,
        const tstring& what_ ) :

        _return(return_),
        _id    (id_),
        _what  (what_)
    {
    };

public:
    operator T() const          { return _return;  };
    const DWORD& id() const     { return _id;      };
    const tstring& what() const { return _what;    };

private:
    T       _return;
    DWORD   _id;
    tstring _what;
};

// Explains error code.
//
// Return: tuple with return value, error code and description.

template< typename T >
inline const typename obtained_return< T > obtain_return(
    const T&     return_,
    const DWORD& errorId )
{
#define ERRMSGBUFFERSIZE (256)

    HLOCAL pBuffer;

    if (FACILITY_MSMQ == HRESULT_FACILITY( errorId ))
    {
        HINSTANCE hInst = ::LoadLibraryEx(
                              _T("MQUTIL.DLL"),
                              NULL,
                              DONT_RESOLVE_DLL_REFERENCES |
                              LOAD_LIBRARY_AS_DATAFILE );
        
        if (hInst)
        {
            ::FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | // Function will handle memory allocation
                FORMAT_MESSAGE_FROM_HMODULE | // Using a module's message table
                FORMAT_MESSAGE_IGNORE_INSERTS,
                hInst, // Handle to the DLL
                errorId, // Message identifier
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPTSTR)&pBuffer, // Buffer that will hold the text string
                ERRMSGBUFFERSIZE, // Allocate at least this many chars for pBuffer
                NULL ); // No insert values
        }
    }
    else
    {
        ::FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | // The function will allocate space for pBuffer
            FORMAT_MESSAGE_FROM_SYSTEM | // System wide message
            FORMAT_MESSAGE_IGNORE_INSERTS, // No inserts
            NULL, // Message is not in a module
            errorId, // Message identifier
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            (LPTSTR)&pBuffer, // Buffer to hold the text string
            ERRMSGBUFFERSIZE, // The function will allocate at least this much for pBuffer
            NULL ); // No inserts
    }

    // Construct message string first.
    tstring what(reinterpret_cast< LPCTSTR >(pBuffer));

    // Free buffer after.
    ::LocalFree( pBuffer );

    return obtained_return< T >(return_, errorId, what);
}

} // namespace utils
} // namespace zlo

#endif // error_obtainer_hpp__
