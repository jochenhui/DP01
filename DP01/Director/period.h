//****************************************************************************
//
//    (C) Copyright 1990 - 1998 by Windows On Wallstreet, Inc.  All rights
//    reserved.  Permission to use this work for any purpose must by obtained
//    in writing from Windows On Wallstreet, Inc.; 1820 Glenville Dr, Ste 100,
//    Richardson, TX 75081.
//
//****************************************************************************

#ifndef period_h
#define period_h

// This is a tricky generalization of period. The previous valid values for
// period were...
//            MSB     LSB
// 'D'  0x44   0100 0100
// 'W'  0x57   0101 0111
// 'M'  0x4D   0100 1101
// 'Y'  0x59   0101 1001
// 'I'  0x49   0100 1001
// 'U'  0x55   0101 0101
// 'X' and 'V' were defined but never used so they can be ignored.

// Note that the Least Significant Bit is 1 for all but daily.  So I hereby
// declare the following : If the LSB is zero then the upper seven bits
// represent the seven days of the week.  Each bit defines if that day is
// a trading day for a security.  Further, Tuesday thru Thursday are inverted.
// In other words, zero bit means the security trades on that day.  The
// reason is so that the binary representation for 'D' (0x44) will represent
// a trading week of Monday thru Friday.

// SMTWHFS
// 01000100 = 0x44 = 'D'

// By doing this we will not need to translate any stored periocities from
// incremental files, stored charts and templates, and old CD's.

// Note that to check for weekly, monthly, yearly, incremental, and unknown is
// the SAME check as before! i.e. period == 'W' or period == 'M'

// Here are some macros for determining trading days, etc.
#define TSPECSUNSET(x, on)  ( on ? ((x)|0x80) : ((x)&0x7F) )
#define TSPECMONSET(x, on)  ( on ? ((x)|0x40) : ((x)&0xBF) )
#define TSPECTUESSET(x, on) ( on ? ((x)&0xDF) : ((x)|0x20) )
#define TSPECWEDSET(x, on)  ( on ? ((x)&0xEF) : ((x)|0x10) )
#define TSPECTHURSET(x, on) ( on ? ((x)&0xF7) : ((x)|8) )
#define TSPECFRISET(x, on)  ( on ? ((x)|4) : ((x)&0xFB) )
#define TSPECSATSET(x, on)  ( on ? ((x)|2) : ((x)&0xFD) )

#define TSPECSUN  0x80
#define TSPECMON  0x40
#define TSPECTUES 0x20
#define TSPECWED  0x10
#define TSPECTHUR 8
#define TSPECFRI  4
#define TSPECSAT  2
#define TSALLSPEC 0xC6
#define TSNOPER   0x38
#define TSPEC(f) (((f)&TSPECSUN  ? TSPECSUN  : 0) | ((f)&TSPECMON  ? TSPECMON  : 0) |\
                 ((f)&TSPECTUES ? 0 : TSPECTUES) | ((f)&TSPECWED  ? 0 : TSPECWED ) |\
                 ((f)&TSPECTHUR ? 0 : TSPECTHUR) |\
                 ((f)&TSPECFRI ? TSPECFRI : 0) | ((f)&TSPECSAT ? TSPECSAT : 0))
//example...
// BYTE period = TSPEC(TSPECMON|TSPECTUES|TSPECWED|TSPECTHUR|TSPECFRI);

#define TRADESSUN(x)     (0x80==((x)&0x81))
#define TRADESMON(x)     (0x40==((x)&0x41))
#define TRADESTUES(x)    (!((x)&0x21))
#define TRADESWED(x)     (!((x)&0x11))
#define TRADESTHUR(x)    (!((x)&9))
#define TRADESFRI(x)     (4==((x)&5))
#define TRADESSAT(x)     (2==((x)&3))
#define ISWEEKSPEC(x)    (!((x)&1))
// This will help catch the places where sixday and sevenday week periocities
// are used.  There should be no archived periods of this type, but 'V' is
// used in code to calc the number of days between.
#define INTERNALWEEKSPECTEST(x)  ASSERT( (x)!='V' && (x)!='X' );
#define ASSERTPERIOD(x)  ASSERT( ISWEEKSPEC(x) || (x)=='W' || (x)=='M' || (x)=='Y' || (x)=='I' || (x)=='U' );
#define PERIODMATCHES(x, y) ((ISWEEKSPEC(x) && ISWEEKSPEC(y)) || ((x) == (y)))

#endif
