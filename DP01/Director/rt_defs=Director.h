/**
TradeStation identifiers used by Third-Party Data Providers.
*/

#ifndef rt_defs_Director_h_included
#define rt_defs_Director_h_included

#include <string>

// Time Zone information
#define WOWRTINFO_AFGHANISTAN     1
#define WOWRTINFO_ALASKAN         2
#define WOWRTINFO_ARABIAN         3
#define WOWRTINFO_ATLANTIC        4
#define WOWRTINFO_AUS_CENTRAL     5
#define WOWRTINFO_AZORES          6
#define WOWRTINFO_BANGKOK         7
#define WOWRTINFO_CANADA_CENTRAL  8
#define WOWRTINFO_CEN_AUSTRALIA   9
#define WOWRTINFO_CENTRAL_ASIA    10
#define WOWRTINFO_CENTRAL_EUROPE  11
#define WOWRTINFO_CENTRAL_PACIFIC 12
#define WOWRTINFO_CENTRAL         13
#define WOWRTINFO_CHINA           14
#define WOWRTINFO_DATELINE        15
#define WOWRTINFO_E_EUROPE        16
#define WOWRTINFO_E_SOUTH_AMERICA 17
#define WOWRTINFO_EASTERN         18
#define WOWRTINFO_EGYPT           19
#define WOWRTINFO_FIJI            20
#define WOWRTINFO_GFT             21
#define WOWRTINFO_GMT             22
#define WOWRTINFO_GMT_STD         23
#define WOWRTINFO_HAWAIIAN        24
#define WOWRTINFO_INDIA           25
#define WOWRTINFO_IRAN            26
#define WOWRTINFO_ISRAEL          27
#define WOWRTINFO_MEXICO          28
#define WOWRTINFO_MID_ATLANTIC    29
#define WOWRTINFO_MOUNTAIN        30
#define WOWRTINFO_NEW_ZEALAND     31
#define WOWRTINFO_NEWFOUNDLAND    32
#define WOWRTINFO_PACIFIC         33
#define WOWRTINFO_ROMANCE         34
#define WOWRTINFO_RUSSIAN         35
#define WOWRTINFO_SA_EASTERN      36
#define WOWRTINFO_SA_PACIFIC      37
#define WOWRTINFO_SA_WESTERN      38
#define WOWRTINFO_SAMOA           39
#define WOWRTINFO_SAUDI_ARABIA    40
#define WOWRTINFO_SOUTH_AFRICA    41
#define WOWRTINFO_SYDNEY          42
#define WOWRTINFO_TAIPEI          43
#define WOWRTINFO_TASMANIA        44
#define WOWRTINFO_TOKYO           45
#define WOWRTINFO_US_EASTERN      46
#define WOWRTINFO_US_MOUNTAIN     47
#define WOWRTINFO_W_EUROPE        48
#define WOWRTINFO_WEST_ASIA       49
#define WOWRTINFO_WEST_PACIFIC    50


// Currency
#define FDS_CURRENCY_USD        1
#define FDS_CURRENCY_CAD        2
#define FDS_CURRENCY_ARS        3
#define FDS_CURRENCY_AMD        4
#define FDS_CURRENCY_AUD        5
#define FDS_CURRENCY_ATS        6
#define FDS_CURRENCY_AZM        7
#define FDS_CURRENCY_BHD        8
#define FDS_CURRENCY_BDT        9
#define FDS_CURRENCY_BBD        10
#define FDS_CURRENCY_BYB        11
#define FDS_CURRENCY_BEF        12
#define FDS_CURRENCY_BMD        13
#define FDS_CURRENCY_BOB        14
#define FDS_CURRENCY_BWP        15
#define FDS_CURRENCY_BRL        16
#define FDS_CURRENCY_BGL        17
#define FDS_CURRENCY_CLP        18
#define FDS_CURRENCY_CNY        19
#define FDS_CURRENCY_COP        20
#define FDS_CURRENCY_CRC        21
#define FDS_CURRENCY_HRK        22
#define FDS_CURRENCY_CYP        23
#define FDS_CURRENCY_CZK        24
#define FDS_CURRENCY_DKK        25
#define FDS_CURRENCY_ECS        26
#define FDS_CURRENCY_EGP        27
#define FDS_CURRENCY_SVC        28
#define FDS_CURRENCY_EEK        29
#define FDS_CURRENCY_EUR        30
#define FDS_CURRENCY_FJD        31
#define FDS_CURRENCY_FIM        32
#define FDS_CURRENCY_FRF        33
#define FDS_CURRENCY_DEM        34
#define FDS_CURRENCY_GHC        35
#define FDS_CURRENCY_GRD        36
#define FDS_CURRENCY_HNL        37
#define FDS_CURRENCY_HKD        38
#define FDS_CURRENCY_HUF        39
#define FDS_CURRENCY_ISK        40
#define FDS_CURRENCY_INR        41
#define FDS_CURRENCY_IDR        42
#define FDS_CURRENCY_IRR        43
#define FDS_CURRENCY_IEP        44
#define FDS_CURRENCY_ILS        45
#define FDS_CURRENCY_ITL        46
#define FDS_CURRENCY_XOF        47
#define FDS_CURRENCY_JMD        48
#define FDS_CURRENCY_JPY        49
#define FDS_CURRENCY_JOD        50
#define FDS_CURRENCY_KZT        51
#define FDS_CURRENCY_KES        52
#define FDS_CURRENCY_KRW        53
#define FDS_CURRENCY_KWD        54
#define FDS_CURRENCY_LVL        55
#define FDS_CURRENCY_LTL        56
#define FDS_CURRENCY_LUF        57
#define FDS_CURRENCY_MKD        58
#define FDS_CURRENCY_MYR        59
#define FDS_CURRENCY_MTL        60
#define FDS_CURRENCY_MUR        61
#define FDS_CURRENCY_MXN        62
#define FDS_CURRENCY_MNT        63
#define FDS_CURRENCY_MAD        64
#define FDS_CURRENCY_NAD        65
#define FDS_CURRENCY_NLG        66
#define FDS_CURRENCY_NZD        67
#define FDS_CURRENCY_NGN        68
#define FDS_CURRENCY_NOK        69
#define FDS_CURRENCY_OMR        70
#define FDS_CURRENCY_PKR        71
#define FDS_CURRENCY_PAB        72
#define FDS_CURRENCY_PYG        73
#define FDS_CURRENCY_PEN        74
#define FDS_CURRENCY_PHP        75
#define FDS_CURRENCY_PLN        76
#define FDS_CURRENCY_PTE        77
#define FDS_CURRENCY_ROL        78
#define FDS_CURRENCY_RUB        79
#define FDS_CURRENCY_SAR        80
#define FDS_CURRENCY_SGD        81
#define FDS_CURRENCY_SKK        82
#define FDS_CURRENCY_SIT        83
#define FDS_CURRENCY_ZAR        84
#define FDS_CURRENCY_ESP        85
#define FDS_CURRENCY_LKR        86
#define FDS_CURRENCY_SZL        87
#define FDS_CURRENCY_SEK        88
#define FDS_CURRENCY_CHF        89
#define FDS_CURRENCY_TWD        90
#define FDS_CURRENCY_TJR        91
#define FDS_CURRENCY_THB        92
#define FDS_CURRENCY_TTD        93
#define FDS_CURRENCY_TND        94
#define FDS_CURRENCY_TRL        95
#define FDS_CURRENCY_UAH        96
#define FDS_CURRENCY_GBP        97
#define FDS_CURRENCY_UYU        98
#define FDS_CURRENCY_UZS        99
#define FDS_CURRENCY_VEB        100
#define FDS_CURRENCY_YUM        101
#define FDS_CURRENCY_ZWD        102

// Attribute types -- taken from SERVER_GENERIC_INFO
enum {
    SERVER_GENERIC_DEFAULT_INDEX                = 0,
    SERVER_GENERIC_INFO_TYPE_EXCHANGE           = 1,
    SERVER_GENERIC_INFO_TYPE_QUOTES             = 2,
    SERVER_GENERIC_INFO_TYPE_COUNTRY            = 4,
    SERVER_GENERIC_INFO_TYPE_CURRENCY           = 5,
    SERVER_GENERIC_INFO_TYPE_CONVERSION_RULES   = 6,
    SERVER_GENERIC_INFO_TYPE_NEWS_COUNTRIES     = 7
};

