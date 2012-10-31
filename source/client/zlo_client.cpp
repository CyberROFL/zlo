#include <client/zlo_client.hpp>
#include <client/group/zlo_group.hpp>
#include <client/browser/zlo_browser.hpp>
#include <session/zlo_session.hpp>

#include <boost/make_shared.hpp>

#include <cassert>

namespace zlo {

client::client(
    session_ptr    session_,
    unsigned long& updateRate ) :

    _session(session_)
{
    assert (_session);

    _group = boost::make_shared< group >(_T(""), updateRate, _session, this);
}

const tstring& client::getName() const
{
    return _session->getName();
}

client::group* const client::getGroup()
{
    assert (_group);

    return _group.get();
}

client::browser* const client::getBrowser()
{
    if (!_browser)
        _browser = boost::make_shared< browser >(_session, this);
        
    return _browser.get();
}

} // namespace zlo
