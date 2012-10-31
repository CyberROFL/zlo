#ifndef zlo_item_hpp__
#define zlo_item_hpp__

#include <zlo_types.hpp>
#include <client/group/zlo_group.hpp>

#include <windows.h>

namespace zlo {

class client::group::item
{
public:
    item(
        const tstring& name,
        const DWORD&   handle,
        group* const   group_ );

public:
    const tstring& getName() const { return _name; };

    const DWORD& getHandle() const { return _handle; };

    tstring getValueStr() const;

    const VARTYPE& getType() const;

    tstring getTypeStr() const;

    const WORD& getQuality() const;

    tstring getQualityStr() const;

    __time64_t getTimestamp() const;

    tstring getTimestampStr() const;

    void setValue( const VARIANT& value );

    void setQuality( const WORD& quality );

    bool write( const VARIANT& value, const WORD& quality );

    bool write( const tstring& valueStr, const WORD& quality );

    void removeThis();

private:
    friend class group;
    void setTimestamp( const FILETIME& timestamp );

private:
    tstring    _name;
    DWORD      _handle;
    group*     _parent;
    VARIANT    _value;
    WORD       _quality;
    SYSTEMTIME _timestamp;
};

} // namespace zlo

#endif // zlo_item_hpp__