//***** Exchange IDs *****
#define RT_EXCHFIELD_INDEX      500 // Always available, RTFIELD_WORD
#define RT_EXCHFIELD_SUFFIX     501 // Always available, RTFIELD_LPSTR
#define RT_EXCHFIELD_SHORTNAME  502 // Always available, RTFIELD_LPSTR
#define RT_EXCHFIELD_LONGNAME   503 // Always available, RTFIELD_LPSTR
#define RT_EXCHFIELD_STARTHOUR  504 // Always available, RTFIELD_SHORT
#define RT_EXCHFIELD_STARTMIN   505 // Always available, RTFIELD_SHORT
#define RT_EXCHFIELD_CLOSEHOUR  506 // Always available, RTFIELD_SHORT
#define RT_EXCHFIELD_CLOSEMIN   507 // Always available, RTFIELD_SHORT
#define RT_EXCHFIELD_CURRENCY   508 // Always available, RTFIELD_LPSTR
#define RT_EXCHFIELD_DAYSOFWEEK 509 // Always available, RTFIELD_LPSTR
#define RT_EXCHFIELD_TIMEZONE   510 // Always available, RTFIELD_SHORT
#define RT_EXCHFIELD_EXCHDELAY  511 // Always available, RTFIELD_BYTE
#define RT_EXCHFIELD_TIME       512 // RTFIELD_LONG
#define RT_EXCHFIELD_M4_ID      513 // Internal usage

// Day of Week Definitions - Exchange
#define FDS_DAYBIT_SUNDAY       1
#define FDS_DAYBIT_MONDAY       2
#define FDS_DAYBIT_TUESDAY      4
#define FDS_DAYBIT_WEDNESDAY    8
#define FDS_DAYBIT_THURSDAY    16
#define FDS_DAYBIT_FRIDAY      32
#define FDS_DAYBIT_SATURDAY    64
#define FDS_DAYBIT_MTWRF       62
#define FDS_DAYBIT_SMTWRFD    127

// Trading Days of Week Definitions - Session
#define SESSION_DAYBIT_SATURDAY     0x02
#define SESSION_DAYBIT_FRIDAY       0x04
#define SESSION_DAYBIT_THURSDAY     0x08
#define SESSION_DAYBIT_WEDNESDAY    0x10
#define SESSION_DAYBIT_TUESDAY      0x20
#define SESSION_DAYBIT_MONDAY       0x40
#define SESSION_DAYBIT_SUNDAY       0x80

// Example - Monday through Friday session
// TradeDays = SESSION_DAYBIT_SET(SESSION_DAYBIT_MONDAY|SESSION_DAYBIT_TUESDAY|SESSION_DAYBIT_WEDNESDAY|SESSION_DAYBIT_THURSDAY|SESSION_DAYBIT_FRIDAY);
#define SESSION_DAYBIT_SET(f) (((f)&SESSION_DAYBIT_SUNDAY  ? SESSION_DAYBIT_SUNDAY  : 0) | ((f)&SESSION_DAYBIT_MONDAY  ? SESSION_DAYBIT_MONDAY  : 0) |\
                 ((f)&SESSION_DAYBIT_TUESDAY ? 0 : SESSION_DAYBIT_TUESDAY) | ((f)&SESSION_DAYBIT_WEDNESDAY  ? 0 : SESSION_DAYBIT_WEDNESDAY ) |\
                 ((f)&SESSION_DAYBIT_THURSDAY ? 0 : SESSION_DAYBIT_THURSDAY) |\
                 ((f)&SESSION_DAYBIT_FRIDAY ? SESSION_DAYBIT_FRIDAY : 0) | ((f)&SESSION_DAYBIT_SATURDAY ? SESSION_DAYBIT_SATURDAY : 0))


#define LOCAL_EXCHANGE_GROUP_SIZE 16 // Maximum of 16 local exchanges can be used per DataProviderID

#define EXCHANGE_US     0       // "US Generic"
#define EXCHANGE_ISEG   1       // "International Securities Exchanges - STOCKS only"

#define EXCHANGE_AMEX   104     // "American Stock Exchange"
#define EXCHANGE_BOS    105     // "Boston Stock Exchange"
#define EXCHANGE_CBOE   106     // "Chicago Board Options Exchange"
#define EXCHANGE_CBS    107     // "Chicago Board Stock Exchange"
#define EXCHANGE_CBOT   108     // "Chicago Board of Trade"
#define EXCHANGE_CME    109     // "Chicago Mercantile Exchange"
#define EXCHANGE_CIN    110     // "Cincinnati Stock Exchange"
#define EXCHANGE_COMEX  111     // "New York Commodity Exchange"
#define EXCHANGE_AMEM   112     // "AMEX Emerging Market"
#define EXCHANGE_FOREX  113     // "Forex"
#define EXCHANGE_DC     114     // "Discount Corp(Fixed Income}"
#define EXCHANGE_INS    115     // "Instinet"
#define EXCHANGE_ISE    116     // "International Securities Exchanges"
#define EXCHANGE_USBA   117     // "BATS Trading"
#define EXCHANGE_KCBT   118     // "Kansas City Board of Trade"
//#define EXCHANGE_MCE    119     // "MidAmerica Commodity Exchange"(obsolete)
//#define EXCHANGE_MW     120     // "MidWest Stock Exchange"(obsolete)
#define EXCHANGE_MGE    121     // "Minneapolis Grain Exchange"
#define EXCHANGE_NASDQ  122     // "NASDAQ National Market"
#define EXCHANGE_NASDA  123     // "NASDAQ Small Cap"
#define EXCHANGE_NYSE   124     // "New York Stock Exchange(NYSE}"
#define EXCHANGE_NYMEX  125     // "New York Mercantile Exchange"
#define EXCHANGE_NYBOT  126     // "New York Board of Trade"
#define EXCHANGE_PCEX   127     // "Pacific Exchange"
#define EXCHANGE_OTCBB  128     // "NASDAQ OTC BB (Domestic)"
#define EXCHANGE_OTCFR  129     // "NASDAQ OTC BB (Foreign)"
#define EXCHANGE_PBT    130     // "Philadelphia Board of Trade"
#define EXCHANGE_PHLX   131     // "Philadelphia Stock Exchange"
#define EXCHANGE_ONCH	132		// "One Chicago"
//#define EXCHANGE_NQLX  133     // "Nasdaq Liffe Markets"(obsolete)
#define EXCHANGE_ARCX	134		// "Archipelago Exchange"
#define EXCHANGE_ADFN	135		// "NASD ADF"
#define EXCHANGE_USNS   136     // "NASDAQ Global Select"
#define EXCHANGE_NASD   137     // "National Association of Securities Dealers"
#define EXCHANGE_TRF    138     // "Trade reporting facility LLC"
#define EXCHANGE_USCX   139     // "CBOE Index Exchange"
#define EXCHANGE_USBX   141     // "Boston Options Exchange"
#define EXCHANGE_CATS   142     // "Toronto Stock Exchange"
#define EXCHANGE_CAWC   143     // "Winnipeg Commodity Exchange"

#define EXCHANGE_DEFSE      150 //"DEFS","FSE","Frankfurt Stock Exchange"
// originally FDS exchange M3EXCHANGE_DERF(54) was mapped to EXCHANGE_DEREFEX(151) but it appears to be unused
//#define EXCHANGE_DEREFEX    151 //"DERF","REFEX","Reference Foreign Exchange Rates"
// now FDS exchange M3EXCHANGE_USIE is mapped to EXCHANGE_USIE
#define EXCHANGE_USIE       151 //"USIE","IEX","Investors?Exchange LLC"
//#define EXCHANGE_DENEUER    152 //"DENM","NEUER","Neuer Markt"(obsolete)
#define EXCHANGE_DEEUWAX    153 //"DEEW","EUWAX","European Warrants Exchange"
#define EXCHANGE_DEBERSE    154 //"DEBE","BERSE","Berlin Stock Exchange"
#define EXCHANGE_DEBRESE    155 //"DEBM","BRESE","Bremen Stock Exchange"
#define EXCHANGE_DEDUSSE    156 //"DEDS","DUSSE","Dusseldorf Stock Exchange"
#define EXCHANGE_DEXETRA    157 //"DEXE","Xetra","Xetra Stock Exchange"
#define EXCHANGE_DEHAMSE    158 //"DEHS","HAMSE","Hamburg Stock Exchange"
#define EXCHANGE_DEHANSE    159 //"DEHN","HANSE","Hannover Stock Exchange"
#define EXCHANGE_DEMUNSE    160 //"DEMX","MUNSE","Munich Stock Exchange"
#define EXCHANGE_DESTUSE    161 //"DEST","STUSE","Stuttgart Stock Exchange"
#define EXCHANGE_EUDE		162	//"EUDE","EUREX","EUREX (Derivatives Exchange)"
#define EXCHANGE_IEIR		163	//"IEIR","ISE","Irish Stock Exchange"
#define EXCHANGE_FIHS		164	//"FIHS","HSE","Helsinki Exchanges"
#define EXCHANGE_DEBI		165	// Deutsche Börse Index

