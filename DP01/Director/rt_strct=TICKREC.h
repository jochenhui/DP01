#pragma once
#include <memory.h>  // need memset

#pragma pack(push,old_pack,1)

struct TICKREC_BASE
{
    unsigned long   m_JulDate;       // always in 1970 format (M4)
    unsigned long   m_Vol;
    float           m_Last;

    unsigned char            m_Type;
    union {
        unsigned char        m_TradeExchange;  // use if (m_TickFlagsEx & TICKFLAGEX_NETTED)==0
        unsigned char        m_TotalTicks;     // use if m_TickFlagsEx & TICKFLAGEX_NETTED
    };
    unsigned char            m_TickFlags;

    // Bitmask m_TickFlags field:
    static const unsigned char TICKFLAG_BADSEQUENCE     = 0x02;
    static const unsigned char TICKFLAG_FILTERED        = 0x04;
    static const unsigned char TICKFLAG_CORRECTIONMASK           = 0x18;
    static const unsigned char TICKFLAG_CORRECTIONMASK_NORMAL    = 0x00;
    static const unsigned char TICKFLAG_CORRECTIONMASK_INSERTED  = 0x08;
    static const unsigned char TICKFLAG_CORRECTIONMASK_DELETED   = 0x10;
    static const unsigned char TICKFLAG_CORRECTIONMASK_CORRECTED = 0x18;
    static const unsigned char TICKFLAG_BID             = 0x40;
    static const unsigned char TICKFLAG_ASK             = 0x80;

    unsigned char            m_TickFlagsEx;

    // Bitmask m_TickFlagsEx field:
    static const unsigned char TICKFLAGEX_NETTED =          0x01;
    static const unsigned char TICKFLAGEX_LOCAL_EXCHANGE =  0x02;

    // End Tick defintions
    static const float END_MINUTE_TICK;
    static const float END_SECOND_TICK;
    static const float END_NETTING_TICK;

    TICKREC_BASE() {
        memset (this, 0, sizeof *this);
        // note that memset is better than RtlZeroMemory because the compiler has an 'intrinsic' form.
    }

    // base record type traits
    unsigned long GetDate() const {return m_JulDate;}
    void SetDate(unsigned long dt) { m_JulDate=dt; }

    bool is_correction_deleted() const { return ((m_TickFlags & TICKFLAG_CORRECTIONMASK) == TICKFLAG_CORRECTIONMASK_DELETED) ? true : false; }
    bool is_regular_trade() const {
        if (m_TickFlags & (TICKFLAG_FILTERED | TICKFLAG_BADSEQUENCE | TICKFLAG_BID | TICKFLAG_ASK))
            return false;
        if (is_correction_deleted())
            return false;

        return true;
    }
    bool is_bid_or_ask() const { return (m_TickFlags & (TICKFLAG_BID | TICKFLAG_ASK)) ? true : false; }
    bool is_bid() const { return (m_TickFlags & TICKFLAG_BID) ? true : false; }
    bool is_ask() const { return (m_TickFlags & TICKFLAG_ASK) ? true : false; }
    bool is_bad_sequence() const { return (m_TickFlags & TICKFLAG_BADSEQUENCE) ? true : false; }
    bool is_filtered() const { return (m_TickFlags & TICKFLAG_FILTERED) ? true : false; }

    bool IsEndMinuteTick() const {
        return (m_Last == END_MINUTE_TICK);
    }
    bool IsEndSecondTick() const {
        return (m_Last == END_SECOND_TICK);
    }
    bool IsEndNettingTick() const {
        return (m_Last == END_NETTING_TICK);
    }
    bool IsEndTick() const {
        return (m_Last >= END_NETTING_TICK);
    }

    // Specialized methods
    void SetEndTickProcessed(bool bReset=false) { m_Vol = (bReset) ? 0 : 0xFFFFFFFF; }
    bool IsEndTickProcessed() const { return (m_Vol == 0xFFFFFFFF); }
    bool IsNettedTick() const { return (m_TickFlagsEx & TICKFLAGEX_NETTED) ? true : false; }
    unsigned char GetTickCount() const { return (m_TickFlagsEx & TICKFLAGEX_NETTED) ? m_TotalTicks : 1; }
    bool NetCompare(const TICKREC_BASE & rTick) const {
        return (  m_JulDate == rTick.m_JulDate && m_Last == rTick.m_Last && m_Type == rTick.m_Type && m_TickFlags == rTick.m_TickFlags) ? true : false;
    }
    void SetEndNettingTick(unsigned long date) {
        m_Last = END_NETTING_TICK;
        m_JulDate = date;
    }
    void SetEndSecondTick(unsigned long date) {
        m_Last = END_SECOND_TICK;
        m_JulDate = date;
    }
    void SetEndMinuteTick(unsigned long date) {
        m_Last = END_MINUTE_TICK;
        m_JulDate = date;
    }

    // 3rd Party DataAPI/Shim interface support
    static const unsigned short LOCAL_EXCHANGE_INDEX_OFFSET=   512;     // Exchanges 512 through 999 are reserved for 3rd Party DataAPI/Shim
    static const unsigned short CUSTOM_EXCHANGE_INDEX_OFFSET= 1000;     // Exchanges 1000+ are reserved for 3rd Party Import files

    static unsigned short MakeLocalExchangeIndex(unsigned char exch_index) {
        return (TICKREC_BASE::LOCAL_EXCHANGE_INDEX_OFFSET + exch_index);
    }
    void SetLocalExchange(unsigned char exch_index) {
        m_TradeExchange = exch_index; m_TickFlagsEx |= TICKFLAGEX_LOCAL_EXCHANGE;
    }
    unsigned short GetTradeExchange() {
        return ((m_TickFlagsEx&TICKFLAGEX_LOCAL_EXCHANGE)>0)? (m_TradeExchange+LOCAL_EXCHANGE_INDEX_OFFSET) : m_TradeExchange;
    }
};


#pragma pack(pop,old_pack)

