#pragma once
#pragma warning (disable: 4800)

#include <vector>

#pragma pack( push, old_pack, 1 )

#define ECNBOOKCODE_NAME_SIZE               9   // ECN Book Code 'Name' field allows maximum 8 unicode characters
#define MAX_ECNLIST_SIZE                    128
#define ECN_BOOKORDER_REFNUM_SIZE           18
#define ECN_BOOKORDER_MMNAME_SIZE           9

//
// 3rd-party ECN Book Code
//
struct ECNBOOKCODE
{
    unsigned short usBookCode;
    wchar_t szBookName[ECNBOOKCODE_NAME_SIZE];

    enum {
        _HIDDEN_ECN_CODE=0x1
    };
    DWORD dwBookFlags;

    ECNBOOKCODE() : usBookCode(0), dwBookFlags(0) { ZeroMemory(szBookName, sizeof(szBookName)); }
    ECNBOOKCODE(unsigned short code, LPWSTR sName, DWORD dwFlags=0) : usBookCode(code), dwBookFlags(dwFlags) {
        wcsncpy_s(szBookName, sName, _TRUNCATE);
    }
    ~ECNBOOKCODE() {};

    short GetCode() { return usBookCode; }
    LPWSTR GetName() { return szBookName; }
    DWORD GetFlag() { return dwBookFlags; }
};
typedef std::vector<ECNBOOKCODE> V_ECNBOOKCODES;
typedef ECNBOOKCODE* PECNBOOKCODE;


//
// Market Maker Book Request Parameters
//
struct RTBOOKREQPARAMS
{
    wchar_t szEcnList[MAX_ECNLIST_SIZE];
    bool bAggregate;
    DWORD dwOrderLevels;
    int flags;

    RTBOOKREQPARAMS()
    {
        memset(szEcnList, 0, sizeof(szEcnList));
        bAggregate = FALSE;
        dwOrderLevels = 0;
        flags = 0;
    }

    RTBOOKREQPARAMS(const wchar_t* pList, bool bAgg, DWORD dwLevels, int flags)
    {
        setData(pList, bAgg, dwLevels, flags);
    }

    void setData(const wchar_t* pList, bool bAgg, DWORD dwLevels, int flags)
    {
        if (pList) wcsncpy_s(szEcnList, pList, _TRUNCATE);
        bAggregate = bAgg;
        dwOrderLevels = dwLevels;
        this->flags = flags;
    }
};
typedef std::vector<RTBOOKREQPARAMS> V_RTBOOKREQPARAMS;
typedef RTBOOKREQPARAMS* PRTBOOKREQPARAMS;


//
// Market Maker Book Orders
//
struct RT_BOOKORDERS_EX
{
    enum {REQUEST_BOOK_INFO=0x01, REQUEST_ORDERS=0x02, REQUEST_DATA_OPTIONS=0x04, REQUEST_ECN=0x08, REQUEST_DATA=0x10, REQUEST_SIMULATOR=0x20};

    enum {_VERSION = 2, _VERSION_DATA_PROVIDER = 3}; // ucVersion
    enum {_NULL_POSITION=0xFF}; // ucPositionCode

    struct INTERNAL {
        enum {_FLAG_ADDED=0x40, _FLAG_NEW=0x80}; // ucOrderFlags(backend only)
    };
    enum {_DELETED=0x01, _CLOSED=0x02}; // ucOrderFlags(generic)
    struct OTC {
        enum {_UNSOLICITED=0x04, _BIDOFFER_WANT = 0x08, _DIVIDED_BY_100 = 0x10}; // ucOrderFlags for systemcode::otc
    };
    enum {_BBO_INELIGIBLE=0x04, _IMPLIED=0x08, _HALT=0x10, _SUBSCRIBER_ONLY=0x20}; // ucOrderFlags for systemcode that is not flex or otc
    struct FLEX {
        enum {_PREOPEN=0, _REGULAR=1, _SPECIAL=3, _CONTINUOUS=4, _SPECIAL_PRIOR2HALT=7, _CONTINUOUS_PRIOR2HALT=8, _NO_QUANTITY=9,
              _MARKET_ORDER_NO_PRICE=10, _CLOSING_AUCTION=13, _CLOSING_AUCTION_MKT_ORDER=14 };
    };
    enum {_BID=0x01, _ASK=0x02, _STALE=0x04, _ECNBOOK=0x08, _SUPER_SOES=0x10, _ADF=0x20}; // ucOrderType
    enum {_FLEX='4', _OTC='6'}; // system codes

    double   dPrice;
    LONG     lSize;
    LONG     lTime;
    LONG     lSystemCode;
    DWORD    dwUniqueID;

    UCHAR    ucOrderFlags;
    UCHAR    ucBookCode;   // obsolete - only used for ECN books!
    UCHAR    ucOrderType;
    UCHAR    ucPositionCode; // used internally
    UCHAR    ucAggDepth; // amount of bid/ask aggregated
    UCHAR    ucVersion;  // version...

    // Do not modify anything above this line..
    union {
        char    szOrderRefNumber[ECN_BOOKORDER_REFNUM_SIZE];
        wchar_t mmaker_name[ECN_BOOKORDER_MMNAME_SIZE];
    };

    RT_BOOKORDERS_EX() { Reset(); }
    ~RT_BOOKORDERS_EX(){}
    void Reset() {ZeroMemory(this, sizeof(RT_BOOKORDERS_EX)); ucPositionCode=RT_BOOKORDERS_EX::_NULL_POSITION; ucVersion=_VERSION; }

    static UCHAR getFlexOrderFlags(UCHAR flags) { return (flags & 0x3C) >> 2; }
}; // 48 bytes
typedef std::vector<RT_BOOKORDERS_EX> V_RTBOOKORDERS;
typedef RT_BOOKORDERS_EX* P_BOOKORDERS;

#pragma warning (default : 4800 )
#pragma pack(pop,old_pack)
