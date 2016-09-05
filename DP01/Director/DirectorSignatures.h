/**
DirectorSignatures.h -- Data structures, types and signatures used by the TradeStation Third-Party API
Note: TS Internal => a  comment intended for personnel internal to TradeStation and can be ignored by API users.
*/

#pragma once

#ifdef _AFXDLL
#include <afxwin.h>
#else
#include <Windows.h>
#endif

#include <string>
#include <float.h>

#include "rt_defs=Director.h"
#include "rt_strct=Director.h"
#include "rt_strct=RTPRICEREC.h"
#include "rt_strct=RTINTRADAY_PRICEREC.h"
#include "rt_strct=TICKREC.h"
#include "rt_strct=RTCCADATA.h"
#include "rt_strct=RTFUND.h"
#include "rt_strct=RTECNBOOK.h"
#include "rt_strct=RTCORRECTIONS.h"
#include "rt_strct=HistData.h"
#include "rt_strct=RTGlobalNews.h"
#include "rt_strct=Session.h"
#include "rt_strct=Scanning.h"

#include <memory.h>  // need memset
#include <map>
#include <vector>

#pragma warning (push)
#pragma warning (disable : 4005)
#include <Boost/variant.hpp>
#include <Boost/utility/enable_if.hpp>
#pragma warning (pop)

// 
//  TradeStation API SDK Versions
//
//  **   1. If the new API SDK is backward compatible, the major version should remain unchanged.
//          Otherwise API SDK major version number should be increased by 1. 
//       2. API SDK minor version number should be updated to new API SDK release version number.
//
//  SDK API Version Summary
//      - Major 1 / Minor 10
//          SDK API version validation deployed
//      - Major 1 / Minor 11 (04/2016)
//          Extended Session String
//          Extended Bar Request
//
enum TradeStationApiSdkVersion {
    //
    //  Base version where SDK API version validation deployed
    //
    TS_APISDK_MAJOR_VERSION_BASE    = 1,
    TS_APISDK_MINOR_VERSION_BASE    = 10,

    //
    //  Current SDK API version 
    //
    TS_APISDK_MAJOR_VERSION         = 1,
    TS_APISDK_MINOR_VERSION         = 12
};


//
// Message Field Tag Definition
//
struct DirectorTags {

    struct connection_uuid {
        unsigned long app_id_;
        unsigned long id_;
        unsigned long type_;

        connection_uuid() : app_id_(0), id_(0), type_(0) {}
        connection_uuid(unsigned long app_id, unsigned long id, unsigned long type) : app_id_(app_id), id_(id), type_(type) {}

        // for hash maps
        typedef struct
        {
            size_t operator() (const connection_uuid &k) const { 
                return std::hash<long double >()(*reinterpret_cast<const long double*>(&k));
            }
        } connection_uuid_hash;

        typedef struct
        {
            bool operator() (const connection_uuid &x, const connection_uuid &y) const { return !memcmp(&x,&y,sizeof connection_uuid); }
        } connection_uuid_eq;
    };

    enum TagType {
        Unknown,
        Version,                    // Message version
        UserName,                   // TradeStation username
        Password,                   // TradeStation password
        AuthToken,                  // Provider's authentication token - communicated to Order Execution process
        ConnectionStatus,           // TradeStation connection status to its backend
        TS_Version,                 // TradeStation build version
        TS_LocaleId,                // TradeStation locale identifier setting (Microsoft LCID notation)

        Msg_Event,                  // Message event
        Msg_Fields,                 // Fields of interest - comma delimited integer list  
        Msg_Flags,                  // Message specific attributes
        Msg_ErrorCode,              // Message error code
        Msg_Records,                // Message - number of records
        Msg_DataSize,               // Message data size
        Msg_Data,                   // Message binary data

        AttributeType,              // Attribute/Property type  [SERVER_GENERIC_INFO_TYPE_]
        AttributeName,              // Attribute/Property name of interest
        AttributeWString,           // Attribute's value 
        AttributeVString,           // Attribute's vector of values
        
        TS_ParentHWND,              // TradeStation platform container HWND

