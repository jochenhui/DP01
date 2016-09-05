#pragma once
#pragma warning (disable: 4800)

// MAKE SURE TO CHANGE VERSION NUMBER IF CCARECORD STRUCTURE MODIFIED!!!!
#define CCA_VERSION_NUMBER  1

// BIT FLAG VALUES - internal usage
#define CCA_BIT_CORPORATE_ACTION    0x01
#define CCA_BIT_RESET_ACTION        0x040
#define CCA_BIT_DELETE_ACTION       0x080
#define CCA_BIT_DELETED_RECORD      0x0100
#define CCA_BIT_RESET_CCA_ACTION    0x0200
#define CCA_BIT_APPLIED             0x8000

// CCA Message Type
#define CCATYPE_INVALID             0
#define CCATYPE_COMPLETE            0x0004
#define CCATYPE_CORPACTION          0x0020
#define CCATYPE_CORRECTION          0x0040


// Format of CCARECORD:
// GetCCAInfo in CCASqlHelper.DLL will return the records in this format:
//
// ACKCCARECORD (defined in WowServer.h) + Symbol (Single byte-Null ended) + X number of (CCARECORD + CCAValue)
// where X is defined in ACKCCARECORD => nRecords
// and CCAValue is equal to a double (coefficient or delete sequence no.) [or an M3 Structure (correction)]
//
// The version number is set by the creator of the record... (CCA_VERSION_NUMBER)
//

#pragma pack( push, old_pack, 1 )

struct CCARECORD
{
    //Flags - dwFlagsField
    //  0x0001  set = corporate action,     reset = correction

    // Specific to CORP ACTIONS
    //  0x0002  set = split,                reset = distribution
    //  0x0004  set = add,                  reset = multiply
    //
    //  0x0020/0x0010/0x0008
    //      =>  001 + split  (11)  = Share dividend - same symbol
    //      =>  010 + split  (19)  = Share dividend - different symbol
    //      =>  011 + split  (27)  = Cash dividend
    //      =>  100 + split  (35)  = Spin off
    //      =>  101 + split  (43)  = Secondary offering
    //      =>  111 + split  (57)  = Change of exchange

    // Specific to CORRECTIONS
    //  0x0010/0x0008
    //      =>  00      = EOD bar correction,       01 (8) = 1 minute bar correction
    //          10 (16) = 1 tick bar correction,    11 (24)= symbol name change
    //
    //
    //  0x0040  set = RESET Cache action,   reset = NO RESET...
    //  0x0080  set = DELETE action,        reset = INSERT action
    //  0x0100  set = Deleted record        reset = Normal record
    //  0x0200  set = RESET CCA action,     reset = NO RESET...
    //
    //  0x0400/0x0800
    //      in conjunction with RESET Cache action bit.
    //      =>  00 = RESET all data types   01 = RESET tick data only
    //          10 = RESET minute data only 11 = RESET eod data only
    //  0x1000 set = Underlying Correction
    //  0x2000 set = Underlying Reset; the above reset all will also reset underlying
    //  0x4000 set = VIRTUAL corp.action   reset = Regular corp.action
    enum
    {
        CORPORATE_ACTION        = 0x0001,
        CA_SPLIT                = 0x0002,
        CA_DISTRIBUTION         = 0x0004,
        CA_SHARE_DIV_SYM        = 0x0001 + 0x0002 + 0x0008,
        CA_SHARE_DIV_DIFF_SYM   = 0x0001 + 0x0002 + 0x0010,
        CA_CASH_DIV             = 0x0001 + 0x0002 + 0x0018,
        CA_SPIN_OFF             = 0x0001 + 0x0002 + 0x0020,
        CA_SECONDARY_OFF        = 0x0001 + 0x0002 + 0x0028,
        CA_CHANGE_EXCH          = 0x0001 + 0x0002 + 0x0038,

        C_EOD_BAR               = 0x0000,
        C_MIN_BAR               = 0x0008,
        C_TICK_BAR              = 0x0010,
        C_SYMBOL_CHANGE         = 0x0018,
        C_BAR_BITMASK           = 0x0018,