#define EXCHANGE_DO_NOT_USE 166  // CBOE
#define EXCHANGE_DO_NOT_USE2 167 // $OEX - virtual - used in symbol entitlement ID
#define EXCHANGE_ICE		168
#define EXCHANGE_VIRTUAL_ICE 169  // ICE - R, RF2, TF ..

// section for EuroNext
#define EXCHANGE_ENIX       180 // "EuroNext Indices"
#define EXCHANGE_ENID       181 // "EuroNext Interest Rate Derivatives"
#define EXCHANGE_ENED       182 // "EuroNext Equity and Index Derivatives"
#define EXCHANGE_ENCD       183 // "EuroNext Commodities Derivatives"
#define EXCHANGE_ENCC       184 // "EuroNext Continental Commodities Deriv."

#define EXCHANGE_DE_SPOT        190 // Spot Market Germany (Frankfurt/Xetra)
#define EXCHANGE_DE_REGIONALS   191 // Regional Exchanges Germany
#define EXCHANGE_DE_XETRA_US    192 // Xetra US Stars
#define EXCHANGE_DE_XETRA_EUR   193 // Xetra European Stars
#define EXCHANGE_DE_BORSE_FUND  194 // Borse Frankfurt Funds

#define EXCHANGE_CHSE           229 // "CHSE","SWX","Swiss Exchange"

#define EXCHANGE_ALTIN  254     // "Alternative Investment Index Ticker"

#define EXCHANGE_INDICES_A 281  // $TIKI, etc.
#define EXCHANGE_INDICES_B 282  // $TVOLSPC, etc.

#define EXCHANGE_INDICES_1 291
#define EXCHANGE_INDICES_2 292
#define EXCHANGE_INDICES_3 293
#define EXCHANGE_INDICES_4 294
#define EXCHANGE_INDICES_5 295
#define EXCHANGE_INDICES_6 296
#define EXCHANGE_INDICES_7 297
#define EXCHANGE_VIRTUAL_8 298  // ES, @ES

#define EXCHANGE_OPRA   299     // OPRA
#define EXCHANGE_UNKNOWN 300        //

#define EXCHANGE_LAST   300     // LAST EXCHANGE DEFINED - update this when adding new exchanges!
#define EXCHANGE_ALL    0xFFFF  // For ranking lists..

#define EXCHANGE_HOTLISTS_JAPAN 301  // Internal only - used only by HotLists Rules
#define EXCHANGE_HOTLISTS_JP_TSE_1ST 302
#define EXCHANGE_HOTLISTS_JP_TSE_2ND 303
#define EXCHANGE_HOTLISTS_JP_TSE_MOTHERS  304
#define EXCHANGE_HOTLISTS_JP_TSE_JQ 305
#define EXCHANGE_HOTLISTS_JP_NSE_FSE_SSE 306
#define EXCHANGE_HOTLISTS_JP_EMERGING_MARKETS 307

//***** End of Exchange IDs *****

enum {TR_PRICEREC=2, TR_PRICEREC_EX, TR_INTRAPRICEREC, TR_TICKREC_OLD, TR_UNDERLYING, TR_TICKREC, TR_CNVREC, TR_SECONDBAR, TR_LAST_RECTYPE /* do not add beyond this type */ };

enum RTSecurityType
{
    RTType_Stock = 0,
    RTType_Index, // AHA Indice
    RTType_Future ,
    RTType_MutualFund,
    RTType_MoneyMarket,
    RTType_Bond,
    RTType_Forex,
    RTType_Option = 7 ,         // do not change this number, matches USACCESS.H
    RTType_FutureOption ,
    RTType_CorpBond,
    RTType_Treasury,
    RTType_IndexOption,
    RTType_CurrencyOption,
    RTType_Stock_OTC = 15,
    RTType_FutureRoot = 70 ,    // Our id, not in USACCESS.H
    RTType_FutureOptionRoot = 71 ,  // Our id, not in USACCESS.H
    RTType_StockOptionRoot = 72 ,
    RTType_IndexOptionRoot = 73 ,
    RTType_Exchange = 74, // Our id, not in M3ACCESS.h
    RTType_AllAssets = 98 ,     // make the same as USACCESS.H 5/18/97
    RTType_AssetOptionRoot = 99 ,
    RTType_UnKnown = 100,
};

// Display attributes definition
#define BASECODE_DISPLAY_REDUCE_FRACTION  0x80000000

//Display attributes.  Multiply or divide price by 10, 100, or 1000
//15th bit Multiply or divide Multiply = 0, divide = 1
//14th and 13th bit 00 = 1, 01 = 10, 10 = 100, 11 = 1000
#define BASECODE_DISPLAY_MULTIPLY_BY_10     0x10000000
#define BASECODE_DISPLAY_MULTIPLY_BY_100    0x20000000
#define BASECODE_DISPLAY_MULTIPLY_BY_1000   0x30000000
#define BASECODE_DISPLAY_DIVIDE_BY_10       0x50000000
#define BASECODE_DISPLAY_DIVIDE_BY_100      0x60000000
#define BASECODE_DISPLAY_DIVIDE_BY_1000     0x70000000

enum E_DISPTYPE {
    AUTO = 0,                  // {"Automatic"},
    E0DECIMALS = 1,            // {"0 Decimals"},
    E1DECIMALS = 2,            // {"1 Decimals"},
    E2DECIMALS = 3,            // {"2 Decimals"},
    E3DECIMALS = 4,            // {"3 Decimals"},
    E4DECIMALS = 5,            // {"4 Decimals"},
    E5DECIMALS = 6,            // {"5 Decimals"},
    SIMPLESTFRACT = 7,         // {"Simplest Fraction"},
    FRACTHALVES=  8,           // {"1/2-Halves"},
    FRACTFOURTHS = 9,          // {"1/4-Fourths"},
    FRACTEIGHTS = 10,          // {"1/8-Eights"},
    FRACTSIXTEENTHS = 11,      // {"1/16-Sixteenths"},
    FRACTTHIRTYSECONDS = 12,   // {"1/32-ThirtySeconds"},
    FRACTSIXTYFOURTHS = 13,    // {"1/64-SixtyFourths"},
    FRACTONETWENTYEIGHTS = 14, // {"1/128-OneTwentyEigths"}
    FRACTTWOFIFTYSIXTHS = 15,  // {"1/256-TwoFiftySixths"},
    FRACT10ANDQUARTERS = 16,   // {"10ths and Quarters"},
    FRACT32ANDHALVES = 17,     // {"32nds and Halves"},
    FRACT32ANDQUARTERS = 18,   // {"32nds and Quarters"},
    FRACT32ANDEIGHTS = 19,     // {"32nds and Eights"},
    FRACT32ANDTENTHS = 20,     // {"32nds and Tenths"},
    FRACT64ANDHALVES = 21,     // {"64ths and Halves"},
    FRACT64ANDTENTHS = 22,     // {"64ths and Tenths"},
    E6DECIMALS = 23            // {"6 Decimals"},
};


#define ADJUST_FROM_1970_TO_1900(x) ((x)+0x83D84540)
#define ADJUST_FROM_1900_TO_1970(x) ((x)-0x83D84540)

// These code are sent back via the notify code thru the client callbacks
// *WARNING* These codes should not be changed (assumed as such in other areas - ngcal/error_codes)
#define ERR_SUCCESS                 0
#define ERR_INVALID                 -1 // symbol not available
#define ERR_NOTENTITLED             -2
#define ERR_LIMITEXCEEDED           -3
#define ERR_INEODPROCESSING         -4
#define ERR_DELAYEDTICKHISTDISABLED -5
#define ERR_NOCCADATA               -6
#define ERR_ARCHIVE_NOSERVERAVAIL   -7
#define ERR_ARCHIVE_NOCONNECT       -8
#define ERR_ARCHIVE_DROPCONNECT     -9
#define ERR_ARCHIVE_OUTOFMEM        -10
#define ERR_NO_DATA_AVAILABLE       -11  // data not available
#define ERR_DISCONNECT_EVENT        -12
#define ERR_NOTAVAILABLE            -13
#define ERR_CACHE_WRITE				-14
#define ERR_CACHE_READ				-15