        Msg_Symbol,                 // Requested symbol
        Msg_FieldIds,               // Field ID list
        Msg_EcnList,                // Book request ECN book code list
        Msg_Aggregate,              // Book request aggregation flag
        Msg_EcnOrderLevels,         // Book request order level
        Msg_Country,                // Country Name or Country Code Name
        Msg_LocaleId,               // Locale ID
        Msg_API_Version_Major,      // TradeStation Data Provider API SDK Major Version
        Msg_API_Version_Minor,      // TradeStation Data Provider API SDK Minor Version
        Msg_HistData,               // Historical Data Configuration
        Msg_SearchCriteria,         // Unicode string search criteria
        Msg_IsKeyWord,              // Global News keyword search flag
        Msg_NewsDepth,              // Global News search depth
        Msg_StartTime,              // Search start time
        Msg_EndTime,                // Search end time
        Msg_NewsStoryId,            // Global News story identifier
        Msg_NewsStoryIds,           // Global News story identifier set
        Msg_NewsHeadline,           // Global News headline
        Msg_NewsStoryBody,          // Global News story body
        Msg_NewsFormat,             // Global News text format
        Msg_NewsProvider,           // Global News provider identifier
        Msg_NewsSource,             // Global News source
        Msg_NewsCategory,           // Global News category
        Msg_NewsTimestamp,          // Global News timestamp
        Msg_NewsLastStory,          // Global News last news flag
        Msg_TickData,               // Tick Data
        Msg_TickType,               // Tick Type
        Msg_IsHistory,              // History flag
        Msg_EodData,                // End-of-day Data
        Msg_CustomBarId,            // Custom Bar identifier
        Msg_SessionString,          // ANSI format session string
        Msg_HolidayData,            // Holiday data buffer
        Msg_Attribute_Category,     // Category
        Msg_Attribute_ListType,     // List type
        Msg_Attribute_Rules,        // Rules
        Msg_Attribute_Options,      // Options
        Msg_VectorUnicodeString,    // Vector of Unicode strings
        Msg_Attribute_Mode,         // Mode
        Msg_Attribute_Interval,     // Interval


        Msg_provider_id = 100,      // Provider ID (ngcal)
        Msg_login_type,             // Login type (live trader, simulator, ...)
        Msg_time,                   // __time32_t timestamp attribute
        Msg_note,                   // Message details / error specifications
        Msg_connection_uuid,        // Message callback identifier <connection_id, type_id>
        Msg_transaction_id,         // Message callback identifier 
        Msg_error_code,             // Message details / error code
        Msg_unit_test_code,         // Internal unit test code
        Msg_sequence_code,          // Internal sequence code

        Msg_asset_type = 200,       // Asset type / quote requests
        Msg_periodic,               // Advise transaction
    };

    template <int> struct TagValueType { typedef void value_type; };
    template <> struct TagValueType <Version> { typedef int value_type; };
    template <> struct TagValueType <UserName> { typedef std::wstring value_type; };                        // 32 characters
    template <> struct TagValueType <Password> { typedef std::wstring value_type; };                        // 48 characters
    template <> struct TagValueType <AuthToken> { typedef std::string value_type; };                        // 4096 characters
    template <> struct TagValueType <ConnectionStatus> { typedef int value_type; };
    template <> struct TagValueType <TS_Version> { typedef std::wstring value_type; };                      // 64 characters
    template <> struct TagValueType <TS_ParentHWND> { typedef int value_type; };

