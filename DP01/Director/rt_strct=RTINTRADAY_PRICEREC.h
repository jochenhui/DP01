#pragma once
#include <memory.h>  // need memset

#pragma pack(push,old_pack,1)
// DO NOT MODIFY This structure's initial order of attributes, must
// be identical to RTINTRADAY_PRICEREC_OLD
struct RTINTRADAY_PRICEREC_BASE
{
    unsigned long JulDate;      // always in 1970 format (M4)
    unsigned long lTotalVolume;
    float         open;
    float         close;
    float         high;
    float         low;
    unsigned long lUpVolume;
    unsigned long lDnVolume;
    unsigned short  wTotalTicks;
    unsigned short  wUpTicks;
    unsigned short  wDnTicks;
    unsigned short  wBidAskTicks;

    RTINTRADAY_PRICEREC_BASE() { memset (this, 0, sizeof *this); }
    RTINTRADAY_PRICEREC_BASE(unsigned long dt, long vol, float o, float c, float h, float l, long upvol, long dnvol, unsigned short ticks, unsigned short upticks, unsigned short dnticks, unsigned short bidaskticks) :
        JulDate(dt), lTotalVolume(vol), open(o), close(c), high(h), low(l), lUpVolume(upvol), lDnVolume(dnvol), wTotalTicks(ticks), wUpTicks(upticks), wDnTicks(dnticks), wBidAskTicks(bidaskticks)
    {
    }

    // base record type traits
    unsigned long GetDate() const {return JulDate;}
    void SetDate(unsigned long dt) { JulDate=dt; }
    bool IsEndMinuteTick() const { return false; }
    bool IsEndSecondTick() const { return false; }
    bool IsEndNettingTick() const { return false; }
    bool IsEndTick() const { return false; }
};

#pragma pack(pop,old_pack)

