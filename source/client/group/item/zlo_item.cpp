#include <client/group/item/zlo_item.hpp>

#include <boost/lexical_cast.hpp>

#include <cassert>

#include <opcda.h>

#if UNICODE
#   define _OPC_T(x)    L#x
#else
#   define _OPC_T(x)    #x
#endif

namespace zlo {

client::group::item::item(
    const tstring& name,
    const DWORD&   handle,
    group* const   group_ ) :

    _name  (name),
    _handle(handle),
    _parent(group_)
{
    _value.vt = VT_EMPTY;
    _quality  = OPC_QUALITY_UNCERTAIN;
}

tstring client::group::item::getValueStr() const
{
    using namespace boost;

    switch (_value.vt)
    {
    case VT_EMPTY: // nothing
        return _T("");

    case VT_I1: // signed char
        return lexical_cast< tstring, int >(_value.cVal);

    case VT_UI1: // unsigned char
        return lexical_cast< tstring >(_value.bVal);

    case VT_I2: // 2 byte signed int
        return lexical_cast< tstring >(_value.iVal);

    case VT_UI2: // unsigned short
        return lexical_cast< tstring >(_value.uiVal);

    case VT_I4: // 4 byte signed int
        return lexical_cast< tstring >(_value.lVal);

    case VT_UI4: // unsigned long
        return lexical_cast< tstring >(_value.ulVal);

    case VT_I8: // signed 64-bit int
        return lexical_cast< tstring >(_value.llVal);

    case VT_UI8: // unsigned 64-bit int
        return lexical_cast< tstring >(_value.ullVal);

    case VT_INT: // signed machine int
        return lexical_cast< tstring >(_value.intVal);

    case VT_UINT: // unsigned machine int
        return lexical_cast< tstring >(_value.uintVal);

    case VT_R4: // 4 byte real
        return lexical_cast< tstring >(_value.fltVal);

    case VT_R8: // 8 byte real
        return lexical_cast< tstring >(_value.dblVal);

    case VT_DECIMAL: // 16 byte fixed point
        return _T("unsupported");

    case VT_BOOL: // True=-1, False=0
        return (_value.boolVal ? _T("true") : _T("false"));

    case VT_CY: // currency
        return _T("unsupported");

    case VT_DATE: // date
        return _T("unsupported");

    case VT_BSTR: // OLE Automation string
        return _value.bstrVal;

    case VT_LPSTR: // null terminated string
        return _T("unsupported");

    case VT_LPWSTR: // wide null terminated string
        return _T("unsupported");

    case VT_FILETIME: // FILETIME
        return _T("unsupported");

    case VT_CLSID: //  A Class ID
        return _T("unsupported");

    case VT_NULL: // SQL style Null
        return _T("unsupported");

    case VT_DISPATCH: // IDispatch *
        return _T("unsupported");

    case VT_ERROR: // SCODE
        return _T("unsupported");

    case VT_VARIANT: // VARIANT *
        return _T("unsupported");

    case VT_UNKNOWN: // IUnknown *
        return _T("unsupported");

    case VT_VOID: // C style void
        return _T("unsupported");

    case VT_HRESULT: // Standard return type
        return _T("unsupported");

    case VT_PTR: // pointer type
        return _T("unsupported");

    case VT_SAFEARRAY: // (use VT_ARRAY in VARIANT)
        return _T("unsupported");

    case VT_CARRAY: // C style array
        return _T("unsupported");

    case VT_USERDEFINED: // user defined type
        return _T("unsupported");

    case VT_RECORD: // user defined type
        return _T("unsupported");

    case VT_INT_PTR: // signed machine register size width
        return _T("unsupported");

    case VT_UINT_PTR: // unsigned machine register size width
        return _T("unsupported");

    case VT_BLOB: // Length prefixed bytes
        return _T("unsupported");

    case VT_STREAM: // Name of the stream follows
        return _T("unsupported");

    case VT_STORAGE: // Name of the storage follows
        return _T("unsupported");

    case VT_STREAMED_OBJECT: // Stream contains an object
        return _T("unsupported");

    case VT_STORED_OBJECT: // Storage contains an object
        return _T("unsupported");

    case VT_BLOB_OBJECT: // Blob contains an object 
        return _T("unsupported");

    case VT_CF: // Clipboard format
        return _T("unsupported");

    case VT_VERSIONED_STREAM: // Stream with a GUID version
        return _T("unsupported");

    case VT_BSTR_BLOB: // Reserved for system use
        return _T("unsupported");

    case VT_VECTOR: // simple counted array
        return _T("unsupported");

    case VT_ARRAY: // SAFEARRAY*
        return _T("unsupported");

    case VT_BYREF: // void* for local use
        return _T("unsupported");
    }

    return _T("unsupported");
}

const VARTYPE& client::group::item::getType() const
{
    return _value.vt;
}

zlo::tstring client::group::item::getTypeStr() const
{
    switch (_value.vt)
    {
    case VT_EMPTY:            return _OPC_T( VT_EMPTY );
    case VT_I1:               return _OPC_T( VT_I1 );
    case VT_UI1:              return _OPC_T( VT_UI1 );
    case VT_I2:               return _OPC_T( VT_I2 );
    case VT_UI2:              return _OPC_T( VT_UI2 );
    case VT_I4:               return _OPC_T( VT_I4 );
    case VT_UI4:              return _OPC_T( VT_UI4 );
    case VT_I8:               return _OPC_T( VT_I8 );
    case VT_UI8:              return _OPC_T( VT_UI8 );
    case VT_INT:              return _OPC_T( VT_INT );
    case VT_UINT:             return _OPC_T( VT_UINT );
    case VT_R4:               return _OPC_T( VT_R4 );
    case VT_R8:               return _OPC_T( VT_R8 );
    case VT_DECIMAL:          return _OPC_T( VT_DECIMAL );
    case VT_BOOL:             return _OPC_T( VT_BOOL );
    case VT_CY:               return _OPC_T( VT_CY );
    case VT_DATE:             return _OPC_T( VT_DATE );
    case VT_BSTR:             return _OPC_T( VT_BSTR );
    case VT_LPSTR:            return _OPC_T( VT_LPSTR );
    case VT_LPWSTR:           return _OPC_T( VT_LPWSTR );
    case VT_FILETIME:         return _OPC_T( VT_FILETIME );
    case VT_CLSID:            return _OPC_T( VT_CLSID );
    case VT_NULL:             return _OPC_T( VT_NULL );
    case VT_DISPATCH:         return _OPC_T( VT_DISPATCH );
    case VT_ERROR:            return _OPC_T( VT_ERROR );
    case VT_VARIANT:          return _OPC_T( VT_VARIANT );
    case VT_UNKNOWN:          return _OPC_T( VT_UNKNOWN );
    case VT_VOID:             return _OPC_T( VT_VOID );
    case VT_HRESULT:          return _OPC_T( VT_HRESULT );
    case VT_PTR:              return _OPC_T( VT_PTR );
    case VT_SAFEARRAY:        return _OPC_T( VT_SAFEARRAY );
    case VT_CARRAY:           return _OPC_T( VT_CARRAY );
    case VT_USERDEFINED:      return _OPC_T( VT_USERDEFINED );
    case VT_RECORD:           return _OPC_T( VT_RECORD );
    case VT_INT_PTR:          return _OPC_T( VT_INT_PTR );
    case VT_UINT_PTR:         return _OPC_T( VT_UINT_PTR );
    case VT_BLOB:             return _OPC_T( VT_BLOB );
    case VT_STREAM:           return _OPC_T( VT_STREAM );
    case VT_STORAGE:          return _OPC_T( VT_STORAGE );
    case VT_STREAMED_OBJECT:  return _OPC_T( VT_STREAMED_OBJECT );
    case VT_STORED_OBJECT:    return _OPC_T( VT_STORED_OBJECT );
    case VT_BLOB_OBJECT:      return _OPC_T( VT_BLOB_OBJECT );
    case VT_CF:               return _OPC_T( VT_CF );
    case VT_VERSIONED_STREAM: return _OPC_T( VT_VERSIONED_STREAM );
    case VT_BSTR_BLOB:        return _OPC_T( VT_BSTR_BLOB );
    case VT_VECTOR:           return _OPC_T( VT_VECTOR );
    case VT_ARRAY:            return _OPC_T( VT_ARRAY );
    case VT_BYREF:            return _OPC_T( VT_BYREF );
    }

    return _T("undefined");
}

const WORD& client::group::item::getQuality() const
{
    return _quality;
}

tstring client::group::item::getQualityStr() const
{
    switch (_quality)
    {
    case OPC_QUALITY_BAD:                      return _OPC_T( BAD );
    case OPC_QUALITY_CONFIG_ERROR:             return _OPC_T( CONFIG_ERROR );
    case OPC_QUALITY_NOT_CONNECTED:            return _OPC_T( NOT_CONNECTED );
    case OPC_QUALITY_DEVICE_FAILURE:           return _OPC_T( DEVICE_FAILURE );
    case OPC_QUALITY_SENSOR_FAILURE:           return _OPC_T( SENSOR_FAILURE );
    case OPC_QUALITY_LAST_KNOWN:               return _OPC_T( LAST_KNOWN );
    case OPC_QUALITY_COMM_FAILURE:             return _OPC_T( COMM_FAILURE );
    case OPC_QUALITY_OUT_OF_SERVICE:           return _OPC_T( OUT_OF_SERVICE );
    case OPC_QUALITY_WAITING_FOR_INITIAL_DATA: return _OPC_T( WAITING_FOR_INITIAL_DATA );
    case OPC_QUALITY_UNCERTAIN:                return _OPC_T( UNCERTAIN );
    case OPC_QUALITY_LAST_USABLE:              return _OPC_T( LAST_USABLE );
    case OPC_QUALITY_SENSOR_CAL:               return _OPC_T( SENSOR_CAL );
    case OPC_QUALITY_EGU_EXCEEDED:             return _OPC_T( EGU_EXCEEDED );
    case OPC_QUALITY_SUB_NORMAL:               return _OPC_T( SUB_NORMAL );
    case OPC_QUALITY_GOOD:                     return _OPC_T( GOOD );
    case OPC_QUALITY_LOCAL_OVERRIDE:           return _OPC_T( LOCAL_OVERRIDE );
    }

    return _T("undefined");
}

__time64_t client::group::item::getTimestamp() const
{
    struct tm tm_;

    tm_.tm_year  = _timestamp.wYear - 1900;
    tm_.tm_mon   = _timestamp.wMonth - 1;
    tm_.tm_wday  = _timestamp.wDayOfWeek - 1;
    tm_.tm_mday  = _timestamp.wDay;
    tm_.tm_hour  = _timestamp.wHour;
    tm_.tm_min   = _timestamp.wMinute;
    tm_.tm_sec   = _timestamp.wSecond;
    tm_.tm_isdst = 0;

    return _mktime64( &tm_ );
}

tstring client::group::item::getTimestampStr() const
{
    TCHAR str[255] = { _T('\0'), };
    
    int dateLen = ::GetDateFormat(
        LOCALE_USER_DEFAULT,
        DATE_SHORTDATE,
        &_timestamp, NULL, str, 255
    );

    if (dateLen <= 0)
        return _T("");

    str[dateLen - 1] = _T(' ');

    ::GetTimeFormat(
        LOCALE_USER_DEFAULT,
        0,
        &_timestamp, NULL, &str[dateLen], 255 - dateLen );
    
    return str;
}

void client::group::item::setValue( const VARIANT& value )
{
    _value = value;
}

void client::group::item::setQuality( const WORD& quality )
{
    _quality = quality;
}

void client::group::item::setTimestamp( const FILETIME& timestamp )
{
    FILETIME ft;

    ::FileTimeToLocalFileTime( &timestamp, &ft );
    ::FileTimeToSystemTime   ( &ft, &_timestamp );
}

bool client::group::item::write( const VARIANT& value, const WORD& quality )
{
    assert (_parent);

    bool ret = _parent->writeItem( _name, value, quality );

    if (ret)
    {
        _value   = value;
        _quality = quality;
    }

    return ret;
}

bool client::group::item::write( const tstring& valueStr, const WORD& quality )
{
    assert (_parent);

    using namespace boost;

    VARIANT value;

    value.vt = _value.vt;

    try
    {
        switch (_value.vt)
        {
        case VT_I1: // signed char
            value.cVal = (lexical_cast< SHORT >(valueStr) & 0xFF);
            break;

        case VT_UI1: // unsigned char
            value.bVal = (lexical_cast< USHORT >(valueStr) & 0xFF);
            break;

        case VT_I2: // 2 byte signed int
            value.iVal = lexical_cast< SHORT >(valueStr);
            break;

        case VT_UI2: // unsigned short
            value.uiVal = lexical_cast< USHORT >(valueStr);
            break;

        case VT_I4: // 4 byte signed int
            value.lVal = lexical_cast< LONG >(valueStr);
            break;

        case VT_UI4: // unsigned long
            value.ulVal = lexical_cast< ULONG >(valueStr);
            break;

        case VT_I8: // signed 64-bit int
            value.llVal = lexical_cast< LONGLONG >(valueStr);
            break;

        case VT_UI8: // unsigned 64-bit int
            value.ullVal = lexical_cast< ULONGLONG >(valueStr);
            break;

        case VT_INT: // signed machine int
            value.intVal = lexical_cast< INT >(valueStr);
            break;

        case VT_UINT: // unsigned machine int
            value.uintVal = lexical_cast< UINT >(valueStr);
            break;

        case VT_R4: // 4 byte real
            value.fltVal = lexical_cast< FLOAT >(valueStr);
            break;

        case VT_R8: // 8 byte real
            value.dblVal = lexical_cast< DOUBLE >(valueStr);
            break;

        case VT_BOOL: // True=-1, False=0
            value.boolVal = (valueStr == _T("true") ? -1 : 0);
            break;

        default:
            return false;
        }
    }
    catch (boost::bad_lexical_cast&)
    {
    }

    return write( value, quality );
}

void client::group::item::removeThis()
{
    assert (_parent);

    _parent->removeItem( _name );
}

} // namespace zlo