    template <> struct TagValueType <Msg_Event> { typedef int value_type; };
    template <> struct TagValueType <Msg_Fields> { typedef std::string value_type; };                       // comma-delimited numeric fields, 1024 characters
    template <> struct TagValueType <Msg_Flags> { typedef int value_type; };     
    template <> struct TagValueType <Msg_ErrorCode> { typedef CErrorCode value_type; };
    template <> struct TagValueType <Msg_Records> { typedef int value_type; };     
    template <> struct TagValueType <Msg_DataSize> { typedef int value_type; };     
    template <> struct TagValueType <Msg_Data> { typedef std::vector<unsigned char> value_type; };     
    template <> struct TagValueType <Msg_Symbol> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_FieldIds> { typedef std::vector<unsigned char> value_type; };
    template <> struct TagValueType <Msg_EcnList> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_Aggregate> { typedef bool value_type; };
    template <> struct TagValueType <Msg_EcnOrderLevels> { typedef unsigned long value_type; };
    template <> struct TagValueType <Msg_Country> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_LocaleId> { typedef unsigned long value_type; };
    template <> struct TagValueType <Msg_HistData> { typedef std::vector<unsigned char> value_type; };
    template <> struct TagValueType <Msg_SearchCriteria> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_IsKeyWord> { typedef bool value_type; };
    template <> struct TagValueType <Msg_NewsDepth> { typedef int value_type; };
    template <> struct TagValueType <Msg_StartTime> { typedef unsigned long value_type; };
    template <> struct TagValueType <Msg_EndTime> { typedef unsigned long value_type; };
    template <> struct TagValueType <Msg_NewsStoryId> { typedef unsigned long long value_type; };
    template <> struct TagValueType <Msg_NewsHeadline> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_NewsStoryBody> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_NewsFormat> { typedef int value_type; };
    template <> struct TagValueType <Msg_NewsProvider> { typedef int value_type; };
    template <> struct TagValueType <Msg_NewsSource> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_NewsCategory> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_NewsTimestamp> { typedef unsigned long value_type; };
    template <> struct TagValueType <Msg_NewsLastStory> { typedef int value_type; };
    template <> struct TagValueType <Msg_NewsStoryIds> { typedef std::vector<unsigned long long> value_type; };
    template <> struct TagValueType <Msg_TickData> { typedef std::vector<unsigned char> value_type; };
    template <> struct TagValueType <Msg_TickType> { typedef int value_type; };
    template <> struct TagValueType <Msg_IsHistory> { typedef int value_type; };
    template <> struct TagValueType <Msg_EodData> { typedef std::vector<unsigned char> value_type; };
    template <> struct TagValueType <Msg_CustomBarId> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_SessionString> { typedef std::string value_type; };
    template <> struct TagValueType <Msg_HolidayData> { typedef std::vector<unsigned char> value_type; };
    template <> struct TagValueType <Msg_VectorUnicodeString> { typedef std::vector<std::wstring> value_type; };

    template <> struct TagValueType <AttributeType> { typedef int value_type; };
    template <> struct TagValueType <AttributeName> { typedef std::wstring value_type; };                   // 256 characters
    template <> struct TagValueType <AttributeWString> { typedef std::wstring value_type; };                // 256 characters
    template <> struct TagValueType <AttributeVString> { typedef std::vector<std::string> value_type; };    // 256 characters

    template <> struct TagValueType <Msg_provider_id> { typedef int value_type; };
    template <> struct TagValueType <Msg_login_type> { typedef int value_type; };
    template <> struct TagValueType <Msg_time> { typedef int value_type; };
    template <> struct TagValueType <Msg_note> { typedef std::wstring value_type; };                        // 256 characters
    template <> struct TagValueType <Msg_connection_uuid> { typedef connection_uuid value_type; };
    template <> struct TagValueType <Msg_transaction_id> { typedef unsigned long value_type; };
    template <> struct TagValueType <Msg_asset_type> { typedef int value_type; };
    template <> struct TagValueType <Msg_periodic> { typedef bool value_type; };
    template <> struct TagValueType <Msg_error_code> { typedef int value_type; };
    template <> struct TagValueType <Msg_unit_test_code> { typedef int value_type; };
    template <> struct TagValueType <Msg_sequence_code> { typedef int value_type; };

    template <> struct TagValueType <Msg_Attribute_Category> { typedef unsigned long value_type; };
    template <> struct TagValueType <Msg_Attribute_ListType> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_Attribute_Rules> { typedef std::wstring value_type; };
    template <> struct TagValueType <Msg_Attribute_Options> { typedef unsigned long value_type; };
    template <> struct TagValueType <Msg_Attribute_Mode> { typedef unsigned long value_type; };
    template <> struct TagValueType <Msg_Attribute_Interval> { typedef unsigned long value_type; };
};


struct DirectorStatus {
    enum State {
        Unknown, 
        Shutdown,
        Offline,
        Online,
        Reset,

        OnlinePending,  // internal usage
        OfflinePending  // internal usage
    };

    static const char* Name(State s) {
        switch (s) {
        case Shutdown: return "Shutdown";
        case Offline: return "Offline";
        case Online: return "Online";
        case Reset: return "Reset";
        }
        return "Unknown";
    }
};


struct DirectorMessages {

