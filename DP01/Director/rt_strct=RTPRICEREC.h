#pragma once
#include <memory.h>  // need memset

#pragma pack(push,old_pack,1)

struct RTPRICEREC_BASE
{
    unsigned long JulDate;           // always in 1900 format (M4)
    unsigned long lTotalVolume;
    float         open;
    float         close;
    float         high;
    float         low;
    unsigned long  dwOpenInt;
    unsigned long  lUpVolume;
    unsigned long  lDnVolume;
    unsigned long  dwTotalTicks;
    unsigned long  dwUpTicks;
    unsigned long  dwDnTicks;

    RTPRICEREC_BASE() { memset (this, 0, sizeof *this); }

    // base record type traits
    unsigned long GetDate() const {return JulDate;}
    void SetDate(unsigned long dt) { JulDate=dt; }
    bool IsEndMinuteTick() const { return false; }
    bool IsEndSecondTick() const { return false; }
    bool IsEndNettingTick() const { return false; }
    bool IsEndTick() const { return false; }
};

#pragma pack(pop,old_pack)

struct EODDATA
{
    unsigned char sMonth;
    unsigned char sDay;
    unsigned short sYear;
    unsigned char eMonth;
    unsigned char eDay;
    unsigned short eYear;
    unsigned short loadOptions; // WOWRT_EOD_LOAD_***
};
typedef EODDATA *PEODDATA;

struct EODDATAEX : public EODDATA
{
    unsigned char BarWeight; // use ORGS_RESOLUTIONID_DAY, WEEK, and MONTH
};
typedef EODDATAEX* PEODDATAEX;
typedef const EODDATAEX* CPEODDATAEX;
