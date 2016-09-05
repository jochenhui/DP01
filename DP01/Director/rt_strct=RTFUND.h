#pragma once
#include <atlbase.h>
#include <atlstr.h>
#include <atlconv.h>
#include <vector>
#include <memory>

// Note: The fundamental record is of varying length - thus we use a dummy record 4-bytes place holder for cache storage
struct FUNDAMENTAL_RECORD_BASE {
    long buffer_value;

    // base record type traits
    unsigned long GetDate() const {return 0;}
    void SetDate(unsigned long /*dt*/) {}
    bool IsEndMinuteTick() const { return false; }
    bool IsEndSecondTick() const { return false; }
    bool IsEndNettingTick() const { return false; }
    bool IsEndTick() const { return false; }
};


static char * monthnameabbr[12]=
{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };


struct FundamentalInfoEx {
    static const unsigned short provider_id_offset = 0x8000; // minimal offset for external provider-specific fundamentals
    static const unsigned short struct_version = 2;

    static const unsigned long lcid_english = 0x0409;  // MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),SORT_DEFAULT)
    static const unsigned long lcid_japanese = 0x0411; // MAKELCID(MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN), SORT_DEFAULT)

    static const unsigned short country_US = 0x5355; // "US"
    static const unsigned short country_JP = 0x504a; // "JP"

    unsigned short  version;    // structure version
    unsigned short  size;       // structure size
    unsigned short  id;         // fundamental field identifier
    unsigned short  type;       // type (FundamentalInfo::Numeric, Char, Date, ...)

    unsigned long   locale_id;

    unsigned short  country_code; // 2-letter ISO country code
    unsigned short  attributes; // Attributes category (Fundamental::_flags [Results] => Term, Consolidated, Standard,  [CapitalTransfer] =>  OrderOfRights, TieInClassification ...)

    char            base_name[64];          //English
    char            base_description[128];  //English
    char            base_group[64];         //English

    FundamentalInfoEx() { memset(this, 0, sizeof(FundamentalInfoEx)); version = struct_version; size = sizeof(FundamentalInfoEx); locale_id = lcid_english; country_code = country_US; }
};

struct FundamentalInfoLocale : public FundamentalInfoEx {
    // This structure should only be used as an extension to FundamentalInfoEx, when locale_id != lcid_english(1033)
    wchar_t         name[64];
    wchar_t         description[128];
    wchar_t         group[64];

    FundamentalInfoLocale() { memset(this, 0, sizeof(FundamentalInfoLocale)); version = FundamentalInfoEx::struct_version; size = sizeof(FundamentalInfoLocale); }

    FundamentalInfoLocale(unsigned short country, unsigned short id, unsigned short type, unsigned short attributes, const char * name, const char * desc, const char * group=nullptr) {
        strncpy_s(base_name, name, _TRUNCATE);
        strncpy_s(base_description, desc, _TRUNCATE);
        if (group) strncpy_s(base_group, group, _TRUNCATE);
        else memset(base_group, 0, sizeof(base_group));

        wcsncpy_s(this->name, CA2W(name), _TRUNCATE);
        wcsncpy_s(description, CA2W(desc), _TRUNCATE);
        if (group) wcsncpy_s(this->group, CA2W(group), _TRUNCATE);
        else memset(this->group, 0, sizeof(this->group));

        country_code=country; this->id=id; this->type=type; this->attributes = attributes; size = sizeof(FundamentalInfoLocale);
    }
};

struct FundamentalInfo {
    enum {UNKNOWN, NUMERIC=0x1, CHAR=0x2, DATE=0x4, NMF=0x8, NA=0x10, _COMMITMENTS=0x20, _SUPPORTS_SCANNING=0x40, _SUPPORTS_HIST=0x80, _MILLIONS=0x100, WCHAR=0x200}; // 2 bytes

    unsigned short  _id;
    unsigned short  _type;
    char            _name[32];
    char            _desc[80];

    FundamentalInfo(unsigned short id, unsigned short type, char * name, char * desc) : _id(id), _type(type) {
        strncpy_s(_name, _countof(_name), name, _TRUNCATE);
        strncpy_s(_desc, _countof(_desc), desc, _TRUNCATE);
    }