#define ERR_NO_DATA_FAILURE         -99  // internal code

#define WARN_ARCHIVE_INTERRUPTED -100
#define WARN_ARCHIVE_SERVICEDROP -101
#define WARN_ARCHIVE_USERCANCEL  -102
#define WARN_CORRECTION_EVENT    -103
#define WARN_RESET_EVENT         -104
#define WARN_PENDING_EVENT       -105
#define WARN_ACTIVE_EVENT        -106

enum RT_MarketMakersType
{
    MM_Data_Options=1,
    MM_EcnData,
    MM_BookDataComplete,  // end of history notification (only used on client side)
    MM_EcnCodes,
    MM_NotEntitled,
    MM_Data,
    MM_NotEntitledForEnhanced
};

//
// Generic error handling class - used to move from Backend error codes to front end..
// Eventually, should be used on the backend as well..
//

class CErrorCode
{
public:
    enum Attributes { free_type=0x1 };

public:
    CErrorCode() : m_nState(0), m_nError(0) {}
    CErrorCode(long state, long value=0) : m_nState(state), m_nError(value) {}
    CErrorCode(const CErrorCode& e) { *this = e; }
    CErrorCode(const CErrorCode&& e) { *this = std::move(e); }

public:
    size_t SizeOf() { return (sizeof(CErrorCode) + m_sMsg.length()); }
    void SetMsg(std::wstring & sMsg) { m_sMsg = sMsg; }
    void SetMsg(LPCWSTR szStr) { m_sMsg = szStr; }

    LPCWSTR GetMsg() { return m_sMsg.c_str(); }
    std::wstring & GetStrMsg() { return m_sMsg; }

    bool Msg() { return !m_sMsg.empty(); }
    bool Failure() const { return (m_nState<0); }
    void Reset() { m_nState=0; m_nError=0; m_sMsg.erase(); }
    bool free_data_type() const { return ((m_nAttributes & free_type)>0); }

    operator long() const {return m_nState;}

    const CErrorCode& operator=(const CErrorCode& e) { if (this!=&e) { m_nState=e.m_nState; m_nError=e.m_nError; m_sMsg = e.m_sMsg; } return *this; }
    const CErrorCode& operator=(CErrorCode&& e) { if (this!=&e) { m_nState=e.m_nState; m_nError=e.m_nError; m_sMsg = std::move(e.m_sMsg); } return *this; }

    HRESULT hresult() const {
        if (m_nState>=0) return S_OK;
        else return 0xE0000000-m_nState;
    }

    static const char* error_str(long code)
    {
        switch (code)
        {
            case ERR_SUCCESS: return "success";
            case ERR_INVALID: return "invalid";
            case ERR_NOTENTITLED: return "not entitled";
            case ERR_LIMITEXCEEDED: return "limit exceeded";
            case ERR_INEODPROCESSING: return "maintenance";
            case ERR_DELAYEDTICKHISTDISABLED: return "disabled";
            case ERR_NOCCADATA: return "no cca";
            case ERR_ARCHIVE_NOSERVERAVAIL: return "archive: not available";
            case ERR_ARCHIVE_NOCONNECT: return "archive: unable to connect";
            case ERR_ARCHIVE_DROPCONNECT: return "archive: dropped";
            case ERR_ARCHIVE_OUTOFMEM: return "archive: out of memory";
            case ERR_NO_DATA_AVAILABLE: return "no data available";
            case ERR_DISCONNECT_EVENT: return "connection dropped";
            case ERR_NOTAVAILABLE: return "server not available";
        }
        return "n/a";
    }

public:
    long m_nState;

    union {
        long m_nError;
        long m_nAttributes;
    };

private:
    std::wstring m_sMsg;
};


//***** macros for use with the callback from request securities ***************

#define FIELDSIZE(p)  (*PBYTE(p))
#define FIELDNUM(p)   (*(PBYTE(p) + 1))
#define FIELDTYPE(p)  (*(PBYTE(p) + 2))
#define FIELDDATA(p)  (PBYTE(p) + 3)
#define FIELDNEXT(p)  (PBYTE(p) + FIELDSIZE(p))

#define FIELDNUM_V9(p)  (*PBYTE(p))
#define FIELDDATA_V9(p) (PBYTE(p) + 1)

