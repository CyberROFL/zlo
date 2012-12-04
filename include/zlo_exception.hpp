#ifndef zlo_exception_hpp__
#define zlo_exception_hpp__

#include <boost/exception/all.hpp>

namespace zlo {

#define zlo_decl_exception( xClass ) \
    class xClass : public std::exception \
    { \
    public: \
        xClass() {}; \
        virtual ~xClass() throw() {}; \
    }

#define zlo_throw_exception( xClass ) \
    BOOST_THROW_EXCEPTION( xClass() )


zlo_decl_exception( create_instance_failed );

} // namespace zlo

#endif // zlo_exception_hpp__