    //
    // Message Type Definition
    //
    enum MessageId {
        Msg_Unknown,
        Msg_Connect,
        Msg_ConnectionStatus,
        Msg_TS_Version,
        Msg_TS_LocaleId,
        Msg_FundamentalInfo,
        Msg_Fundamental,
        Msg_EcnBookCodeInfo,
        Msg_ReqMarketMakers,
        Msg_ReqSymbolList,
        Msg_ReqHotList,
        Msg_ReqHist,
        Msg_ReqGlobalNewsProviders,
        Msg_ReqGlobalNewsHeadlines,
        Msg_ReqGlobalNewsStories,
        Msg_ReqArchiveHistory,
        Msg_ReqBars,
        Msg_ReqDailyBars,
        Msg_ReqSession,
        Msg_ReqChartInfo,
        Msg_ReqScanningInfo,
        Msg_ReqScanning,

        // ngCal
        Msg_QuoteGet = (1 << 10),
        Msg_NoLatency,
        Msg_Sequence,
        Msg_Release,

        Msg_Synchronous_Offset=(1<<16),
        Msg_Attribute_String_Get,
        Msg_Attribute_VString_Get,
        Msg_Attribute_API_Version_Get
    };

    class MSG {
    public:
        // Version 1.1 => Added new variant types, new attributes and retrieval by reference
        // Version 2.0 => ngCal support - new attributes

        static const int Version = MAKELONG(2,0);
        MessageId MessageId_;
    private:
        typedef boost::variant< int, double, std::string, std::wstring, CErrorCode, std::vector<unsigned char>, std::vector<std::string>, 
            unsigned long, bool, DirectorTags::connection_uuid, unsigned long long, std::vector<unsigned long long>, std::vector<std::wstring> > MsgVariant;
        std::map< DirectorTags::TagType, MsgVariant > Attributes_;

    public: // constructor
        MSG() : MessageId_(Msg_Unknown) { add_attribute(DirectorTags::Version, Version); }
        MSG(MessageId id) : MessageId_(id) { add_attribute(DirectorTags::Version, Version); }
        MSG(const MSG& m) { *this = m; }
        MSG(const MSG&& m) { *this = std::move(m); }

        template <class T>
        MSG(MessageId id, DirectorTags::TagType t, const T& value) : MessageId_(id) { add_attribute(DirectorTags::Version, Version); add_attribute(t, value); }

        const MSG& operator=(const MSG& msg) { if (this!=&msg) { MessageId_ = msg.MessageId_; Attributes_ = msg.Attributes_; } return *this; }
        const MSG& operator=(MSG&& msg) { if (this!=&msg) { MessageId_ = msg.MessageId_; Attributes_ = std::move(msg.Attributes_); } return *this; }

    public:
        // Parameters handling
        void clear_attributes() { Attributes_.clear(); }
        bool has_attributes() { return !Attributes_.empty(); }

        template<class T>
        void add_attribute(DirectorTags::TagType t, const T& value) { 
            Attributes_[t] = value; 
        }

        void add_attribute(DirectorTags::TagType t, const char* value) {
            std::string s = value; Attributes_[t] = s;
        }

        void add_attribute(DirectorTags::TagType t, const wchar_t* value) {
            std::wstring s = value; Attributes_[t] = s;
        }

        void add_attribute(DirectorTags::TagType t, const std::vector<unsigned char>& value) {
            Attributes_[t] = std::move(value);
        }

        void add_attribute(DirectorTags::TagType t, const std::vector<unsigned long long>& value) {
            Attributes_[t] = std::move(value);
        }

        void add_attribute(DirectorTags::TagType t, const std::vector<std::string>& value) {
            Attributes_[t] = std::move(value);
        }

        void add_attribute(DirectorTags::TagType t, const std::vector<std::wstring>& value) {
            Attributes_[t] = std::move(value);
        }

        void add_attribute(DirectorTags::TagType t, DirectorTags::connection_uuid& value) {
            Attributes_[t] = value;
        }

        template<class T>
        typename boost::disable_if< boost::is_enum<T>, bool >::type get_attribute(DirectorTags::TagType t, T& value) const { 
            auto it = Attributes_.find(t);
            if (it==Attributes_.end()) return false;
            value = boost::get<T>(it->second);
            return true;
        }

        template<class T>
        typename boost::disable_if< boost::is_enum<T>, bool >::type get_attribute(DirectorTags::TagType t, T* & value) { 
            auto it = Attributes_.find(t);
            if (it==Attributes_.end()) return false;
            value = boost::get<T>(&it->second);
            return true;
        }

