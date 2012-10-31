#ifndef zlo_instance_hpp__
#define zlo_instance_hpp__

#include <zlo_types.hpp>
#include <utils/error_obtainer/error_obtainer.hpp>

#include <boost/noncopyable.hpp>

#include <cassert>

#include <Unknwn.h>

namespace zlo {
namespace utils {

// Wraps and manage IUnknown*.

template< typename TUnknown = IUnknown >
class instance : public boost::noncopyable
{
public:
    instance() : _pUnknown(nullptr)
    {
        ::CoInitializeEx( NULL, COINIT_MULTITHREADED );
    };

    ~instance()
    {
        if (_pUnknown)
            while (_pUnknown->Release());

        ::CoUninitialize();
    };

public:
    const obtained_return< bool > create(
        const tstring& hostName,
        const IID*     pIid,
        const CLSID&   clsId )
    {
        assert (nullptr == _pUnknown);

        COAUTHINFO   cai;
        COSERVERINFO csi;
        MULTI_QI     results;

        cai.dwAuthnLevel         = RPC_C_AUTHN_LEVEL_CONNECT;
        cai.dwAuthnSvc           = RPC_C_AUTHN_WINNT; // NTLMSSP
        cai.dwAuthzSvc           = RPC_C_AUTHZ_NONE; // Currently, RPC_C_AUTHN_WINNT use only RPC_C_AUTHZ_NONE
        cai.dwCapabilities       = EOAC_NONE; // Currently, this member must be EOAC_NONE
        cai.dwImpersonationLevel = RPC_C_IMP_LEVEL_IMPERSONATE; // This value must be RPC_C_IMP_LEVEL_IMPERSONATE or above
        cai.pwszServerPrincName  = NULL; // If you are using RPC_C_AUTHN_WINNT, the principal name must be NULL
        cai.pAuthIdentityData    = NULL;

        csi.pAuthInfo            = &cai;
        csi.pwszName             = const_cast< LPTSTR >(hostName.c_str());
        csi.dwReserved1          = NULL;
        csi.dwReserved2          = NULL;

        results.pIID             = pIid;
        results.pItf             = NULL;
        results.hr               = S_OK;

        HRESULT hResult = ::CoCreateInstanceEx(
            clsId,
            NULL,
            CLSCTX_INPROC_SERVER |
            CLSCTX_LOCAL_SERVER |
            CLSCTX_REMOTE_SERVER,
            &csi,
            1,
            &results );

        if (SUCCEEDED(hResult))
            _pUnknown = results.pItf;

        return obtain_return( SUCCEEDED(hResult), hResult );
    }

    void release()
    {
        assert (nullptr != _pUnknown);

        while (_pUnknown->Release());
        _pUnknown = nullptr;
    };

    template< typename T > inline T* get() const
    {
        assert (nullptr != _pUnknown);

        return static_cast< T* >(_pUnknown);
    };

    TUnknown* operator->() const
    {
        return get< TUnknown >();
    };

    operator bool() const
    {
        return (nullptr != _pUnknown);
    };

private:
    IUnknown* _pUnknown;
};

} // namespace utils
} // namespace zlo

#endif // zlo_instance_hpp__