    FundamentalInfo(const FundamentalInfoLocale& f) {
        _id = f.id;
        _type = f.type;
        strncpy_s(_name, _countof(_name), f.base_name, _TRUNCATE);
        strncpy_s(_desc, _countof(_desc), f.base_description, _TRUNCATE);
    }
    FundamentalInfo() {memset (this, 0, sizeof *this); }
};

// predicate for above structure ordering
struct FundamentalInfoLess : public std::binary_function<FundamentalInfo, FundamentalInfo, bool> {
    bool operator() (const FundamentalInfo& lhs, const FundamentalInfo& rhs) const
    {
        return (lhs._id < rhs._id);
    }
};

struct FundamentalInfoLocaleLess : public std::binary_function<FundamentalInfoLocale, FundamentalInfoLocale, bool> {
    bool operator() (const FundamentalInfoLocale& lhs, const FundamentalInfoLocale& rhs) const
    {
        return (lhs.id < rhs.id);
    }
};


#pragma pack(push,old_pack,1)


template <typename T> struct my_stream_iterator {
    T * _p;
    my_stream_iterator (T*p) : _p(p) {}
    my_stream_iterator& operator=(T*p) { _p=p; return (*this); }
    my_stream_iterator& operator=(const my_stream_iterator& it) { _p=it._p; return (*this); }

    my_stream_iterator& operator++() { _p = reinterpret_cast<T*>(reinterpret_cast<char*>(_p) + _p->_size); return (*this);}
    my_stream_iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
    T* operator->() { return _p; }
    const unsigned char* begin() { return ((unsigned char*)(_p)); }
    const unsigned char* end() { return ((unsigned char*)(_p) + _p->_size); }
};

typedef std::vector<unsigned char> FundamentalStg;    // binary storage for dynamic fundamental structure

struct Fundamental  { // ACKFUNDAMENTAL::_VERSION (3)
    typedef my_stream_iterator<Fundamental> iterator;
    static const double not_threshold() { return -99999; }
    static const double not_available() { return -99999.99; }
    static const double not_meaningful() { return -99999.98; }
    static const char* not_available_s() { return "-99999.99"; }
    static const char* not_meaningful_s() { return "-99999.98"; }

    static inline int CmpDbl( double d1, double d2) {
        double epsilon = fabs( ldexp(d2, -50));
        if (d1<d2-epsilon) return -1;
        if (d1>d2+epsilon) return 1;
        return 0;
    }

    struct db_TIMESTAMP { short year; unsigned short month; unsigned short day; unsigned short hour; unsigned short minute; unsigned short second; unsigned long fraction; };

    // internal structures & definitions
    struct ymd {
        unsigned char _day; unsigned char _month; unsigned short _year;

        ymd() : _day(0), _month(0), _year(0) {}
        ymd(unsigned char m, unsigned char d, unsigned short y) : _day(d), _month(m), _year(y) {}
        bool operator==(const ymd& rh) { return ((_day==rh._day) && (_month==rh._month) && (_year==rh._year)); }
        bool operator>(const ymd& rh) { return ((_year>rh._year) || ( (_year==rh._year) && ( (_month>rh._month) || ((_month==rh._month) && (_day>rh._day))))); }
        ymd& operator=(const ymd& rh) { _year=rh._year; _month=rh._month; _day = rh._day; return *this; }
    };

    struct hms {
        unsigned char _hour; unsigned char _min; unsigned char _sec; unsigned char _unused;

        hms() : _hour(0), _min(0), _sec(0), _unused(0) {}
        hms(unsigned char h, unsigned char m, unsigned char s) : _hour(h), _min(m), _sec(s), _unused(0) {}
        bool operator==(const hms& rh) { return ((_hour==rh._hour) && (_min==rh._min) && (_sec==rh._sec)); }
        bool operator>(const hms& rh) { return ((_hour>rh._hour) || ( (_hour==rh._hour) && ( (_min>rh._min) || ((_min==rh._min) && (_sec>rh._sec))))); }
        hms& operator=(const hms& rh) { _hour=rh._hour; _min=rh._min; _sec=rh._sec; return *this; }
    };

    struct FundamentalNum   { double _val; };
    struct FundamentalChar  { char _val[512]; };
    struct FundamentalWChar { wchar_t _val[256]; };
    struct FundamentalDate  {
        struct f_d {
            ymd _d;
            hms _t;
            f_d() : _d(ymd()), _t(hms()) {}
        } _val;