enum
{
    RT_SECFIELD_NAME=1,             // Always available, RTFIELD_LPSTR
    RT_SECFIELD_CURRDESC,           // Always available, RTFIELD_LPSTR
    RT_SECFIELD_ASSETTYPE,          // Always available, RTFIELD_SECTYPE
    RT_SECFIELD_LASTTRADE,          // Always available, RTFIELD_DOUBLE
    RT_SECFIELD_PREVCLOSE,          // Always available, RTFIELD_FLOAT
    RT_SECFIELD_LASTCHGTIME,
    RT_SECFIELD_BITFLAGS,
    RT_SECFIELD_EXCHANGEINDEX,
    RT_SECFIELD_TRADEEXCHANGE,      // retired - used by TS9.2 and older
    RT_SECFIELD_HIGH,
    RT_SECFIELD_LOW,
    RT_SECFIELD_OPEN,
    RT_SECFIELD_CLIENT_LOCALE_ID,   // Locale ID defining language used in result sets
    RT_SECFIELD_DESCRIPTION,        // UNICODE
    RT_SECFIELD_TOTALVOL,
    RT_SECFIELD_TRADEVOL,
    RT_SECFIELD_BIDSIZE,
    RT_SECFIELD_ASKSIZE,
    RT_SECFIELD_BIDEXCHANGE,        // retired - used by TS9.2 and older
    RT_SECFIELD_ASKEXCHANGE,        // retired - used by TS9.2 and older
    RT_SECFIELD_8UPDOWNBITPAIRS,
    RT_SECFIELD_TRADESTARTTIME,
    RT_SECFIELD_TRADEENDTIME,
    RT_SECFIELD_EODKEEPDAYS,
    RT_SECFIELD_TICKKEEPDAYS,
    RT_SECFIELD_NUMTRADES,
    RT_SECFIELD_12MONTHHIGH,
    RT_SECFIELD_12MONTHLOW,
    RT_SECFIELD_NUMNEWSITEMS,
    RT_SECFIELD_NEWSKEEPDAYS,
    RT_SECFIELD_LASTTRADE_UNDERLYING,
    RT_SECFIELD_OPEN_GAP,
    RT_SECFIELD_OPEN_GAP_PERCENT,
    RT_SECFIELD_CURRENCY,
    RT_SECFIELD_MINBAR_OPEN,        // backend only - scanner
    RT_SECFIELD_MINBAR_CLOSE,       // backend only - scanner
    RT_SECFIELD_STRIKE,
    RT_SECFIELD_MINBAR_VOLUME,      // backend only - scanner
    RT_SECFIELD_OPENINTEREST,
    RT_SECFIELD_SETTLEMENT,
    RT_SECFIELD_ROOTSYMBOL,
    RT_SECFIELD_UNDERLYINGSYMBOL,
    RT_SECFIELD_CONTRACTSIZE,
    RT_SECFIELD_OPTIONTYPE,         // recycle the ID for call put
    RT_SECFIELD_OPTLEAPYEAR,        // used to distinguish LEAP or normal option
    RT_SECFIELD_ENTITLEEXCHANGE,    // obsolete
    RT_SECFIELD_EXPIRATIONDATE,     // qdg change from YEAR to DATE
    RT_SECFIELD_NUMOPTIONS,
    RT_SECFIELD_12MOHIGHMONTH,
    RT_SECFIELD_12MOHIGHDAY,
    RT_SECFIELD_12MOLOWMONTH,
    RT_SECFIELD_12MOLOWDAY,
    RT_SECFIELD_DAYS_TO_EXPIRATION,
    RT_SECFIELD_OPTION_VALUE,
    RT_SECFIELD_ENTITLEEXCHANGE_EX,
    RT_SECFIELD_LASTASKARROW,
    RT_SECFIELD_LASTTRADETIME,
    RT_SECFIELD_DISPLAYTYPE,
    RT_SECFIELD_LASTBIDARROW,
    RT_SECFIELD_BASECODE,   // DisplayType version for TS.COM
    RT_SECFIELD_POINTVALUE, // TS.COM
    RT_SECFIELD_MINMOVE,    // TS.COM
    RT_SECFIELD_DAILY_LIMIT,// TS.COM
    RT_SECFIELD_UP_VOLUME,          //TS.com
    RT_SECFIELD_DOWN_VOLUME,        //TS.com
    RT_SECFIELD_UNCHANGED_VOLUME,   //TS.com
    RT_SECFIELD_UP_TICKS,           //TS.com
    RT_SECFIELD_DOWN_TICKS,         //TS.com
    RT_SECFIELD_UNCHANGED_TICKS,    //TS.com
    RT_SECFIELD_LASTBIDTIME,        //TS.com
    RT_SECFIELD_LASTASKTIME,        //TS.com
    RT_SECFIELD_CUSIP,              //TS.com
    RT_SECFIELD_MARGIN,             //TS.com
    RT_SECFIELD_FIRST_NOTICE_DATE,  //TS.com
    RT_SECFIELD_LAST_TRADING_DATE,  //TS.com
    RT_SECFIELD_DELIVERY_DATE,      //TS.com
    RT_SECFIELD_EXPIRATION_STYLE,   //TS.com
    RT_SECFIELD_CLOSE,
    RT_SECFIELD_PREV_OPENINTEREST,
    RT_SECFIELD_PREV_TOTALVOL,
    RT_SECFIELD_VWAP,
    RT_SECFIELD_FUTURETYPE,          // TS.com = Electronic, Pit or Combined
    RT_SECFIELD_NAME_EXT,           // retired - used by TS9.2 and older - Ticker name extension i.e. 'delayed, easy-to-borrow, etc..'
    RT_SECFIELD_BID_EX, // double support - need to add new field for backward compatibility
    RT_SECFIELD_ASK_EX, // double support - need to add new field for backward compatibility
    RT_SECFIELD_FILE_RESOLUTION,
    RT_SECFIELD_FILE_RESN_QTY,
    RT_SECFIELD_FUTVALIDMONTHS,
    RT_SECFIELD_STRIKE_MULTIPLIER,
    RT_SECFIELD_FILE_LASTAVLDATE,
    RT_SECFIELD_VENDOR_ID,
    RT_SECFIELD_LOCALE_ID,
    RT_SECFIELD_DELIVERABLE,
    RT_SECFIELD_COUNTRY_CODE,
    RT_SECFIELD_CONVERSION_FORMULAS,
    RT_SECFIELD_CONVERSION_BARS,
    RT_SECFIELD_BASE_LOCALE_ID,
    RT_SECFIELD_DELIVERABLE_QTY,
    RT_SECFIELD_CONVERSION_FACTOR,
    RT_SECFIELD_CFI,
    RT_SECFIELD_EXPIRY_TYPE,
    RT_SECFIELD_JP_INDUSTRY_CODE,
    RT_SECFIELD_JP_SECTOR_NAME, // UNICODE
    RT_SECFIELD_JP_INDUSTRY_NAME, // UNICODE
    RT_SECFIELD_JP_SECTCLASS_CODE,
    RT_SECFIELD_JP_SECTCLASS_NAME, // UNICODE
    RT_SECFIELD_JP_OPENTIME,
    RT_SECFIELD_JP_HIGHTIME,
    RT_SECFIELD_JP_LOWTIME,
    RT_SECFIELD_JP_LASTTIME,
    RT_SECFIELD_JP_MINPRICE,
    RT_SECFIELD_JP_MAXPRICE,
    RT_SECFIELD_JP_UNITOFTRADE,
    RT_SECFIELD_JP_TURNOVER,
    RT_SECFIELD_BIDTYPE,
    RT_SECFIELD_ASKTYPE,
    RT_SECFIELD_TRADETYPE,
    RT_SECFIELD_JP_EX_RIGHT,
    RT_SECFIELD_NAME_EXT_W,         // Ticker name extension i.e. 'delayed, easy-to-borrow, etc..'
    RT_SECFIELD_TRADE_EXCHANGE,
    RT_SECFIELD_BID_EXCHANGE,
    RT_SECFIELD_ASK_EXCHANGE,
    RT_SECFIELD_EXCHANGE_SUFFIX,
    RT_SECFIELD_JP_TICK_SIZE_TABLE,
    RT_SECFIELD_ABBREVIATION, // UNICODE
    RT_SECFIELD_SHORT_DESCRIPTION, // UNICODE
    RT_SECFIELD_ALIAS, // UNICODE
    RT_SECFIELD_HOTLIST_CRITERIA, // 128
    RT_SECFIELD_TWAP,
    RT_SECFIELD_AM_CLOSE,
    RT_SECFIELD_PM_OPEN,
    RT_SECFIELD_AM_VOLUME,
    RT_SECFIELD_AM_TRADES,
    RT_SECFIELD_AM_UP_TICKS,
    RT_SECFIELD_AM_DOWN_TICKS,
    RT_SECFIELD_AM_TURNOVER,

    RT_SECFIELD_MARKET_CAP,

    RT_SECFIELD_DYNAMIC_PE,
    RT_SECFIELD_TURNOVER_RATE,
    RT_SECFIELD_IOPV,
    RT_SECFIELD_TURNOVER,

    RT_SECFIELD_JP_EST_PRICE,
    RT_SECFIELD_JP_EST_PRICE_TYPE, // see ORGSFieldValues.h ORGS_ESTPRICE_TYPE_OPEN and ORGS_ESTPRICE_TYPE_CLOSE

    RT_SECFIELD_PRICE_LOWLIMIT,
    RT_SECFIELD_PRICE_HIGHLIMIT,

    RT_SECFIELD_CAL_SIMULATED=192,	// This is the begin of sec fields simulated by CAL/WowRT. Server don't handle them.
    RT_SECFIELD_PUT_VOLUME = 192,
    RT_SECFIELD_CALL_VOLUME,
    RT_SECFIELD_PUT_CALL_VOLUME_RATIO,
    RT_SECFIELD_PUT_OPEN_INTEREST,
    RT_SECFIELD_CALL_OPEN_INTEREST,
    RT_SECFIELD_IMPLIED_VOLATILITY,
    RT_SECFIELD_LAST_CCC_NOTIFY,
    RT_SECFIELD_LAST_AUTO_NOTIFY,
    RT_SECFIELD_MAX_VALUE = 255
};

typedef short int sec_period  ;  // qdg  16-bit Archiver comp
#define NUM_SESSIONS 4
#define ALL_SESSIONS NUM_SESSIONS

// NOTE : all times stored in timezone of the primary
//        exchange for that security
// NOTE : non-inclusive of last minute.  If this structure
//        says 9:00-16:00 this means 9:00:00-15:59:59
// NOTE : a 24-hr session is represented by sStartTime[x] == sEndTime[x]
// NOTE : Session 1 is stored in index 0, etc.

struct SESSION_INFO
{
    short      sSizeStruct;              // what is the size of this struct
    bool       bSession[NUM_SESSIONS];
    short      tradeDays[NUM_SESSIONS];  // see period.h for description
    short      sStartTime[NUM_SESSIONS]; // i.e. 0x0F1E = 15:30
    short      sEndTime[NUM_SESSIONS];   // i.e. 0x0F1E = 15:30
    short      sOpeningSession;          // which session is opening
    BYTE       chTimeZone;               // what is primary exchange of security?
    BYTE       chMinutesPast;            // filled in by client side
    bool       bIsFirstSessionSameDay;   // is session 1 considered part of tomorrow
    bool       bSingleSessionStandard;   // for internal use only
    sec_period dailyPeriod;              // consolidate tradeDays[] into one value
};

// NOTE : extended session type
#pragma message("BM: EXT_SESSIONS - Not sure why we're not using directly the ExtSessions class instead")
struct EXT_SESSION
{
private:
    char session[10240];

public:
    EXT_SESSION() { session[0]=0; }
    EXT_SESSION(const EXT_SESSION* s) { strcpy_s(session, s->c_str()); }
    const EXT_SESSION& operator=(const EXT_SESSION& s) { if (this!=&s) { strcpy_s(session, s.c_str()); } return *this; }

    const char* c_str() const { return session; }
    char * str() { return session; }

    void clear() { memset(this, 0, sizeof(this)); }
    size_t size() const { return sizeof(session); }
    size_t length() const { return strlen(session); }
    bool empty() const { return (session[0]==0); }
};

// NOTE : all times stored in timezone of the primary
//        exchange for that security
// NOTE : to mark a full holiday mark as sAffectedSession == NUM_SESSIONS
// NOTE : non-inclusive of last minute.  If this structure
//        says 9:00-16:00 this means 9:00:00-15:59:59

