#pragma once
#include <memory.h>  // need memset
#include <type_traits> // tr1

#pragma pack(push,old_pack,1)

// Hist Data description
struct HistData
{
    // same value as ORCORRECTIONTYPE_ and M3HISTREQTYPE_ - needs to be in sync with nugget_bag::HistoryType (aa\clodfile\arsenal.h)
    enum TYPE { TYPE_UNKNOWN=0, TYPE_EOD=7 , TYPE_MBAR, TYPE_TICK, TYPE_FUNDAMENTAL, TYPE_CONVERSION, TYPE_CONVERSION_RESERVED_MIN, TYPE_CONVERSION_RESERVED_TICK, TYPE_CCCROLLOVER, TYPE_UNDERLYING=16, TYPE_SECONDBAR, TYPE_CONVERSION_RESERVED_SECBAR, TYPE_LOCALE_ID_DATA, TYPE_CORPACTIONS=0x20, TYPE_CORRECTIONS=0x40 };

    unsigned char	type;
    unsigned char	unused1;
    unsigned short  unused2;
    int				begin;
    int				end;	// upTo but not include end; set to INT_MAX to load all history; set end=begin means no history
    unsigned		limit;	// limit bars. use option flag to limit days, etc. UINT_MAX means no limit
    unsigned		options;

    HistData() {
        memset (this, 0, sizeof *this);
        // note that memset is better than RtlZeroMemory because the compiler has an 'intrinsic' form.
    }
    HistData(unsigned char cType, int iBegin, int iEnd, unsigned uLimit) : type(cType), begin(iBegin), end(iEnd), limit(uLimit), unused1(0), unused2(0), options(0) {}
};


// JMD 2010-March-11:  This enum doesn't have a name, and I'm not sure it "goes with" the
// HistData structure above.  The bottom ones are not used in the code, and the top ones are used
// with parameters named "options".  Is that the same as the "options" field above?

enum {
     HISTDATA_OPTION_HISTORY = 0x0000
    ,HISTDATA_OPTION_REALTIME=0x0001	// request realtime update, return realtime data.
    ,HISTDATA_OPTION_CACHED=0x0002       // return cached data
    ,HISTDATA_OPTION_BLOCK=0x4000	    // return, the data are formated in block
    ,HISTDATA_OPTION_ERROR=0x8000	    // return, error code follows

    ,HISTDATA_FUNDAMENTAL_HISTORY=0x0000
    ,HISTDATA_FUNDAMENTAL_REALTIME=0x0001
    ,HISTDATA_FUNDAMENTAL_BLOCK=0x4000
};

#pragma pack(pop,old_pack)


/*  The following metafunctions are for sorting records of type
TICKREC, RTINTRADAY_PRICEREC, RTPRICEREC, and RTCNVREC.
The 'unsigned' forms are for comparing records with a time value key, useful for upper_bound and lower_bound.
Currently, those history records are storing the time in an 'unsigned' with a nested typedef datetime_t
stating what the type really is.  The plan is to change the record to strongly type the value (and the
GetDate/SetDate functions) eventually.  These predicates would then change to use the proper type
rather than 'unsigned', or both supported but with the other one being the native form.
*/

template <typename RecType>
struct rectype_time_compare_asc {
    typedef typename RecType::datetime_t datetime_t;
    bool operator()( const RecType & a , unsigned long b ) {
        return tm(a.GetDate()) < tm(b) ;
    }
    bool operator()( unsigned long a, const RecType & b ) {
        return tm(a) < tm(b.GetDate());
    }
    bool operator() (const RecType& left, const RecType& right) {
        return tm(left.GetDate()) < tm(right.GetDate());
    }
    bool operator()( const RecType & a , const datetime_t& b ) {
        return tm(a.GetDate()) < b ;
    }
    bool operator()( const datetime_t& a, const RecType & b ) {
        return a  < tm(b.GetDate());
    }
private:
    static const datetime_t& tm (const unsigned long& val) {  return reinterpret_cast<const datetime_t&>(val); }
};


template <typename RecType>
struct rectype_time_compare_desc {
    typedef typename RecType::datetime_t datetime_t;
    bool operator()( const RecType & a , unsigned long b ) {
        return tm(a.GetDate()) > tm(b) ;
    }
    bool operator()( const RecType & a , const datetime_t& b ) {
        return tm(a.GetDate()) > b;
    }
    bool operator()( unsigned long a, const RecType & b ) {
        return tm(a) > tm(b.GetDate());
    }
    bool operator()( const datetime_t& a, const RecType & b ) {
        return a > tm(b.GetDate());
    }
    bool operator() (const RecType& left, const RecType& right) {
        return tm(left.GetDate()) > tm(right.GetDate());
    }
private:
    static const datetime_t& tm (const unsigned long& val) {  return reinterpret_cast<const datetime_t&>(val); }
};

// Used for storage behavior - single or multiple blocks
template <typename RecType>
struct is_multiblock :std::tr1::false_type { };