        bool operator==(const FundamentalDate& rh) {
            return ((_val._d == rh._val._d) && (_val._t == rh._val._t));
        }
        bool operator>(const FundamentalDate& rh) {
            return ((_val._d > rh._val._d) || ((_val._d == rh._val._d) &&  (_val._t > rh._val._t)));
        }
        FundamentalDate& operator=(const FundamentalDate& rh) {
            _val._d = rh._val._d; _val._t = rh._val._t; return *this;
        }
    };

    // attributes declarations
    struct Results {
        unsigned char   n_months;

        enum { undefined=0, full_year_settlement=1, mid_term_settlement=2, quarterly_settlement=3 };
        unsigned char   settlement_type;

        enum { Japanese=1, SEC=2, IFRS=3 };
        unsigned char   accounting_standard;

        enum { consolidated=1, non_consolidated=2 };
        unsigned char   consolidated_value;
    };

    struct Capital {
        unsigned char order_of_rights; // "0" to "9"
        unsigned char tie_in_classification; // "0" to "9"
    };

    //////////////////////////////////////////////////////
    // DATA storage => MUST BE 4-bytes aligned ..
    // *** We must never reduce the size of this structure,
    // as it would break backward compatibility ***
    //
    unsigned long   _size;

    enum { struct_version=3 };
    unsigned long   version; // structure version
    unsigned long   data_offset; // offset position for FundamentalNum/Char/WChar/Date...

    ymd      	    _period_date; // quarterly period
    ymd             _date; // announcement date
    ymd             record_date;

    // based on - _flags - attributes category
    union { // 4 bytes
        Results results;
        Capital capital;
        unsigned long value;
    } attributes;

    unsigned short 	_id;  	 // field ID
    unsigned short 	_type; 	 // value type - Numeric, Character or Date

    enum {
        // first byte - attributes category
        attributes_results=0x1, attributes_capital,
        // second byte - reserved flags
        _RESTATED=0x100, _NEW_UPDATE=0x200
    };
    unsigned long   _flags;

    FundamentalNum  _data; // place-holder for dynamic data

public:
    // Methods
    Fundamental() : _type(FundamentalInfo::UNKNOWN), _id(0), _flags(0), version(struct_version) { _size = GetSize(); data_offset = offsetof(Fundamental, _data); attributes.value=0; }
    void reset() { memset(this, 0, sizeof(*this)); _type=FundamentalInfo::UNKNOWN; _size = GetSize(); version=struct_version; data_offset = offsetof(Fundamental, _data); }
    bool valid() const { return (_type!=FundamentalInfo::UNKNOWN); }
    unsigned long get_attributes_type() const { return (_flags&0xFF); }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // WARNING: USE WITH EXTREME CAUTION - only with identical Fundamental object (i.e. num, char or dates)
    //                                     and within already allocated memory storage!!
    Fundamental(const Fundamental& f) {copy(f);}
    Fundamental& operator=(const Fundamental& f) {copy(f); return (*this);}
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<Fundamental> CopyFundamental () {
        std::shared_ptr<Fundamental> ptr ( reinterpret_cast<Fundamental*>(new unsigned char[_size]) );
        Fundamental * pFund = ptr.get(); pFund->copy(*this);
        return ptr;
    }

    bool operator==(const Fundamental& rhs) {
        if (_size != rhs._size) return false;
        if (_id != rhs._id) return false;
        if (!(_period_date == rhs._period_date)) return false;
        if (!(_date == rhs._date)) return false;
        if (getType(_type) != getType(rhs._type)) return false;
        unsigned long data_size = GetSize() - (sizeof(Fundamental) - sizeof(FundamentalNum));
        return (memcmp(&_data, &rhs._data, data_size) == 0);
    }


    // compatible with future versions - as it uses offset position for _data
    bool GetValue(double & val) const {
        switch (getType(_type)) {
            case FundamentalInfo::NUMERIC:
            case FundamentalInfo::NMF:
            case FundamentalInfo::NA:
                val = reinterpret_cast<const FundamentalNum*>(reinterpret_cast<const unsigned char*>(this)+data_offset)->_val;
                return true;
        }
        return false;
    }

    bool GetValue(std::string & val) const {
        if (getType(_type) != FundamentalInfo::CHAR) return false;
        const FundamentalChar * ptr = reinterpret_cast<const FundamentalChar*>(reinterpret_cast<const unsigned char*>(this)+data_offset);
        val = ptr->_val;
        return true;
    }