struct HOLIDAY_INFO
{
    short sSizeStruct;  // what is the size of this struct
    char  chMonth;          // i.e. 12
    char  chDay;            // i.e. 31
    short sYear;            // i.e. 1997
    short sAffectedSession; // 0 to 3, or ALL_SESSIONS
    // the following are ignored if sAffectedSession == ALL_SESSIONS
    // (used to mark a reduced trading session)
    // set this to -1 to mean entire session removed
    short sNewEndTime;      // i.e. 0x0F1E = 15:30
};

// use this to access the pHolidays field
// p is pointer to HOLIDAYS_INFO struct
// x is index into pHolidays
// returns a reference to a HOLIDAY_INFO struct

#define HOLIDAYS_ACCESS(p, x) ((HOLIDAY_INFO*)(&((p)->pHolidays)))[x]

#define MAX_HOLIDAYS                    400
#define MAX_HOLIDAYS_PARTNER            1024    // partner maximum holidays

#define FLAG_IS_PARTNER_HOLIDAY_DATA    0x01

//
//  Holiday Data Common Header
struct HOLIDAYS_INFO_HEADER
{
public:
    HOLIDAYS_INFO_HEADER() : chFlags(0) {}
    short         sNumHolidays;
    bool          bAreAllHolidaysFull;
    char          chFlags;      //  - set 0 for TradeStation native holiday data
                                //  - set bit FLAG_IS_PARTNER_HOLIDAY_DATA for partner holiday data
};

//
// TradeStation Native Holiday Structure
//
struct HOLIDAYS_INFO : public HOLIDAYS_INFO_HEADER
{
public:
    HOLIDAYS_INFO() : HOLIDAYS_INFO_HEADER() {}
    HOLIDAY_INFO  pHolidays[MAX_HOLIDAYS];
};

//
//  Partner Holidays Structure
//
struct HOLIDAYS_INFO_PARTNER : public HOLIDAYS_INFO_HEADER
{
public:
    HOLIDAYS_INFO_PARTNER() : HOLIDAYS_INFO_HEADER() { chFlags = FLAG_IS_PARTNER_HOLIDAY_DATA; }
    HOLIDAY_INFO  pHolidays[MAX_HOLIDAYS_PARTNER];
};

// Symbol lookup types
enum {
    SYMBOL_LIST_OPTION, SYMBOL_LIST_RANK, SYMBOL_LIST_PARTIAL, SYMBOL_LIST_EXACT_NAME, SYMBOL_LIST_EXACT_DESC,
    SYMBOL_LIST_CATEGORY, SYMBOL_LIST_INDUSTRY_GROUP, SYMBOL_LIST_GENERAL_GROUP, SYMBOL_LIST_FUNDAMENTAL_HISTORY, SYMBOL_LIST_FUNDAMENTAL_SNAPSHOT,
    SYMBOL_LIST_RESOLVE_AUTOMATABLE_CCC_SYMBOL
};

enum FieldTypeSignature
{
    FIELD_UNKNOWN       = 0,
    FIELD_ULONG         = 1,
    FIELD_LPSTR         = 2,
    FIELD_WORD          = 3,
    FIELD_SECTYPE       = 4,
    FIELD_BYTE          = 5,
    FIELD_EXCHANGE      = 6,
    FIELD_DOUBLE        = 7,
    FIELD_FLOAT         = 8,
    FIELD_LONG          = 9,
    FIELD_DWORD         = 10,
    FIELD_SHORT         = 11,
    FIELD_LPWSTR        = 13,
    FIELD_ULONGLONG     = 14,
    FIELD_DATE_TIME      = 15
};

enum LogLevels {
    critical_error = (1 << 0),
    general_error = (1 << 1),
    debug_level_1 = (1 << 2),
    debug_level_2 = (1 << 3),
    memory_error = (1 << 4),
    warning_level = (1 << 5),
    misc_level_1 = (1 << 6),
    misc_level_2 = (1 << 7),
    debug_level_3 = (1 << 10),
    debug_level_4 = (1 << 12)
};

enum QuoteCallbackDefinitions {
    Quote_Complete = 0,
    Quote_Update = 3
};


enum SecurityListCallbackDefinitions {
    SecurityList_Complete = 0,
    SecurityList_Seclist = 2
};


class RT_SECFIELD
{
public:
    enum {_RESET_FUNDAMENTALS=0x1};
    static BOOL IsStaticField(BYTE byField)
    {
        switch (byField)
        {
            case RT_SECFIELD_NAME:
            case RT_SECFIELD_CLIENT_LOCALE_ID:
            case RT_SECFIELD_DESCRIPTION:
            case RT_SECFIELD_CURRDESC:
            case RT_SECFIELD_ASSETTYPE:
            case RT_SECFIELD_PREVCLOSE:
            case RT_SECFIELD_EXCHANGEINDEX:
            case RT_SECFIELD_12MONTHHIGH:
            case RT_SECFIELD_12MONTHLOW:
            case RT_SECFIELD_SETTLEMENT:
            case RT_SECFIELD_ROOTSYMBOL:
            case RT_SECFIELD_UNDERLYINGSYMBOL:
            case RT_SECFIELD_CONTRACTSIZE:
            case RT_SECFIELD_OPTIONTYPE:
            case RT_SECFIELD_OPTLEAPYEAR:
            case RT_SECFIELD_ENTITLEEXCHANGE_EX:
            case RT_SECFIELD_EXPIRATIONDATE:
            case RT_SECFIELD_NUMOPTIONS:
            case RT_SECFIELD_STRIKE:
            case RT_SECFIELD_OPENINTEREST:
            case RT_SECFIELD_PREV_OPENINTEREST:
            case RT_SECFIELD_PREV_TOTALVOL:
            case RT_SECFIELD_DISPLAYTYPE:
            case RT_SECFIELD_BASECODE:
            case RT_SECFIELD_POINTVALUE:
            case RT_SECFIELD_DELIVERY_DATE:
            case RT_SECFIELD_EXPIRATION_STYLE:
            case RT_SECFIELD_FUTURETYPE:
            case RT_SECFIELD_DAILY_LIMIT:
            case RT_SECFIELD_NAME_EXT:
            case RT_SECFIELD_NAME_EXT_W:
            case RT_SECFIELD_STRIKE_MULTIPLIER:
            case RT_SECFIELD_LOCALE_ID:
            case RT_SECFIELD_DELIVERABLE:
            case RT_SECFIELD_COUNTRY_CODE:
            case RT_SECFIELD_CONVERSION_FORMULAS:
            case RT_SECFIELD_CONVERSION_BARS:
            case RT_SECFIELD_BASE_LOCALE_ID:
            case RT_SECFIELD_CONVERSION_FACTOR:
            case RT_SECFIELD_CFI:
            case RT_SECFIELD_EXPIRY_TYPE:
            case RT_SECFIELD_CURRENCY:
            case RT_SECFIELD_JP_INDUSTRY_CODE:
            case RT_SECFIELD_JP_SECTOR_NAME:
            case RT_SECFIELD_JP_INDUSTRY_NAME:
            case RT_SECFIELD_JP_SECTCLASS_CODE:
            case RT_SECFIELD_JP_SECTCLASS_NAME:
            case RT_SECFIELD_JP_EX_RIGHT:
            case RT_SECFIELD_EXCHANGE_SUFFIX:
            case RT_SECFIELD_ABBREVIATION:
            case RT_SECFIELD_SHORT_DESCRIPTION:
            case RT_SECFIELD_ALIAS:
                return TRUE;
        }
        return FALSE;
    }

    static BOOL IsLocaleDependant(BYTE byField)
    {
        switch (byField)
        {
            case RT_SECFIELD_DESCRIPTION:
            case RT_SECFIELD_JP_SECTOR_NAME:
            case RT_SECFIELD_JP_INDUSTRY_NAME:
            case RT_SECFIELD_JP_SECTCLASS_NAME:
            case RT_SECFIELD_NAME_EXT_W:
            case RT_SECFIELD_ABBREVIATION:
            case RT_SECFIELD_SHORT_DESCRIPTION:
            case RT_SECFIELD_ALIAS:
                return TRUE;
        }
        return FALSE;
    }
};

// OPTION Types
enum {
    OPTION_TYPE_CALL = 1,
    OPTION_TYPE_PUT = 2
};

