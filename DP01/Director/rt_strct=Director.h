
#pragma once


///////////////////////////////////////////////////////////////////
// BAR load options

// One of these load options is set in the lower bits of loadOptions
//#define WOWRT_LOAD_TICKS 0
#define WOWRT_LOAD_BIDS  1
#define WOWRT_LOAD_ASKS  2
// This type is for requesting ticks/bids/asks all together
// (for time & sales)
#define WOWRT_LOAD_TRADES 4
#define WOWRT_LOAD_ALL   7

// These flags are set in the upper bits of loadOptions
#define WOWRT_LOAD_TIME_SALES_MINUTES       0x10
#define WOWRT_LOAD_VOLUME_AT_PRICE          0x20
#define WOWRT_LOAD_SEND_END_OF_MINUTE_TICKS 0x40
#define WOWRT_LOAD_TRADE_DAY_START			0x80	// For bars back request to send data start from TradeDayStart in TICKDATA
#define WOWRT_LOAD_MIN_BARS_RECONNECT       0x100   // Used internally on client-side
#define WOWRT_LOAD_DELAYED_HIST             0x200
#define WOWRT_LOAD_FORCE_ARCHIVE_EARLIEST   0x400
#define WOWRT_LOAD_SEND_END_OF_SECOND_TICKS 0x800
#define WOWRT_LOAD_SEND_NETTED_TICKS        0x1000
#define WOWRT_LOAD_VWAP                     0x2000
#define WOWRT_LOAD_FREE_HIST                0x4000
#define WOWRT_LOAD_CURRENT_CALENDAR_DAY     0x8000

#define WOWRT_LOAD_OPEN_INTEREST_BARS       0x10000
#define WOWRT_LOAD_TWAP_BARS                0x20000


//////////////////////////////////////////////////////
// EOD Load options
#define WOWRT_EOD_LOAD_ALL_BARS      0x00
#define WOWRT_EOD_LOAD_COMPLETE_ONLY 0x01
#define WOWRT_EOD_LIMIT_TO_ONE_BAR   0x02
#define WOWRT_EOD_LOAD_FILTER_DATE   0x04

#define WOWRT_EOD_LOAD_OPEN_INTEREST_BARS   0x10
#define WOWRT_EOD_LOAD_TWAP_BARS            0x20


// Additional flags located in HIWORD of type, LOWORD(type) = {TR_TICKRECK, TR_PRICEREC)
#define WOWRT_EOD_AFTER_MARKET_BAR  0x01
#define WOWRT_CNV_LAST_BAR          0x40
#define WOWRT_CNV_DAILY_UPDATE      0x80
///////////////////////////////////////////////////////


struct TICKDATA
{
    ULONG      JulianStartDate;
    ULONG      JulianEndDate;

    enum { MINUTE_BARS=-1, TICK_BARS=1, SECOND_BARS=2 }; // supported bar weights
    short      BarWeight;
    short      nMaxTicks;
    DWORD      dwBack;        // bars, ticks, or minutes
    BYTE       TradeDayStartHour;
    BYTE       TradeDayStartMin;
    BYTE       TimeZone;
    BYTE       Reserved; // for future use
    DWORD      dwLoadOptions;         // WOWRT_LOAD_***

    bool free() { return (dwLoadOptions&WOWRT_LOAD_FREE_HIST)>0; }
    bool delayed() { return (dwLoadOptions&WOWRT_LOAD_DELAYED_HIST)>0; }
};
typedef struct TICKDATA *PTICKDATA;

struct RTSec_OptionFilter
{
    enum	{	AllOptions = 0x00 ,
                DateRange = 0x01 ,
                DateNum = 0x02 ,
                StrikeRange = 0x04 ,
                StrikeNum = 0x08 ,
                Call = 0x10 ,
                Put = 0x20 ,
                OpenIntNum = 0x40 ,
                Regionals = 0x80,
                Composites = 0x100,
                FuturePit = 0x200,
                FutureElectronic = 0x400,
                FutureCombined = 0x800,
                Mini = 0x1000
         };

    UINT        cbSize;
    UINT        fMask;
    union
    {
        struct
        {
            long	DateL ;		// julTy
            long	DateH ;		// julTy
        } ;
        int	DateN ;
    } ;
    union
    {
        struct
        {
            float StrikeL ;
            float StrikeH ;
        } ;
        int	StrikeN ;
    } ;
    int m_nOpenIntN;

    // Constructor
    RTSec_OptionFilter() { cbSize = sizeof ( RTSec_OptionFilter ) , fMask = AllOptions ; }
} ;

struct HISTORYINFO
{
    enum { OptionArchiveInfo=0x1, ForceArchiveDownload=0x2, SupportUnicodeSymbolDescription=0x4 };

    UINT	options;
    ULONG	startdate;
    ULONG	enddate;

    HISTORYINFO() : options(0), startdate(0), enddate(0) {}
};

typedef struct tagCFI {
    typedef unsigned int element_type;
    unsigned int c:5, g:5, a1:5, a2:5, a3:5, a4:5, unused:2;

    tagCFI(char category, char group, char a1='X', char a2='X', char a3='X', char a4='X')
        : c(category), g(group), a1(a1), a2(a2), a3(a3), a4(a4), unused(0) {}
    explicit tagCFI(element_type v) { *(unsigned int*)this = v; }
    element_type element() const { return *(const unsigned int*)this; }

    char category() const { return to_char(c); }
    char group() const { return to_char(g); }
    char exercise() const {
        switch (category()) {
            case 'O': return to_char(a1);
        }
        return 'X';
    }
    char underlying() const {
        switch (category()) {
            case 'O': return to_char(a2);
            case 'F': return to_char(a1);
        }
        return 'X';
    }
    char delivery() const {
        switch (category()) {
            case 'O': return to_char(a3);
            case 'F': return to_char(a2);
        }
        return 'X';
    }
    char settlement() const {
        switch (category()) {
            case 'O': return to_char(a4);
            case 'F': return to_char(a3);
        }
        return 'X';
    }
    static char to_char(unsigned int i) { return '@' + (char)i; }
} CFI, *PCFI;

//
//  Archive Download Information
//
#define MAX_SYMBOL_SIZE             25
#define MAX_DESCRIPT_SIZE           80

struct ACKARCHIVEINFO
{
    ULONG ArchiveJulianStartDate;
    ULONG ArchiveJulianEndDate;
    DWORD JulianNextDownloadPeriod;
    DWORD JulianNextDownloadPeriodEnd;
    char  Symbol[MAX_SYMBOL_SIZE];              //  allows lookup of CA info once complete
    char  Description[MAX_DESCRIPT_SIZE];       //  ANSI symbol description, sending to client
    bool  bOption;
    wchar_t DescriptionW[MAX_DESCRIPT_SIZE];    //  Unicode symbol description

    ACKARCHIVEINFO() { ZeroMemory(this, sizeof(ACKARCHIVEINFO)); }
};
typedef struct ACKARCHIVEINFO *PACKARCHIVEINFO;