    bool GetValue(char* val, size_t len) const {
        if (getType(_type) != FundamentalInfo::CHAR) return false;
        const FundamentalChar * ptr = reinterpret_cast<const FundamentalChar*>(reinterpret_cast<const unsigned char*>(this)+data_offset);
        strcpy_s(val, len, ptr->_val);
        return true;
    }

    bool GetValue(FundamentalDate & val) const {
        if (getType(_type) != FundamentalInfo::DATE) return false;
        const FundamentalDate * ptr = reinterpret_cast<const FundamentalDate*>(reinterpret_cast<const unsigned char*>(this)+data_offset);
        val._val = ptr->_val;
        return true;
    }

    bool GetValue(std::wstring & val) const {
        if (getType(_type) != FundamentalInfo::WCHAR) return false;
        const FundamentalWChar * ptr = reinterpret_cast<const FundamentalWChar*>(reinterpret_cast<const unsigned char*>(this)+data_offset);
        val = ptr->_val;
        return true;
    }

    bool GetValue(wchar_t* val, size_t len) const {
        if (getType(_type) != FundamentalInfo::WCHAR) return false;
        const FundamentalWChar * ptr = reinterpret_cast<const FundamentalWChar*>(reinterpret_cast<const unsigned char*>(this)+data_offset);
        wcsncpy_s(val, len, ptr->_val, _TRUNCATE);
        return true;
    }


    bool SetValue(const Fundamental* pfund) {
        copy(*pfund); return true;
    }

    bool SetValue(const double& val) {
        _data._val = val; _type = FundamentalInfo::NUMERIC;
        validate_numeric_value();
        _size=GetSize(); return true;
    }

    bool SetValue(const FundamentalDate::f_d& d) {
        _type = FundamentalInfo::DATE;
        FundamentalDate * ptr = reinterpret_cast<FundamentalDate*>(&_data);
        ptr->_val = d;
        return true;
    }

    bool SetValue(const char * val) {
        if (_type == FundamentalInfo::UNKNOWN) _type = FundamentalInfo::CHAR;

        switch (getType(_type)) {
            case FundamentalInfo::NUMERIC:
            case FundamentalInfo::NMF:
            case FundamentalInfo::NA:
                _data._val = atof(val);
                validate_numeric_value();
                break;

            case FundamentalInfo::WCHAR: {
                FundamentalWChar * ptr = reinterpret_cast<FundamentalWChar*>(&_data);
                wcsncpy_s(ptr->_val, _countof(ptr->_val), ATL::CA2WEX<_countof(ptr->_val)>(val), _TRUNCATE);
                break; }

            case FundamentalInfo::CHAR: {
                FundamentalChar * ptr = reinterpret_cast<FundamentalChar*>(&_data);
                strncpy_s(ptr->_val, _countof(ptr->_val), val, _TRUNCATE);
                break; }

            case FundamentalInfo::DATE:
                validate_date_value(val);
                break;
        }
        _size = GetSize();
        return true;
    }

    bool SetValue(const wchar_t * val) {
        if (_type == FundamentalInfo::UNKNOWN) _type = FundamentalInfo::WCHAR;

        switch (getType(_type)) {
            case FundamentalInfo::NUMERIC:
            case FundamentalInfo::NMF:
            case FundamentalInfo::NA:
                _data._val = _wtof(val);
                validate_numeric_value();
                break;

            case FundamentalInfo::CHAR: {
                FundamentalChar * ptr = reinterpret_cast<FundamentalChar*>(&_data);
                strncpy_s(ptr->_val, _countof(ptr->_val), ATL::CW2AEX<_countof(ptr->_val)>(val), _TRUNCATE);
                break; }

            case FundamentalInfo::WCHAR: {
                FundamentalWChar * ptr = reinterpret_cast<FundamentalWChar*>(&_data);
                wcsncpy_s(ptr->_val, _countof(ptr->_val), val, _TRUNCATE);
                break; }

            case FundamentalInfo::DATE: {
                validate_date_value(ATL::CW2A(val));
            }
            break;
        }
        _size = GetSize();
        return true;
    }