// TRADETYPE VALUES
class RTDEF_TRADETYPE
{
public:
    enum {
        REGULAR_SALE=0,//       0
        ACQUISITION,//          1
        DISTRIBUTION,//         2
        SPLIT,  //              3
        RESERVED_SALE,//        4
        CASH_SALE,//            5
        NEXT_DAY_SALE,//        6
        SELLER_SALE,//          7
        RULE_155,//             8
        SOLD_LAST_SALE,//       9
        OPENED_SALE,//          10
        OUT_OF_SEQ,//           11
        BUNCHED,//              12
        BUNCHED_SOLD,//         13
        FORM_T,//               14
        INTRADAY_DETAIL,//      15
        OPENING_DETAIL,//       16
        RULE_127,//             17
        AVERAGE_PRICE,//        18
        BURST_BASKET,//         19
        BASKET_INDEX_CLOSE,//   20
        CUSTOM_BASKET_CROSS,//  21
        PRIOR_REFERENCE_PRICE,//22
        UNKNOWN,//              23
        DIRECT_PLUS, //         24
        OPEN_REOPEN_TRADEDETAIL,    //25
        CASH_ONLY_MARKET, //    26
        NEXT_DAY_ONLY, //       27
        REOPEN, //              28
        MIDDAY_SETTLEMENT,  //  29
        ADJUSTED, //            30

        INVALID_TRADE=0x1F, //  31 - internal usage

        REGULAR_ITAYOSE                    = 0x20,
        REGULAR_EOD                        = 0x21,
        REGULAR_SUSPENSION                 = 0x22,
        REGULAR_SUSPENSION_DONT_RECV_ORDER = 0x23,
        REGULAR_REMOVE_SUSPENSION          = 0x24,
        REGULAR_INTERRUPTION               = 0x25,
        REGULAR_REMOVE_INTERRUPTION        = 0x26,
        REGULAR_IN_SYSTEM_FAILURE          = 0x27,

        SPREAD = 50,                 // 50
        STRADDLE,                    // 51
        STOPPED,                     // 52
        LATE_OPEN,                   // 53
        OPEN_PRICE,                  // 54
        CLOSE_PRICE,                 // 55
        ODDLOT,                      // 56
        CROSSED,                     // 57
        LATE,                        // 58
        BUYSTOCK_SELLCALLOPTION,     // 59
        COMBO_BUYCALL_SELLPUT,       // 60
        OPENING,                     // 61
        VARIABLE,                    // 62
        FIXING,                      // 63
        CLOSING,                     // 64
        EXCHANGE_TRADE,              // 65
        MARKET_TRADE_CROSSING,       // 66
        OTC_TRADE,                   // 67
        BEST_VAL_PRICE_WO_TURNOVER,  // 68
        XETRA_BEST_TRADE,            // 69
        BLOCK_CROSSING_TRADE,        // 70
        OTC_BASIS,                   // 71
        OTC_BLOCK,                   // 72
        EXCHANGE_FOR_PHYSICAL,       // 73
        OTC_VOLA,                    // 74
        EFP_BASIS,                   // 75
        DNTP,                        // 76
        EFS_BASIS,                   // 77
        INTERMARKET_SWEEP,           // 78
        DERIVATIVELY_PRICED,         // 79
        REOPENING_PRINTS,            // 80
        CLOSING_PRINTS,              // 81
        PRICE_VARIATION,             // 82
        MARKETCENTER_OFFICIAL_CLOSE, // 83
        MARKETCENTER_OFFICIAL_OPEN,  // 84
        CROSS_TRADE,                 // 85
        BLOCK_TRADE,                 // 86
        EFP_BLOCK_TRADE,             // 87
        EFS_BLOCK_TRADE,             // 88
        BILAT_BLOCK_TRADE,           // 89
        CROSS_CONTRA_BLOCK_TRADE,    // 90
        EFPEFS_CONTRA_BLOCK_TRADE,   // 91
        NG_EFPEFS_BLOCK_TRADE,       // 92
        CONTRA_BLOCK_TRADE,          // 93
        CCX_EFP_TRADE,               // 94
        STOCKOPTION_TRADE,           // 95
        EXPIT_TRADE,                 // 96
        UNDER_INVESTIGATION,         // 97
        BENCHMARK_TRADE,             // 98
        SPIM,                        // 99
        BASIS_TRADE,                 // 100
        PROFESSIONAL_TRADE,          // 101
        AGAINST_ACTUAL_TRADE,        // 102
        ASSET_ALLOCATION_TRADE,      // 103
        EXTERNAL_MATCH_TRADE,        // 104
        TRADE_THROUGH_EXEMPT,        // 105
        EFR_TRADE,                   // 106
        EOO_TRADE,                   // 107

        DOWNTICK=0x80
    };

    static BOOL IsUpTick(DWORD x)
    {
        return !IsDownTick(x);
    }

    static BOOL IsDownTick(DWORD x)
    {
        return ((x & DOWNTICK) > 0);
    }

    static DWORD GetTradeFlag(DWORD x)
    {
        return ( (DWORD) (x & (0x7F) ) );
    }

    static BOOL IsOutOfSequence(DWORD x)
    {
        switch (GetTradeFlag(x)) {
            case BUNCHED_SOLD:
            case RULE_127:
            case OUT_OF_SEQ:
            case SELLER_SALE:
            case INTRADAY_DETAIL:
            case OPENING_DETAIL:
            case CASH_SALE:
            case NEXT_DAY_SALE:
            case PRIOR_REFERENCE_PRICE:
            case AVERAGE_PRICE:
            case BASKET_INDEX_CLOSE:
            case OPEN_REOPEN_TRADEDETAIL:
            case MIDDAY_SETTLEMENT:
            case OTC_BASIS:
            case OTC_BLOCK:
            case EXCHANGE_FOR_PHYSICAL:
            case OTC_VOLA:
            case EFP_BASIS:
            case DNTP:
            case EFS_BASIS:
            case DERIVATIVELY_PRICED:
            case PRICE_VARIATION:
            case MARKETCENTER_OFFICIAL_CLOSE:
            case MARKETCENTER_OFFICIAL_OPEN:
            case BASIS_TRADE:
            case PROFESSIONAL_TRADE:
            case AGAINST_ACTUAL_TRADE:
            case ASSET_ALLOCATION_TRADE:
            case EXTERNAL_MATCH_TRADE:
            case UNKNOWN:
                return TRUE;
        }
        return FALSE;
    }

    static BOOL IsInvalid(DWORD x) { return (GetTradeFlag(x) == INVALID_TRADE); }

    static BOOL IsRegularTrade(DWORD x)
    {
        return !IsInvalid(x) && !IsOutOfSequence(x);
    }

    template<typename T> static BOOL IsEndMinuteTick(T tPrice)
    {
        return (tPrice == FLT_MAX);
    }
    template<typename T> static BOOL IsEndSecondTick(T tPrice)
    {
        return (tPrice == FLT_ALMOST_MAX);
    }
};

#define BIDASK_FLAG 0x80

//
//  Symbol List Field Definitions
//
enum COL_LIST_CATEGORY_TABLES
{
    SLIST_CATEGORY_TICKER_COL_ID = 3,
    SLIST_CATEGORY_DESCRIPTION_COL_ID = 4,
    SLIST_CATEGORY_EXCHANGE_COL_ID  = 7,

    SLIST_CATEGORY_NAME_COL_ID      = 5001,
    SLIST_CATEGORY_ID_COL_ID,
    SLIST_CATEGORY_SUB_NAME_COL_ID,
    SLIST_CATEGORY_SUB_ID_COL_ID,
    SLIST_CATEGORY_TYPE_NAME_COL_ID,
    SLIST_CATEGORY_TYPE_ID_COL_ID,
    SLIST_CATEGORY_ROOT_COL_ID,
    SLIST_CATEGORY_ROOT_NAME_COL_ID,
    SLIST_CATEGORY_DISPLAY_COL_ID,
    SLIST_CATEGORY_CRITERIA_ID,
    SLIST_CATEGORY_BASECODE_ID
};

#define SYMLISTS_SIZE_SYMBOL            31  // ORGS_SIZE_SYMBOL
#define SYMLISTS_SIZE_DESCRIPTION       81  // ORGS_SIZE_DESCRIPTION

//
//  Symbol List Interface Support
//
#define SYMLISTS_CATEGORIES             (1 << 2)
#define SYMLISTS_LIST                   (1 << 4)
#define SYMLISTS_SCANNING_CATEGORIES    (1 << 5)
#define SYMLISTS_HOTLISTS_CATEGORIES    (1 << 6)
#define SYMLISTS_BYNAME                 (1 << 13)
#define SYMLISTS_UNICODE_RESULTS        (1 << 30)
#define SYMLISTS_ADDWEIGHT              (1 << 31)