        C_RESET_CACHE           = 0x0040,
        C_DELETE_ACTION         = 0x0080,
        C_DELETED_RECORD        = 0x0100,
        C_RESET_ACTION          = 0x0200,
        C_RESET_ALL             = 0x0040,
        C_RESET_ALL_TICKS       = 0x0040 + 0x0400,
        C_RESET_ALL_MIN         = 0x0040 + 0x0800,
        C_RESET_ALL_EOD         = 0x0040 + 0x0C00,
        C_RESET_BITMASK         = 0x0040 + 0x0400 + 0x0800,

        C_UNDERLYING            = 0x1000,
        C_RESET_UNDERLYING      = 0x2000,

        CA_VIRTUAL              = 0x4000
    };

    unsigned long   dwDate;
    unsigned long   dwFlagsField;
    unsigned long   dwCCAseqNo;
    unsigned long   dwValLen;
    unsigned char    byVersion;
    unsigned char    byAssetType;

public:
    CCARECORD() : byVersion(CCA_VERSION_NUMBER), dwDate(0), dwFlagsField(0), dwCCAseqNo(0), dwValLen(0), byAssetType(0) {}
    CCARECORD(unsigned char asset_type, unsigned long date, unsigned long seqno, unsigned long cca_type) :
        byVersion(CCA_VERSION_NUMBER), byAssetType(asset_type), dwDate(date), dwCCAseqNo(seqno), dwFlagsField(cca_type), dwValLen(sizeof(double)) {}

public:
    bool IsCorpAction() const            { return dwFlagsField & CORPORATE_ACTION; }
    bool IsAccretive() const             { return dwFlagsField & CA_DISTRIBUTION; }
    bool IsResetCache() const             { return dwFlagsField & C_RESET_CACHE; }
    bool IsResetCacheAll() const         { return (dwFlagsField & C_RESET_BITMASK) == C_RESET_CACHE; }
    bool IsResetCacheEOD() const         { return (dwFlagsField & C_RESET_BITMASK) ==  C_RESET_ALL_EOD; }
    bool IsResetCacheUnderlying() const  { return dwFlagsField & C_RESET_UNDERLYING; }
    bool IsResetCacheMin() const         { return (dwFlagsField & C_RESET_BITMASK) == C_RESET_ALL_MIN; }
    bool IsResetCacheTick() const        { return (dwFlagsField & C_RESET_BITMASK) == C_RESET_ALL_TICKS; }
    bool IsDeleteAction() const          { return dwFlagsField & C_DELETE_ACTION; }
    bool IsDeleted() const               { return dwFlagsField & C_DELETED_RECORD; }
    bool IsResetCCA() const              { return dwFlagsField & C_RESET_ACTION; }
    bool IsResetUnderlying() const       { return dwFlagsField & C_RESET_UNDERLYING; }
    bool IsApplied() const               { return dwFlagsField & CCA_BIT_APPLIED; }
    bool IsMinuteBarCorrection() const   { return (dwFlagsField <= C_BAR_BITMASK) && ((dwFlagsField & C_BAR_BITMASK) == C_MIN_BAR); }
    bool IsTickCorrection() const        { return (dwFlagsField <= C_BAR_BITMASK) && ((dwFlagsField & C_BAR_BITMASK) == C_TICK_BAR); }
    bool IsEODBarCorrection() const      { return (dwFlagsField <= C_BAR_BITMASK) && ((dwFlagsField & C_BAR_BITMASK) == C_EOD_BAR); }
    bool IsUnderlyingCorrection() const  { return dwFlagsField == C_UNDERLYING; }
    bool IsSymbolChange() const          { return !IsCorpAction() && (dwFlagsField & C_BAR_BITMASK) == C_SYMBOL_CHANGE; }
    bool IsCorrection() const            { return !(IsCorpAction() || IsSymbolChange()); }

    bool IsBarCorrection() const         {
        unsigned long dwFlags = IsDeleted() ? (dwFlagsField - 0x0100) : dwFlagsField;
        return (!IsCorpAction() && ((dwFlags < 0x0040) || (dwFlags & 0x1000)));
    }

    unsigned long GetSize() const { return sizeof(CCARECORD); }
    void* GetHeader() { return (this + 1); }
    CCARECORD * NextRecord() { return (CCARECORD*) (reinterpret_cast<char*>(this) + sizeof(CCARECORD) + dwValLen); }
    void Applied() { dwFlagsField |= CCA_BIT_APPLIED; }
};

typedef CCARECORD * PCCARECORD;

#pragma warning (default : 4800 )
#pragma pack(pop,old_pack)