    unsigned short getType() { return getType(_type); }
    static unsigned short getType(unsigned short type) {
        if (type & FundamentalInfo::NMF) return FundamentalInfo::NMF;
        if (type & FundamentalInfo::NA) return FundamentalInfo::NA;
        if (type & FundamentalInfo::NUMERIC) return FundamentalInfo::NUMERIC;
        if (type & FundamentalInfo::CHAR) return FundamentalInfo::CHAR;
        if (type & FundamentalInfo::DATE) return FundamentalInfo::DATE;
        if (type & FundamentalInfo::WCHAR) return FundamentalInfo::WCHAR;
        return FundamentalInfo::UNKNOWN;
    }

    bool restated() { return ((_flags&Fundamental::_RESTATED)>0); }
    bool updated(bool flip=false) {
        if (_flags & Fundamental::_NEW_UPDATE) { if (flip) _flags ^= Fundamental::_NEW_UPDATE; return true; }
        return false;
    }
    void update() { _flags |= Fundamental::_NEW_UPDATE; }

    static bool supportsHist(unsigned long flags) {
        return ((flags&FundamentalInfo::_SUPPORTS_HIST)>0);
    }
    static bool unit_in_millions(unsigned long flags) {
        return ((flags&FundamentalInfo::_MILLIONS)>0);
    }
    static bool unit_convert_millions(const std::wstring& name) {
        // only VOL1DAVG, VOL10DAVG, VOL3MAVG - lower case
        if ((name.length()>3) && (name[0]=='v') && (name[1]=='o') && (name[2]=='l'))
            return true;
        return false;
    }

    static bool compare(const Fundamental& lhs, const Fundamental& rhs) {
        if (lhs._id < rhs._id)
            return true;
        if (lhs._id == rhs._id) {
            if (lhs._period_date._year<rhs._period_date._year)
                return true;
            if (lhs._period_date._year==rhs._period_date._year){
                if (lhs._period_date._month<rhs._period_date._month)
                    return true;
                if (lhs._period_date._month==rhs._period_date._month)
                    return (lhs._period_date._day<rhs._period_date._day);
            }
        }
        return false;
    }

    unsigned long GetSize() {
        switch (getType(_type)) {
            case FundamentalInfo::CHAR:
                return sizeof(Fundamental) + (sizeof(FundamentalChar) - sizeof(FundamentalNum));
            case FundamentalInfo::DATE:
                return sizeof(Fundamental) + (sizeof(FundamentalDate) - sizeof(FundamentalNum));
            case FundamentalInfo::WCHAR:
                return sizeof(Fundamental) + (sizeof(FundamentalWChar) - sizeof(FundamentalNum));
        }
        return sizeof(Fundamental);
    }

    static const size_t MaxSize() { return sizeof(Fundamental) + (std::max)(sizeof(FundamentalChar), sizeof(FundamentalWChar)); }

protected:
    void copy(const Fundamental& f) {
        _period_date = f._period_date; _date = f._date; record_date = f.record_date; _id = f._id; _type = f._type; _flags = f._flags; attributes = f.attributes;
        _size = Fundamental::GetSize();

        switch (getType(_type)) {
            case FundamentalInfo::CHAR: {
                const FundamentalChar * ptr = reinterpret_cast<const FundamentalChar*>(&f._data);
                FundamentalChar * ptrT = reinterpret_cast<FundamentalChar*>(&_data);
                strncpy_s(ptrT->_val, _countof(ptrT->_val), ptr->_val, _TRUNCATE);
                break;
            }

            case FundamentalInfo::WCHAR: {
                const FundamentalWChar * ptr = reinterpret_cast<const FundamentalWChar*>(&f._data);
                FundamentalWChar * ptrT = reinterpret_cast<FundamentalWChar*>(&_data);
                wcsncpy_s(ptrT->_val, _countof(ptrT->_val), ptr->_val, _TRUNCATE);
                break;
            }

            case FundamentalInfo::DATE: {
                const FundamentalDate * ptr = reinterpret_cast<const FundamentalDate*>(&f._data);
                FundamentalDate * ptrT = reinterpret_cast<FundamentalDate*>(&_data);
                ptrT->_val = ptr->_val;
                break;
            }

            default:
                _data._val = f._data._val; break;
        }
    }