//
// Subheader of a sub-list section, in a response
//
struct SYMLISTS_ACK_SUBHEADER {
    BYTE bySize;
    BYTE byFieldType;
    WORD wFieldID;
};

// Bit Flag values
#define WOWRTFLAG_DELETED             0x0001
#define WOWRTFLAG_SETTLEMENT          0x0002
#define WOWRTFLAG_REPLAY_MODE         0x0004
#define WOWRTFLAG_OVERRIDEKEEPDAYS    0x0008
#define WOWRTFLAG_OVERRIDETRADEHOURS  0x0010
#define WOWRTFLAG_DELAYED             0x0020
#define WOWRTFLAG_UPTICK              0x0040
#define WOWRTFLAG_DOWNTICK            0x0080
#define WOWRTFLAG_MORNING_SETTLE      0x0100
#define WOWRTFLAG_PREFERRED_EXCHANGE  0x0200
#define WOWRTFLAG_MINI_OPTION         0x0400
#define WOWRTFLAG_FREE                0x0800
#define WOWRTFLAG_CORPACTION_TODAY    0x1000

// Security List flags
#define WOWRT_SECLIST_FILTERNODESC          0x00000001
#define WOWRT_SECLIST_INCLUDE_EXPIRED       0x00000002
#define WOWRT_SECLIST_FILTER_NOT_OPTIONABLE 0x00000004
#define WOWRT_SECLIST_INCLUDE_NOT_TRADING   0x00000008
// 0x00000010 is available as it has not been used since 2010 and possibly ever before that
#define WOWRT_SECLIST_EXACT_ROOT            0x00000020
#define WOWRT_SECLIST_FILTER_DAILY_FUTURE   0x00000040
#define WOWRT_SECLIST_LIMITTO_DAILY_FUTURE  0x00000080
#define WOWRT_SECLIST_INCLUDE_A_M_SYMBOLS   0x00000100

//
//  Security Category Definitions
//
enum SecurityCategory
{
    SECURITY_CATEGORY_FUTURE            = 0,
    SECURITY_CATEGORY_FUTUREOPTION      = 1,
    SECURITY_CATEGORY_STOCK             = 2,
    SECURITY_CATEGORY_STOCKOPTION       = 3,
    SECURITY_CATEGORY_INDEX             = 4,
    SECURITY_CATEGORY_CURROPTION        = 5,
    SECURITY_CATEGORY_MUTUALFUND        = 6,
    SECURITY_CATEGORY_MONEYMKTFUND      = 7,
    SECURITY_CATEGORY_INDEXOPTION       = 8,
    SECURITY_CATEGORY_CASH              = 9,
    SECURITY_CATEGORY_BOND              = 10,
    SECURITY_CATEGORY_SPREAD            = 11,
    SECURITY_CATEGORY_FOREX             = 12,
    SECURITY_CATEGORY_CPCSYMBOL         = 13,
    SECURITY_CATEGORY_COMPOSITE         = 14,
    SECURITY_CATEGORY_FUTUREROOT        = 15,
    SECURITY_CATEGORY_FUTUREOPTIONROOT  = 16,
    SECURITY_CATEGORY_STOCKOPTIONROOT   = 17,
    SECURITY_CATEGORY_UNKNOWN           = 254,
    SECURITY_CATEGORY_ANY               = 255
};


struct SecCategoryHelper
{
    static RTSecurityType to_RTType(SecurityCategory val)
    {
        switch (val)
        {
            case SECURITY_CATEGORY_STOCK: return RTType_Stock;
            case SECURITY_CATEGORY_INDEX: return RTType_Index;
            case SECURITY_CATEGORY_FUTURE: return RTType_Future;
            case SECURITY_CATEGORY_MUTUALFUND: return RTType_MutualFund;
            case SECURITY_CATEGORY_MONEYMKTFUND: return RTType_MoneyMarket;
            case SECURITY_CATEGORY_BOND: return RTType_Bond;
            case SECURITY_CATEGORY_STOCKOPTION: return RTType_Option;
            case SECURITY_CATEGORY_FUTUREOPTION: return RTType_FutureOption;
            case SECURITY_CATEGORY_INDEXOPTION: return RTType_IndexOption;
            case SECURITY_CATEGORY_CURROPTION: return RTType_CurrencyOption;
            case SECURITY_CATEGORY_CASH: return RTType_Treasury;
            case SECURITY_CATEGORY_FUTUREROOT: return RTType_FutureRoot;
            case SECURITY_CATEGORY_FUTUREOPTIONROOT: return RTType_FutureOptionRoot;
            case SECURITY_CATEGORY_STOCKOPTIONROOT: return RTType_AssetOptionRoot;
            case SECURITY_CATEGORY_FOREX: return RTType_Forex;
            case SECURITY_CATEGORY_ANY: return RTType_AllAssets;
        }
        return RTType_UnKnown;
    }

    static SecurityCategory to_SecCategory(RTSecurityType val)
    {
        switch (val)
        {
            case RTType_Stock: return SECURITY_CATEGORY_STOCK;
            case RTType_Index: return SECURITY_CATEGORY_INDEX;

            case RTType_FutureRoot: return SECURITY_CATEGORY_FUTUREROOT;
            case RTType_Future: return SECURITY_CATEGORY_FUTURE;

            case RTType_MutualFund: return SECURITY_CATEGORY_MUTUALFUND;
            case RTType_MoneyMarket: return SECURITY_CATEGORY_MONEYMKTFUND;

            case RTType_Treasury:
            case RTType_CorpBond:
            case RTType_Bond: return SECURITY_CATEGORY_BOND;

            case RTType_Option: return SECURITY_CATEGORY_STOCKOPTION;
            case RTType_AssetOptionRoot: return SECURITY_CATEGORY_STOCKOPTIONROOT;

            case RTType_IndexOption: return SECURITY_CATEGORY_INDEXOPTION;
            case RTType_CurrencyOption: return SECURITY_CATEGORY_CURROPTION;

            case RTType_FutureOptionRoot: return SECURITY_CATEGORY_FUTUREOPTIONROOT;
            case RTType_FutureOption: return SECURITY_CATEGORY_FUTUREOPTION;

            case RTType_Forex: return SECURITY_CATEGORY_FOREX;
            case RTType_AllAssets: return SECURITY_CATEGORY_ANY;
        }
        return SECURITY_CATEGORY_UNKNOWN;
    }
};

//
//  Expiry Type
//
enum ExpiryType
{
    EXPIRY_TYPE_NA          = 0x0,
    EXPIRY_TYPE_WEEKLY      = 0x1,
    EXPIRY_TYPE_MONTHLY     = 0x2,
    EXPIRY_TYPE_QUARTERLY   = 0x3
};

//
//  Expiration Style
//
enum ExpirationStyle
{
    EXPIRATION_STYLE_AMER   = 0x01,
    EXPIRATION_STYLE_WEEKLY = 0x04
};

//
//  Trade Direction Pair Values
//
enum TradeDirectionPairValues
{
    TRADE_DIRECTION_DOWNTICK    = 0x01,
    TRADE_DIRECTION_UPTICK      = 0x02,
    TRADE_DIRECTION_NOCHANGE    = 0x03
};

//
//  HotLists Criteria Basecode
//
enum HOTLISTS_CRITERIA_BASECODE
{
    HOTLISTS_CRITERIA_DECIMAL_0 = 0,
    HOTLISTS_CRITERIA_DECIMAL_2 = 2,
    HOTLISTS_CRITERIA_DECIMAL_4 = 4,
    HOTLISTS_CRITERIA_DOLLAR    = 64,
    HOTLISTS_CRITERIA_PERCENT   = 128,
    HOTLISTS_CRITERIA_DEFAULT   = 256
};

//
//  Scanning Field Property
//
enum SCANNING_FIELD_PROPERTY
{
    SCANNING_FIELD_PROPERTY_NONE            = 0x00000000,
    SCANNING_FIELD_PROPERTY_DISPLAY_ONLY    = 0x00000001 
};

//
//  Scanning Request Modes
//
enum SCANNING_REQUESTMODE
{
    SCANNING_REQUESTMODE_UNKNOWN = 0,
    SCANNING_REQUESTMODE_SNAPSHOT = 1,
    SCANNING_REQUESTMODE_STREAMING = 2
};

#endif  // rt_defs_Director_h_included

