#pragma once
#pragma warning (disable: 4800)

#include <algorithm>  // need std::min

#pragma pack(push, old_pack)

#include "rt_strct=RTCCADATA.h"

#undef min
#undef max


//
// Correction Data Version
//
#define ORCORRECTION_VERSION2   2

//
// Tick Structure
//
typedef struct {
    long           lTime;
    unsigned char  reserved[20];
} RTOR_TICK, *LPRTOR_TICK;

//
// Minute Bar (BAR) Structure
//
typedef struct {
    long     lTime;
    unsigned char  reserved[60];
} RTOR_BAR, *LPRTOR_BAR;

//
// End of Day (EOD) Structure
//
typedef struct {
    unsigned char  ucDay;
    unsigned char  ucMonth;
    unsigned short usYear;
    unsigned char  reserved[68];
} RTOR_EOD, *LPRTOR_EOD;

//
// Correction Request Type Definition
//
#define ORCORRECTIONTYPE_EOD                        7
#define ORCORRECTIONTYPE_BAR                        8
#define ORCORRECTIONTYPE_TICK                       9

//
// Correction Action Type Definition
//
#define ORCORRECTIONACTION_UPDATE                   2
#define ORCORRECTIONACTION_SYMBOLCHANGE             5
#define ORCORRECTIONACTION_MODIFYRANGE              11


#define ORCORRECTIONACTION_CORPACT_SPLIT			16  // This correction is sent when a symbol has undergone a split
                                                        // - Data provider backend should have updated data ready
                                                        //   before sending ORCORRECTIONACTION_CORPACT_SPLIT.
                                                        // - TradeStation will reset & reload data stream from data provider.

#define ORCORRECTIONACTION_CORPACT_ADJUSTMENT		17  // This correction is sent when a symbol has undergone a adjustment
                                                        // - Data provider backend should have updated data ready
                                                        //   before sending ORCORRECTIONACTION_CORPACT_ADJUSTMENT.
                                                        // - TradeStation will reset & reload data stream from data provider.

//
// *** Correction Structures *********************************************************
//

// Correction Header
typedef struct {
    unsigned long dwTotalLength;
    unsigned short wReqType;
    unsigned short wAction;
    int        iVersion;
} ORCORRECTION_HEADER, *LPORCORRECTION_HEADER;

// Tick Update Structure
struct RTORCORRECTION2_TICK {
    RTORCORRECTION2_TICK(unsigned short action) {
        memset((void*)this, 0, sizeof(RTORCORRECTION2_TICK));
        header.dwTotalLength = sizeof(RTORCORRECTION2_TICK);
        header.wReqType = ORCORRECTIONTYPE_TICK;
        header.wAction = action;
        header.iVersion = ORCORRECTION_VERSION2;
    }
    ORCORRECTION_HEADER header;
    RTOR_TICK tick1;
    RTOR_TICK tick2;
    unsigned char reserved[20];
};
typedef RTORCORRECTION2_TICK*  LPRTORCORRECTION2_TICK;

// Bar Update Structure
struct RTORCORRECTION2_BAR {
    RTORCORRECTION2_BAR(unsigned short action) {
        memset((void*)this, 0, sizeof(RTORCORRECTION2_BAR));
        header.dwTotalLength = sizeof(RTORCORRECTION2_BAR);
        header.wReqType = ORCORRECTIONTYPE_BAR;
        header.wAction = action;
        header.iVersion = ORCORRECTION_VERSION2;
    }
    ORCORRECTION_HEADER header;
    RTOR_BAR bar1;
    RTOR_BAR bar2;
    unsigned char reserved[12];
};
typedef RTORCORRECTION2_BAR* LPRTORCORRECTION2_BAR;

// EOD Update Structure
struct RTORCORRECTION2_EOD {
    RTORCORRECTION2_EOD(unsigned short action) {
        memset((void*)this, 0, sizeof(RTORCORRECTION2_EOD));
        header.dwTotalLength = sizeof(RTORCORRECTION2_EOD);
        header.wReqType = ORCORRECTIONTYPE_EOD;
        header.wAction = action;
        header.iVersion = ORCORRECTION_VERSION2;
    }
    ORCORRECTION_HEADER header;
    RTOR_EOD eod1;
    RTOR_EOD eod2;
    unsigned char reserved[12];
};
typedef RTORCORRECTION2_EOD* LPRTORCORRECTION2_EOD;

// Symbol Renamed Structure
struct RTORCORRECTION2_SYMBOLRENAMED {
    RTORCORRECTION2_SYMBOLRENAMED(unsigned short action) {
        memset((void*)this, 0, sizeof(RTORCORRECTION2_SYMBOLRENAMED));
        header.dwTotalLength = sizeof(RTORCORRECTION2_SYMBOLRENAMED);
        header.wAction = action;
        header.iVersion = ORCORRECTION_VERSION2;
    }
    ORCORRECTION_HEADER  header;
    char szSymbol1[32];
    char szSymbol2[32];
};
typedef RTORCORRECTION2_SYMBOLRENAMED* LPRTORCORRECTION2_SYMBOLRENAMED;


#pragma warning (default : 4800 )
#pragma pack(pop,old_pack)