    void validate_numeric_value() {
        if (_data._val < not_threshold()) {
            // validate for not-applicable or not-meaningful
            if (CmpDbl(_data._val, not_available()) == 0)
                _type |= FundamentalInfo::NA;
            else if (CmpDbl(_data._val, not_meaningful()) == 0)
                _type |= FundamentalInfo::NMF;
        }
    }

    void validate_date_value(const char* val) {
        FundamentalDate * ptr = reinterpret_cast<FundamentalDate*>(&_data);

        std::string sVal(val);
        ptr->_val._t = hms(); // default to midnight

        // check format like 2006-6-15T00:00
        std::string::size_type p0 = sVal.find('T'), p1=std::string::npos, p2=std::string::npos;
        if (p0!=std::string::npos && isdigit(static_cast<unsigned char>(sVal[0]))) {
            p1 = sVal.find_first_of(':');
            if (p1!=std::string::npos) {
                unsigned char h = (unsigned char) atoi(sVal.substr(p0+1,p1).c_str());
                unsigned char min = (unsigned char) atoi(sVal.substr(p1+1).c_str());
                ptr->_val._t._hour = h; ptr->_val._t._min = min;
            }

            sVal.erase(p0);
            p1 = sVal.find_first_of('-'); p2 = sVal.find_last_of('-');
            if (p1!=std::string::npos && p2!=std::string::npos) {
                unsigned short y = static_cast<unsigned short>(atoi(sVal.substr(0,p1).c_str()));
                unsigned char m = static_cast<unsigned char>(atoi(sVal.substr(p1+1,p2).c_str()));
                unsigned char d = static_cast<unsigned char>(atoi(sVal.substr(p2+1).c_str()));
                ptr->_val._d = ymd(m, d, y);
            }
            return;
        }

        // check format like Aug  4 2006  2:29PM
        p0 = sVal.find(' ');
        if (p0!=std::string::npos) {
            std::string sM = sVal.substr(0,p0);
            unsigned char m=1;
            for (; m <= 12 && (_stricmp(sM.c_str(), monthnameabbr[m-1])!=0); ++m);
            if (m<=12) {
                for (;p0 < sVal.length() && !isdigit(static_cast<unsigned char>(sVal[p0])); ++p0);
                if (p0>=sVal.length()) return;
                for (p1=p0; p1<sVal.length() && isdigit(static_cast<unsigned char>(sVal[p1])); ++p1);
                unsigned char d=static_cast<unsigned char>(atoi(sVal.substr(p0,p1).c_str()));
                for(; p1<sVal.length() && !isdigit(static_cast<unsigned char>(sVal[p1])); ++p1);
                if (p1>=sVal.length()) return;
                unsigned short y=static_cast<unsigned short>(atoi(sVal.substr(p1).c_str()));
                ptr->_val._d = ymd(m, d, y);

                // time handling
                p0 = sVal.find_first_of(':');
                for (;p1<sVal.length() && isdigit(static_cast<unsigned char>(sVal[p1])); ++p1);
                if (p1>=sVal.length() || p0==std::string::npos) return;
                unsigned char hour = (unsigned char)atoi(sVal.substr(p1,p0).c_str());
                hour = (std::min)(hour, unsigned char(23));

                for (p1=p0+1;p1<sVal.length() && isdigit(static_cast<unsigned char>(sVal[p1])); ++p1);
                unsigned char minutes = (unsigned char)atoi(sVal.substr(p0+1,p1).c_str());
                minutes = (std::min)(minutes, unsigned char(59));

                if (p1<sVal.length() && sVal[p1]=='P') {
                    if (hour < 12) hour += 12;
                }
                else {
                    if (hour == 12) hour = 0;
                }

                ptr->_val._t._hour = hour; ptr->_val._t._min = minutes;
                return;
            }
        }

        const db_TIMESTAMP * date = reinterpret_cast<const db_TIMESTAMP*>(val);
        ptr->_val._d = ymd((unsigned char)date->month, (unsigned char)date->day, date->year);
    }
};


struct FundamentalMsg {
    int _begin;
    int _end;
    Fundamental _obj[1]; // dynamic array of objects..
};

struct FundamentalUpdate {
    char _symbol[16];
    Fundamental::FundamentalDate _date;

    bool operator==(const FundamentalUpdate& rh) {
        return (!_strcmpi(_symbol, rh._symbol) && (_date==rh._date));
    }
};

#pragma pack(pop,old_pack)