        template<class T>
        typename boost::enable_if< boost::is_enum<T>, bool >::type get_attribute(DirectorTags::TagType t, T& value) const { 
            auto it = Attributes_.find(t);
            if (it==Attributes_.end()) return false;

            int v = boost::get<int>(it->second);
            value = static_cast<T>(v);
            return true;
        }
    };
};



namespace DirectorSignatures {
    typedef BOOL (CALLBACK* CallbackBarsGet)(unsigned long, CErrorCode&, BOOL /* history or r/t? */, int /* type tick or intraday TR_INTRAPRICE */, void * /* buffer of tickrec or intraday price rec */,  unsigned long /* UserrData */);
    typedef BOOL (CALLBACK* CallbackCCAGet) (unsigned long, unsigned long, CErrorCode&, void*, unsigned long);
    typedef void (CALLBACK* CallbackConnect) (int,void*);
    typedef BOOL (CALLBACK* CallbackDailyBarsGet)(/* event */ unsigned long, CErrorCode&, BOOL /* bClosed */ , BOOL /* bHistory */,BOOL /* bUpdate */,int /* type = TR_PRICEREC */, void* /* pRecs */, unsigned long /* UserData */);
    typedef int (CALLBACK* CallbackProcessMessage)(DirectorMessages::MSG& msg);
    typedef int (CALLBACK* CallbackQuoteGet)(unsigned long, CErrorCode&, int, int, void*, void*, unsigned long);
    typedef BOOL (CALLBACK* CallbackSecurityListGet)(unsigned long, CErrorCode&, int, int, void *, void *, unsigned long);
    typedef int (CALLBACK* CallbackSessionGet)(unsigned long,CErrorCode&,const SESSION_INFO*,void*,unsigned long);
    typedef int (CALLBACK* CallbackExSessionGet)(unsigned long, CErrorCode&, const EXT_SESSION*, void*, unsigned long);
    typedef bool (CALLBACK* GlobalNewsProvidersCallback)(unsigned long, int notify, unsigned short providers, char* data, unsigned long user_data);

    typedef long (* AttributeNumericGetSignature)(unsigned long, int, int, long);
    typedef bool (* AttributeStringGetSignature)(unsigned long, int, int, std::wstring&);
    typedef unsigned long (*BarsGetSignature)(PCWSTR pSymbol, int AssetType, PTICKDATA pTickData, DirectorSignatures::CallbackBarsGet pCB, unsigned long UserData);
    typedef unsigned long (*CCAGetSignature)(PCWSTR pSymbol, unsigned long dwCorpActionNo, unsigned long dwCorrectionNo, CallbackCCAGet pCB, unsigned long dwUserData);
    typedef unsigned long (*DailyBarsGetSignature)(PCWSTR pSymbol, int AssetType, EODDATA* pData, CallbackDailyBarsGet pCB, unsigned long UserData, BOOL bPeriodic);
    typedef int (*EventReleaseSignature)(unsigned long event, bool connected);
    typedef int (* ExchangeIndexGetSignature) (PCWSTR exchangeName);
    typedef void (* ExchangesGetSignature)(std::map<unsigned short, std::wstring>& ex_map);
    typedef void (* InitializeSignature) (PCWSTR, unsigned long, DirectorSignatures::CallbackProcessMessage pCB);
    typedef int (*ProcessMessageSignature)(DirectorMessages::MSG& msg);
    typedef unsigned long (*QuoteGetSignature)(PCWSTR pSymbol, int AssetType, unsigned char* pFields, LCID locale_id, CallbackQuoteGet pCB, unsigned long UserData, bool bPeriodic);
    typedef int (*QuoteModifySignature) (unsigned long event, unsigned char* pFields, LCID locale_id);
    typedef unsigned long (*SecurityListGetSignature)(PCWSTR pSymbol,int AssetType, PBYTE pFields, RTSec_OptionFilter* pFilter, CallbackSecurityListGet pCB, unsigned long UserData, unsigned char currency, short ExchID, LCID locale_id, int flags);
    typedef unsigned long (*SessionGetSignature)(PCWSTR pSymbol, int AssetType, CallbackSessionGet pCB, unsigned long UserData);
    typedef void (* UninitializeSignature)(int);
};

