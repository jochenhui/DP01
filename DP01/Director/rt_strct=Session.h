#ifndef rt_strct_Session_h_included
#define rt_strct_Session_h_included

#pragma pack( push, rt_strct_Session_h, 1 )

#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <set>
#include <memory>
#include <map>
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

#include <assert.h>

#ifndef period_h
    #include "period.h"
#endif  // period_h

#ifndef rt_defs_Director_h_included
    #include <rt_defs=Director.h>
#endif  // rt_defs_Director_h_included

using namespace std;


struct ORGS_SESSION_INFO
{
    WORD		wStartTime;			// time of the week in minutes since 12:00 midnight Sunday
    WORD		wStopTime;			// time of the week in minutes since 12:00 midnight Sunday
    WORD		wSettlementTime;	// time in minutes starting after wStoptime
    WORD		wDribbleTime : 15;	// time in minutes starting after wStoptime
    WORD		wReset : 1;			// signifies that this session is the end of day.

    bool operator==(const ORGS_SESSION_INFO & sess) const
    {
        return ( (wStartTime == sess.wStartTime) &&
                    (wStopTime == sess.wStopTime) &&
                    (wSettlementTime == sess.wSettlementTime) &&
                    (wDribbleTime == sess.wDribbleTime));
    }
    bool operator < (const ORGS_SESSION_INFO & sess) const { return wStartTime < sess.wStartTime; }
    ORGS_SESSION_INFO() : wStartTime(0), wStopTime(0), wSettlementTime(0), wDribbleTime(0), wReset(0) {}
    ORGS_SESSION_INFO(WORD start, WORD stop, WORD dribble, WORD settlement, WORD reset) :
        wStartTime(start), wStopTime(stop), wSettlementTime(settlement), wDribbleTime(dribble), wReset(reset)
    {
    }
};


struct ORGS_SESSION : public std::vector<ORGS_SESSION_INFO> {
    enum {ORGS_MAX_SESSIONS=256};

    void add_session(ORGS_SESSION_INFO& info) { push_back(info); }

    const ORGS_SESSION& operator=(const ORGS_SESSION& Ses) {
        assign(Ses.begin(), Ses.end());
        return *this;
    }
};


//
//  ExtSessions is the container class for parsing and generating different session definition
//  formats. An internal data model holds the session definition information for user application
//  to iterate through individual sessions at historical session / weekly / daily levels.
//
//  Currently, user can construct the ExtSessions instance from:
//      - Current generation session structure container (ORGS_SESSION)
//      - Current generation session strings
//      - Extended session string definition (https://confluence.tradestation.com/display/DN/Extended+Session+Descriptor+Design)
//        Only extended session version 1 is supported at the moment.
//
//  Source session information will be parsed and stored in OrgExtSessions internal data model.
//  From the data model, user can retrieve the following session definition output format from
//  an ExtSessions instance.
//      - Current generation session structure container (ORGS_SESSION)
//      - Current generation session strings
//      - Extended session string definition (https://confluence.tradestation.com/display/DN/Extended+Session+Descriptor+Design)
//        Only extended session version 1 is supported at the moment.
//
//  Also, user could construct the ExtSessions instance data model with the following components and
//  generate above session definition output formats as well.
//      - ExtSingleSession (individual sessions)
//      - ExtDailySession (all sessions for a trading day)
//      - ExtWeeklySession (current/historical session definition block, contains all sessions for a week)
//
//  Comparison operators(==) are provided at following session component level.
//      - ExtSessions
//      - ExtWeeklySession
//      - ExtDailySession
//      - ExtSingleSession
//
//  Examples:
//
//    From current generation session string:
//
//    /* create ExtSessions instance from current generation session string */
//    string strInSessionV0 =
//        string("20:") +
//        string("1260,1560,0,0,0;1980,2055,0,0,0;2070,2130,0,0,0;2250,2370,0,0,1;") +
//        string("2700,3000,0,0,0;3420,3495,0,0,0;3510,3570,0,0,0;3690,3810,0,0,1;") +
//        string("4140,4440,0,0,0;4860,4935,0,0,0;4950,5010,0,0,0;5130,5250,0,0,1;") +
//        string("5580,5880,0,0,0;6300,6375,0,0,0;6390,6450,0,0,0;6570,6690,0,0,1;") +
//        string("7020,7320,0,0,0;7740,7815,0,0,0;7830,7890,0,0,0;8010,8130,0,0,1");
//
//    ExtSessions sessionV0(strInSessionV0);
//    ORGS_SESSION v0OrgsSession;
//    string v0SessionStr, v1SessionStr;
//    if (sessionV0.isValid()) {
//        v0SessionStr = sessionV0.getString(0);        /* version 0 session format, no historical support */
//        v1SessionStr = sessionV0.getString(1);        /* version 1 session format, extended */
//        v0OrgsSession = sessionV0.getOrgsSession();   /* version 0 ORGS_SESSION container, no historical support */
//    }
//
//    /* create ExtSessions instance from ORGS_SESSION container (current generation) */
//    ExtSessions sessionV0Session(v0OrgsSession);
//    if (sessionV0OrgsSession.isValid()) {
//        v0SessionStr = sessionV0Session.getString(0);        /* version 0 session format, no historical support */
//        v1SessionStr = sessionV0Session.getString(1);        /* version 1 session format, extended */
//        v0OrgsSession = sessionV0Session.getOrgsSession();   /* version 0 ORGS_SESSION container, no historical support */
//    }
//
//    /* create ExtSessions instance from extended session string version 1*/
//    string strInSessionV0 =
//        string("v1") +
//        string("{") +
//        string("<4:8460,330,0,0,0,2;1980,75,0,0,0,2;2070,60,0,0,0,2;2250,120,0,0,1,2>") +
//        string("[2700,4140,5580,7020]<4:0,330,0,0,0,2;720,75,0,0,0,2;810,60,0,0,0,,2;990,120,0,0,1,2>") +
//        string("(*-2015/12/31)") +
//        string("}") +
//        string("{") +
//        string("<3:8460,150,0,0,0,2;1980,150,0,0,0,2;2250,120,0,0,1,2>") +
//        string("[2700,4140,5580,7020]<3:0,150,0,0,0,2;720,150,0,0,0,2;990,120,0,0,1,2>") +
//        string("(2016/01/01-*)") +
//        string("}");
//
//    ExtSessions sessionV1(strInSessionV1);
//    if (sessionV1.isValid()) {
//        v0SessionStr = sessionV1.getString(0);        /* version 0 session format, no historical support */
//        v1SessionStr = sessionV1.getString(1);        /* version 1 session format, extended */
//        v0OrgsSession = sessionV1.getOrgsSession();   /* version 0 ORGS_SESSION container, no historical support */
//    }
//


// extended session container common base
//
class ExtSessionsBase
{
public:
    typedef shared_ptr<ExtSessionsBase> ptr;
    enum { SESSION_VERSION_V0, SESSION_VERSION_V1 };

    enum TimeGlobals {
        MinutesInAWeek = 7*24*60,
        MinutesInADay  = 24*60,
        MinutesInHour  = 60,
        SecondsInHour  = 60*60,
        SecondsInADay  = 24*60*60,
        SecondsInAWeek = 24*60*60*7
    };

    enum TimeCounters {
        milliseconds,
        seconds,
        minutes,
        hours
    };

    enum WeekDay
    {
        Sunday = 0,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday
    };

    enum ResetType
    {
        ResetNone,
        ResetDaily,
        ResetWeekly,
        ResetMonthly
    };

    enum CommandTypes {
        command_apply_offset,       // adjust the sessions according to the new offset (minute-based) - specified within attributes value
        command_filter_dribble,     // remove dribble value from each session
        command_resolution_check    // verify if sessions are compatible with this resolution
    };

    enum SessionCounter {
        counter_sessions,
        counter_resets
    };

    enum Status {
        NotInAnyTimePeriod,
        InTimePeriodNotTrading,
        InSessionTimePeriod,
        InDribbleTimePeriod,
        InSettlementTimePeriod
    };

    enum StatusFlags {
        StatusFlagsUndefined = 0,

        // output flags
        PreviousSessionReset = 0x1,
        CurrentSessionReset = 0x2,
        AllowCrossSessionBars = 0x4,

        // input/output flags
        ApplyNoDribbleOffset = 0x10
    };

    enum ExtSessionFlags
    {
        EXTSESSION_NO_FLAG                 = 0,

        // bit flags
        EXTSESSION_ALLOW_CROSS_SESSION_BARS= 0x1
    };


    static const __time64_t min_date = __time64_t(0);
    static const __time64_t max_date = __time64_t(ULONG_MAX);

protected:
    ExtSessionsBase(void) { reset(); }
    virtual ~ExtSessionsBase(void) {}
    ExtSessionsBase(const ExtSessionsBase& obj) { valid_ = obj.valid_; }
    const ExtSessionsBase& operator=(const ExtSessionsBase& obj) {
        if (this == &obj)
            return *this;
        valid_=obj.valid_;
        return *this;
    }

public:
    virtual bool isValid() const { return valid_; }
    void setValid(bool val) { valid_ = val; }

    virtual const string getString(int version) const { return makeString(version); }

    virtual int getSessionCount(SessionCounter counter=counter_sessions) const { counter; return 0; }

    // helper methods
    int get_week_offset_in_seconds(const tm& tm_t) const {
        return static_cast<int>(((tm_t.tm_wday) * MinutesInADay)*60 + tm_t.tm_hour*SecondsInHour + tm_t.tm_min*60 + tm_t.tm_sec);
    }

    static __time64_t make_time(const tm& date_time);
    static tm apply_date_offset(const tm& date_time, int seconds);
    static WORD max_day(int month, int year);

    enum SessionTypes {
        regular_session             =0x0,
        crossing_sunday_session     =0x1,
        before_session              =0x2,

        inside_session              =0x4,
        inside_session_before       =0x8,
        inside_session_after        =0x10,
        inside_session_mask         = (inside_session | inside_session_before | inside_session_after),

        inside_dribble              =0x20,
        inside_settlement           =0x40,

        after_session               =0x80
    };

    static int within_session_range(int offset_t, int start, int end, int dribble, int settlement); // return Session Types bitflags
    static int calculate_session_offsets(int week_t, int session_start, int session_end, int dribble, int settlement, int& start_offset, int& end_offset);

protected:
    // parse single session string
    virtual bool parseString(const string&) { return false; }

    // generate single session string
    virtual const string makeString(int version) const;

    virtual const string makeStringV0() const = 0;
    virtual const string makeStringV1() const = 0;

    // reset local data
    virtual void reset() { valid_ = false; }

    // non-boost tokenizer
    void tokenizer(const string& datastr, const string& delimiters, vector<string>& tokens);

protected:
    bool valid_;
};


//  single session container
//
class ExtSingleSession : public ExtSessionsBase, public ORGS_SESSION_INFO
{
    friend class ExtDailySession;
public:
    typedef shared_ptr<ExtSingleSession> ptr;

public:
    // construct from text format session definition, versioning support
    ExtSingleSession(const string& datastr, int version, __time64_t offset) { reset(); valid_ = parseString(datastr, version, offset);  }

    // construct from session definition values
    ExtSingleSession(WORD start, WORD length, WORD dribble, WORD settlement, WORD reset, int flags=0) :
        ORGS_SESSION_INFO(start, start+length, dribble, settlement, reset), length_(length), flags_(flags)
    {
        valid_ = true;
    }

    // create empty single session instance
    ExtSingleSession() : ExtSessionsBase() { reset(); }

    virtual ~ExtSingleSession(void) {}

public:
    // accessors
    int getStartTime(TimeCounters tc=minutes) const { return (tc==seconds) ? wStartTime*60 : wStartTime; }
    int getStopTime(TimeCounters tc=minutes) const { return (tc==seconds) ? wStopTime*60 : wStopTime; }
    int getLength(TimeCounters tc=minutes) const { return (tc==seconds) ? length_*60 : length_; }
    int getSettlementTime(TimeCounters tc=minutes) const { return (tc==seconds) ? wSettlementTime*60 : wSettlementTime; }
    int getDribbleTime(TimeCounters tc=minutes) const { return (tc==seconds) ? wDribbleTime*60 : wDribbleTime; }
    int getAdjustedEndTime(TimeCounters tc=minutes) const { return getStopTime(tc) + max(getSettlementTime(tc), getDribbleTime(tc)); }
    WORD getReset() const { return wReset; }
    int  getFlags() const { return flags_; }

    void setStartTime(WORD val) { wStartTime = val; } // minutes
    void setStopTime(WORD val) { wStopTime = val; } // minutes
    void setLength(WORD val) { length_ = val; } // minutes
    void setSettlementTime(WORD val) { wSettlementTime = val; } // minutes
    void setDribbleTime(WORD val) { wDribbleTime = val; } // minutes
    void setReset(WORD val) { wReset = val; } // 0 or 1
    void setFlags(int flags) { flags_ = flags; } // ExtSessionFlags

    bool hasFlag(int flag) { return ((flags_ & flag)>0); }

    // operator overloads
    bool operator==(ExtSingleSession& session) const {
        if (length_ != session.length_) return false;
        if (flags_ != session.flags_) return false;
        return (*((ORGS_SESSION_INFO*)this) == *((ORGS_SESSION_INFO*)&session));
    }

protected:
    // parse single session string
    bool parseString(const string& datastr, int version, __time64_t offset) {
        if (!version) {
            // current generation session string format
            return parseSingleSessionStringV0(datastr, offset);
        }
        // extended session string format
        return parseSingleSessionStringExt(datastr, version, offset);
    }

    bool parseSingleSessionStringV0(const string& datastr, __time64_t offset);
    bool parseSingleSessionStringExt(const string& datastr, int version, __time64_t offset);

    // generate single session string (version support)
    const string makeStringV0(void) const;
    const string makeStringV1(void) const;

    void reset() { length_ = WORD(0); flags_ = EXTSESSION_NO_FLAG; }
    bool process_command(CommandTypes command, int attributes);

protected:
    WORD length_;
    unsigned long flags_;
};


//  daily session(s) container
//
class ExtDailySession : public ExtSessionsBase
{
    friend class ExtWeeklySession;
public:
    typedef shared_ptr<ExtDailySession> ptr;

public:
    ExtDailySession(const string& datastr, int version);
    ExtDailySession(const string& datastr, __time64_t offset, int version);
    virtual ~ExtDailySession(void) {}

    // create empty daily session instance
    ExtDailySession() : ExtSessionsBase() { reset(); }

    // copy constructor
    ExtDailySession(const ExtDailySession& obj);

    inline bool isValid() const;

public:
    vector<ExtSingleSession::ptr>& getSingleSessions() { return singleSessions; };

    void appendSingleSession(const ExtSingleSession::ptr singleSession) { singleSessions.push_back(singleSession); }

    //  day         - enum(Sunday/Monday/Tuesday/Wednesday/Thursday/Friday/Saturday)
    //  start       - examples: 930 (9:30am), 2130 (9:30pm)
    //  length      - length of session in minutes
    //  settlement  - length of settlement period in minutes
    //  dribble     - length of dribble period in minutes
    //  reset       - 0/1, 1 means last session of the trading day
    //  flag        - enum single session flag (ExtSessionFlags)
    void appendSingleSession(WeekDay day, WORD start, WORD length, WORD settlement, WORD dribble, WORD reset, int flag);

    // get total number of sessions
    int getSessionCount(SessionCounter counter) const {
        switch (counter) {
            case counter_sessions: return singleSessions.size();
        }
        return 0;
    }

    // operator overloads
    bool operator==(ExtDailySession& session) const;

public: // Session lookups

    int start_offset() const { return singleSessions.empty() ? 0 : singleSessions.front()->getStartTime(seconds); } // seconds
    int end_offset() const { return singleSessions.empty() ? 0 : singleSessions.back()->getStopTime(seconds); } // seconds
    int dribble() const { return singleSessions.empty() ? 0 : singleSessions.back()->getDribbleTime(seconds); } // seconds
    int settlement() const { return singleSessions.empty() ? 0 : singleSessions.back()->getSettlementTime(seconds); } // seconds

    int within_session(int offset_t, unsigned short flags=0) const;

    // Returns session with the reset within our daily sessions
    ExtSingleSession::ptr get_session_reset() const;


protected:
    // parse single session string
    bool parseString(const string& datastr, int version, __time64_t offset);

    // generate single session string (with version support)
    const string makeStringV0() const;
    const string makeStringV1() const;

    void reset() { singleSessions.clear(); }
    bool process_command(CommandTypes command, int attributes);

    bool get_session_info_none(const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const;
    bool get_session_info_daily(const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const;

    int calculate_daily_session_offsets(int week_t, unsigned short flags, int& start_offset, int& end_offset) const;
    bool calculate_bar_time(unsigned long seconds_span, const int week_t, int& bar_offset, int& end_offset) const;

private:
    Status get_session_status(const ResetType type, int offset_t, unsigned short& flags, ExtSingleSession::ptr * session_ptr=nullptr) const;

protected:
    vector<ExtSingleSession::ptr> singleSessions;
};


//  weekly session container
//
class ExtWeeklySession : public ExtSessionsBase
{
    friend class ExtSessions;

public:
    typedef shared_ptr<ExtWeeklySession> ptr;

public:
    ExtWeeklySession(const string& datastr, int version);
    virtual ~ExtWeeklySession(void) {}

    // create empty weekly session instance
    ExtWeeklySession() : ExtSessionsBase() { reset(); }

    // copy constructor
    ExtWeeklySession(const ExtWeeklySession& obj);

public:
    vector<ExtDailySession::ptr>& getDailySessions() { return dailySessions; };

    // retrieve ORGS_SESSION compatible session list
    const ORGS_SESSION& getOrgsSession();

    // effective session date range accessors
    __time64_t getStartDate() const { return start_date; }
    void setStartDate(__time64_t val) { start_date = val; }
    __time64_t getEndDate() const { return end_date; }
    void setEndDate(__time64_t val) { end_date = val; }

    bool within_date_range(__time64_t val) { return (val >= start_date) && (val < end_date); }

    // date string format:
    //           "*"  - Open date range start/stop
    //  "YYYY/MM/DD"  - Calendar date in GMT timezone
    void setStartDate(const string& datestr);
    void setEndDate(const string& datestr);

    // get total number of sessions
    int getSessionCount(SessionCounter counter=counter_sessions) const;

    // append single/repetitive day session(s)
    void appendDailySession(const ExtDailySession::ptr dailySession) { dailySessions.push_back(dailySession); }
    bool appendRepetitiveDaySessions(const string& daysession, const string& attrs, int version);

    // operator overloads
    bool operator==(ExtWeeklySession& sessions) const;

    // utility methods
    bool get_trading_day_hours(const int week_t, WORD& sHour, WORD& sMin, WORD& eHour, WORD& eMin) const;

public: // session lookups

    // Given a weekly-bound second-based time parameter - returns offset (in seconds) until the next/previous session start/end period
    bool get_previous_daily_reset(const int week_t, int& start_offset, int& end_offset) const;
    bool get_session_info(const ResetType type, const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const;
    bool calculate_bar_time(unsigned long seconds_span, const int week_t, int& bar_offset, int& end_offset) const;


protected:
    // parse single session string
    bool parseString(const string& datastr, int version);

    // generate single session string (with version support)
    const string makeStringV0() const;
    const string makeStringV1() const;

    // make effective date range string
    const string makeEffectiveDateRangeString() const;
    const string makeEffectiveDateStamp(__time64_t t) const;

    // parsing weekly session definition
    bool parseWeeklySessionString(const string& datastr, int version);

    // parsing session effective date range
    bool parseEffectiveDateRange(const string& datastr);

    // parsing current generation session string format
    bool parseWeeklySessionStringV0(const string& datastr);

    // parsing extended session string format
    bool parseWeeklySessionStringExt(const string& datastr, int version);

    // parsing extended session string date format
    bool parseSessionDateStr(const string& datastr, __time64_t& date_t, __time64_t default_t);

    // backward compatible - make session list of the week in ORGS_SESSION_INFO format
    void makeOrgsSession();

    void reset() { start_date = __time64_t(0); end_date = max_date; str_start_date = string("*"); str_end_date = string("*"); dailySessions.clear(); orgsSession.clear(); }

    enum session_placement { previous, next };
    ExtDailySession::ptr get_session(const ResetType type, const int week_t, unsigned short flags=ApplyNoDribbleOffset, session_placement position=next) const;

    bool get_session_info_none(const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const;
    bool get_session_info_daily(const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const;
    bool get_session_info_weekly(const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const;

    bool process_command(CommandTypes command, int attributes);

    bool calculate_previous_session_offsets(int week_t, int& start_offset, int& end_offset) const;

protected:
    // effective date range for the session definition
    __time64_t start_date, end_date;
    string str_start_date, str_end_date;

    vector<ExtDailySession::ptr> dailySessions;

    // session list in ORGS_SESSION format
    ORGS_SESSION orgsSession;
};


//  extended session container
//
class ExtSessions : public ExtSessionsBase
{
public:
    typedef shared_ptr<ExtSessions> ptr;

public:
    // construct data model from session string
    ExtSessions(const string& datastr);
    ExtSessions(const char* datastr);
    ExtSessions(const EXT_SESSION* sessions);

    // construct data model from ORGS_SESSION definition (backward compatible)
    ExtSessions(const ORGS_SESSION& sessions);

    // construct data model from SESSION_INFO structure
    ExtSessions(const SESSION_INFO* sessions);

    virtual ~ExtSessions(void) {}

    // create emtpy session instance
    ExtSessions() : ExtSessionsBase() { reset(); }

    // copy constructor
    ExtSessions(const ExtSessions& obj);
    const ExtSessions& operator=(const ExtSessions & obj);

public:
    // get data model
    vector<ExtWeeklySession::ptr>& getWeeklySessions() { return weeklySessions; }

    BYTE getTimezone() { return timezone_; }
    void setTimezone(BYTE tz) { timezone_ = tz; }
    int get_version() { return version_; }
    bool is_extended() { return (version_!=0); }
    bool is_resolution_compatible(int seconds) const;

    bool get_trading_day_hours(const tm& date_time, WORD& sHour, WORD& sMin, WORD& eHour, WORD& eMin) const;

    // backward compatible with ORG_SESSION for current generation session data
    // only return current active session definition
    const ORGS_SESSION& getOrgsSession();

    // return weekly session for certain timestamp
    vector<ExtWeeklySession::ptr>::iterator getWeeklySession(__time64_t start, PINT pindex = nullptr);

    // add weekly session definition to data model (current/historical)
    void appendWeeklySession(const ExtWeeklySession::ptr weeklySession) {
        // sort based on time
        for (auto it(weeklySessions.begin()); it!=weeklySessions.end(); ++it) {
            if ((*it)->getStartDate() > weeklySession->getStartDate()) {
                weeklySessions.insert(it, weeklySession);
                return;
            }
        }
        weeklySessions.push_back(weeklySession);
    }

    // operator overloads
    bool operator==(ExtSessions& sessions) const;

    // helper functions
    bool process_command(CommandTypes command, int attributes=0);
    int getSessionCount(SessionCounter counter=counter_sessions) const;

    // conversions to data model
    void set_session(const SESSION_INFO* sessions);
    void set_session(const ORGS_SESSION& sessions);

    // walk through week sessions, until we find our effective date range
    ExtWeeklySession::ptr get_current_session(const __time64_t date_time=max_date-1) const;


public: // session lookups

    // date_time expected to be in session's timezone - returns offset (in seconds) from given input until the next/previous session start/end
    bool get_session_info(const ResetType type, const tm& date_time, int& start_offset, int& end_offset) const {
        Status status(NotInAnyTimePeriod); unsigned short flags(ApplyNoDribbleOffset);
        return get_session_info(type, date_time, start_offset, end_offset, status, flags);
    }
    bool get_session_info(const ResetType type, const tm& date_time, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const;
    bool get_previous_daily_reset(const tm& date_time, int& start_offset, int& end_offset) const;

    // Calculate the bar time based on the seconds resolution and data point's date/time, returning the offset to bar close & session end
    bool calculate_bar_time(unsigned long seconds_span, const tm& date_time, int& bar_offset, int& end_offset) const;

protected:
    // parse single session string
    bool parseString(const string& datastr);
    bool parseString(const char* datastr);

    // generate single session string (version support)
    const string makeStringV0() const;
    const string makeStringV1() const;

    // initialization
    void reset() {
        weeklySessions.clear();
        timezone_ = 0xff;    // TZINFO_DEFAULT, no timezone information available
    }

    // utilities
    WORD convertSessionTime(short session_time);

    void adjust_date_range(); // make the effective date ranges consecutive to prevent gaps

    bool get_session_info_monthly(const tm& date_time, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const;

protected:
    // list of session definitions
    vector<ExtWeeklySession::ptr> weeklySessions;

    // timezone identifer
    BYTE timezone_;
    int version_;
};


//
// Base
//

inline const string ExtSessionsBase::makeString(int version) const {
    if (isValid() == false)
        return string();

    // make session string on-demand
    switch (version)
    {
        case 0: return makeStringV0();
        case 1: return makeStringV1();
        default: break;     // assertion check happens at session string map validation below.
    };
    return string();
}


inline void ExtSessionsBase::tokenizer(const string& datastr, const string& delimiters, vector<string>& tokens)
{
    tokens.clear();
    if (datastr.empty())
        return;

    auto lastPos = datastr.find_first_not_of(delimiters, 0);
    auto pos = datastr.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos) {
        tokens.push_back(datastr.substr(lastPos, pos - lastPos));
        lastPos = datastr.find_first_not_of(delimiters, pos);
        pos = datastr.find_first_of(delimiters, lastPos);
    }
}


inline __time64_t ExtSessionsBase::make_time(const tm& date_time)
{
    struct tm tm_copy(date_time);

    // Range acceptable is 1970+ - anything below will fail with -1 ... treat as 0 for effective date range purposes...
    __time64_t t = _mkgmtime64(&tm_copy);
    if (t < min_date) t = min_date;
    else if (t > max_date) t = max_date;

    return t;
}

inline tm ExtSessionsBase::apply_date_offset(const tm& date_time, int seconds) {
    // Typically, this involves adding/substracting seconds from a given date time value
    tm new_date(date_time);
    auto t = _mkgmtime64(&new_date);
    t += seconds;
    _gmtime64_s(&new_date, &t);
    return new_date;
}


inline WORD ExtSessionsBase::max_day(int month, int year) {
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;

    if(month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    // February special leap year handling
    if(year % 4 == 0) {
        if(year % 100 == 0) {
            if(year % 400 == 0)
                return 29;
            return 28;
        }
        return 29;
    }
    return 28;
}

inline int ExtSessionsBase::within_session_range(int offset_t, int start, int end, int dribble, int settlement) {
    int end_adj = max(dribble, settlement);

    if (end < start) {
        // session crossing weekly threshold (ex. Friday to Monday)
        if (offset_t >= start) {
            return crossing_sunday_session | inside_session_before;
        }
        if (offset_t < end+end_adj) {
            if (offset_t >= end) {
                if (offset_t < end+dribble)
                    return crossing_sunday_session | inside_session_after | inside_dribble;
                // in settlement
                return crossing_sunday_session | inside_session_after | inside_settlement;
            }
            return crossing_sunday_session | inside_session_after;
        }
        // evaluate distance between start/end times
        if (abs(offset_t - start) < abs(offset_t - (end+end_adj)))
            return crossing_sunday_session | before_session;

        return crossing_sunday_session | after_session;
    }

    // regular weekly session (ex. Monday 9AM to 4PM)
    if (offset_t >= start) {
        if (offset_t < end + end_adj) {
            if (offset_t >= end) {
                if (offset_t < end+dribble)
                    return inside_session | inside_dribble;
                // in settlement
                return inside_session | inside_settlement;
            }
            return inside_session;
        }
        return after_session;
    }
    return before_session;
}



// Adjust next (or current) start/end session distance based on offset!
inline int ExtSessionsBase::calculate_session_offsets(int offset_t, int session_start, int session_end, int dribble, int settlement, int& start, int& end)
{
    start = session_start;
    end = session_end;

    auto session_type = within_session_range(offset_t, start, end, dribble, settlement);

    if (session_type & crossing_sunday_session) {
        // session crossing weekly threshold (ex. Friday to Monday)
        if (session_type & (inside_session_before | after_session | before_session)) {
            // offset_t is within session (ex. offset=Saturday)
            // after/before session (ex. offset = anywhere in the week - prior to start) - we do not go backwards (interested next session only)
            start -= offset_t;
            end += (SecondsInAWeek-offset_t); // ending value needs to cross over to next week!
        }
        else {
            if (!(session_type & inside_session_after)) {
                assert(false);
                return 0;
            }
            start -= (SecondsInAWeek + offset_t); // starting value needs to cross over to previous week!
            end -= offset_t;
        }
    }
    else {
        if (session_type & (inside_session_mask | before_session)) {
            // before or within session - simply substract our offsets
            start -= offset_t;
            end -= offset_t;
        }
        else if (session_type & after_session) {
            // ahead of the session ... need to cross over to next week!
            start += (SecondsInAWeek-offset_t);
            end += (SecondsInAWeek-offset_t);
        }
    }
    return session_type;
}

//
// Sessions
//

inline ExtSessions::ExtSessions(const string& datastr)
{
    reset();
    valid_ = parseString(datastr);
}

inline ExtSessions::ExtSessions(const char* datastr)
{
    if (!datastr) { valid_ = false; return; }
    reset();
    valid_ = parseString(datastr);
}

inline ExtSessions::ExtSessions(const EXT_SESSION* session)
{
    if (!session) { valid_ = false; return; }
    reset();
    valid_ = parseString(session->c_str());
}

inline ExtSessions::ExtSessions(const ExtSessions& obj) : ExtSessionsBase(obj)
{
    weeklySessions = obj.weeklySessions;
    timezone_ = obj.timezone_;
    version_ = obj.version_;
}

inline const ExtSessions& ExtSessions::operator=(const ExtSessions & obj) {
    if (this == &obj)
        return *this;

    ExtSessionsBase::operator=(obj);

    weeklySessions = obj.weeklySessions;
    timezone_ = obj.timezone_;
    version_ = obj.version_;
    return *this;
}


inline ExtSessions::ExtSessions(const SESSION_INFO* sessions)
{
    if (!sessions) { valid_ = false; return; }
    reset();
    set_session(sessions);
}


inline ExtSessions::ExtSessions(const ORGS_SESSION& sessions)
{
    reset();
    set_session(sessions);
}



inline bool ExtSessions::parseString(const string& datastr)
{
    return parseString(datastr.c_str());
}


inline bool ExtSessions::parseString(const char* datastr)
{
    string str = datastr;
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());

    vector<string> tokens;
    tokenizer(str, "{}", tokens);
    if (tokens.empty())
        return false; // empty session string

    auto token(tokens.begin());

    //  versions:
    //      0  - session string based on SESSION_INFO
    //      1+ - extended session string definition
    version_ = 0;
    const char* p = token->c_str();

    // parse version information
    if (*p == 'v') {
        // get version number
        version_ = atoi(p + 1);
    }

    // get timezone information for the extended session string
    if (version_ > 0) {
        if (++token == tokens.end())
            return false;   // timezone token missing

        timezone_ = BYTE(atoi(token->c_str()));

        // iterate through current/historical session blocks
        if (++token == tokens.end())
            return false;
    }

    for (; token != tokens.end(); ++token) {
        ExtWeeklySession::ptr weeklySession(new ExtWeeklySession(*token, version_));
        if (!weeklySession->isValid())
            return false;
        appendWeeklySession(weeklySession);
    }

    adjust_date_range();
    return true;
}



inline const string ExtSessions::makeStringV0() const
{
    // for SESSION_INFO based session string, we only support current session block
    // the "Current" session block must have open ending attribute.
    ExtWeeklySession::ptr current_session;
    for each (auto& weekly_session in weeklySessions) {
        if (weekly_session->getEndDate() == max_date) {
            current_session = weekly_session;
            break;
        }
    }

    if (!current_session)
        assert(false);  // we should not be here

    ostringstream sstr;

    // insert session count
    int session_count = current_session->getSessionCount();
    sstr << session_count << ":";

    // insert session block
    sstr << current_session->getString(SESSION_VERSION_V0);
    return sstr.str();
}


inline const string ExtSessions::makeStringV1() const
{
    ostringstream sstr;

    // insert version
    sstr << "{v1}";

    // insert timezone tag
    sstr << "{" << int(timezone_) << "}";

    // insert current/historical blocks
    for each (auto& weekly_session in weeklySessions) {
        sstr << string("{") + weekly_session->getString(SESSION_VERSION_V1) + string("}");
    }
    return sstr.str();
}


inline bool ExtSessions::is_resolution_compatible(int seconds) const
{
    ExtWeeklySession::ptr current_session(get_current_session());

    if (!current_session)
        assert(false);  // we should not be here

    return current_session->process_command(command_resolution_check, seconds);
}


inline bool ExtSessions::get_trading_day_hours(const tm& date_time, WORD& sHour, WORD& sMin, WORD& eHour, WORD& eMin) const
{
    ExtWeeklySession::ptr current_session(get_current_session());
    if (!current_session) {
        assert(false);  // we should not be here
        return false;
    }
    auto week_t = get_week_offset_in_seconds(date_time);
    return current_session->get_trading_day_hours(week_t, sHour, sMin, eHour, eMin);
}



inline const ORGS_SESSION& ExtSessions::getOrgsSession()
{
    static ORGS_SESSION empty_session;
    if (!valid_) return empty_session;

    // for SESSION_INFO based session string, we only support current session block
    // the "Current" session block must have open ending attribute.
    ExtWeeklySession::ptr current_session(get_current_session());

    if (!current_session)
        assert(false);  // we should not be here

    return current_session->getOrgsSession();
}

inline vector<ExtWeeklySession::ptr>::iterator ExtSessions::getWeeklySession(__time64_t start, PINT pindex)
{
    auto& sarray = getWeeklySessions();
    for (auto weekly_it = sarray.begin(); weekly_it != sarray.end(); weekly_it++) {
        auto weekly_session = *weekly_it;
        __time64_t t1 = weekly_session->getStartDate();
        __time64_t t2 = weekly_session->getEndDate();
        if (start >= t1 && start <= t2) {
            if (pindex) *pindex = std::distance(sarray.begin(), weekly_it);
            return weekly_it;
        }
    }
    if (pindex) *pindex = -1;
    return sarray.end();
}

inline bool ExtSessions::operator==(ExtSessions& sessions) const
{
    if (weeklySessions.size() != sessions.weeklySessions.size())
        return false;

    // the order of the single session could be random in the data model
    for (auto lhs(weeklySessions.begin()); lhs != weeklySessions.end(); lhs++) {
        auto rhs(sessions.getWeeklySessions().begin());
        for (; rhs != sessions.getWeeklySessions().end(); rhs++) {
            if (*lhs->get() == *rhs->get())
                break;
        }
        if (rhs == sessions.getWeeklySessions().end())
            return false; // we didn't find the session
    }
    return true;
}


inline void ExtSessions::set_session(const SESSION_INFO* sessions)
{
    if (!sessions)
        return;

    timezone_ = sessions->chTimeZone;

    ExtWeeklySession::ptr weekly;

    ExtDailySession::ptr daily[7];
    for (int i = 0; i < 7; i++)
        daily[i] = ExtDailySession::ptr(new ExtDailySession);

    ExtSingleSession::ptr single;

    /*  NOTE: there is no information for settlement minutes. user application needs to data fill if necessary. */

    // iterate through possible trading days
    for (int week_day(Sunday); week_day <= Saturday ; ++week_day) {
        for (int i=0; i < NUM_SESSIONS; i++) {
            if (!sessions->bSession[i]) continue;

            bool valid_session = false;
            switch (week_day) {
                case Sunday: valid_session = TRADESSUN(sessions->tradeDays[i]); break;
                case Monday: valid_session = TRADESMON(sessions->tradeDays[i]); break;
                case Tuesday: valid_session = TRADESTUES(sessions->tradeDays[i]); break;
                case Wednesday: valid_session = TRADESWED(sessions->tradeDays[i]); break;
                case Thursday: valid_session = TRADESTHUR(sessions->tradeDays[i]); break;
                case Friday: valid_session = TRADESFRI(sessions->tradeDays[i]); break;
                case Saturday: valid_session = TRADESSAT(sessions->tradeDays[i]); break;
            }

            if (valid_session) {
                single.reset(new ExtSingleSession);
                single->setValid(true);
                single->setStartTime(static_cast<WORD>(convertSessionTime(sessions->sStartTime[i]) + (week_day*MinutesInADay)));
                single->setStopTime(static_cast<WORD>(convertSessionTime(sessions->sEndTime[i]) + (week_day*MinutesInADay)));

                if (sessions->bIsFirstSessionSameDay && (single->getStartTime()>single->getStopTime())) {
                    assert(false);
                    const_cast<SESSION_INFO*>(sessions)->bIsFirstSessionSameDay = false;
                }
                single->setLength(static_cast<WORD>(single->getStopTime() - single->getStartTime())); // adjusted below for crossing midnight sessions
                single->setReset(((i == (NUM_SESSIONS - 1)) || !sessions->bSession[i + 1])? 1 : 0);
                single->setDribbleTime((sessions->sStartTime[i] == sessions->sEndTime[i]) ? 0 : sessions->chMinutesPast);
                daily[week_day]->getSingleSessions().push_back(single);
            }
        }
    }

    // construct data model
    weekly.reset(new ExtWeeklySession);
    for (int i = 0; i < 7; i++) {
        // adjust first session start time
        if (daily[i]->getSingleSessions().size() > 0) {
            if (!sessions->bIsFirstSessionSameDay) {
                // adjust the first session to start on previous day
                ExtSingleSession::ptr session = daily[i]->getSingleSessions().front();
                if (session->getStartTime() < MinutesInADay) {
                    // previous week
                    session->setStartTime(static_cast<WORD>(MinutesInAWeek - (MinutesInADay - session->getStartTime())));
                    session->setLength(static_cast<WORD>((MinutesInAWeek - session->getStartTime()) + session->getStopTime()));
                }
                else {
                    session->setStartTime(static_cast<WORD>(session->getStartTime() - MinutesInADay));
                    session->setLength(static_cast<WORD>(session->getStopTime() - session->getStartTime()));
                }
            }
        }
        if (daily[i]->getSingleSessions().size() > 0) {
            daily[i]->setValid(true);
            weekly->appendDailySession(daily[i]);
        }
    }
    if (weekly->getDailySessions().size() > 0) {
        weekly->setValid(true);
        weekly->setStartDate(min_date);
        weekly->setEndDate(max_date);
        appendWeeklySession(weekly);
        setValid(true);
    }
}


inline void ExtSessions::set_session(const ORGS_SESSION& sessions)
{
    //
    //  Assumption:
    //      - sessions contained by ORGS_SESSION is not sorted
    //      - sessions contained by ORGS_SESSIONS is sortable by session starting offset
    //
    ORGS_SESSION valsessions = sessions;
    sort(valsessions.begin(), valsessions.end());

    // create transitional session string for parsing
    ostringstream sstr;

    sstr << valsessions.size() << ":";
    for (auto it_sess(valsessions.begin()); it_sess != valsessions.end(); it_sess++) {
        sstr << ((it_sess != valsessions.begin()) ? ";" : "") << it_sess->wStartTime << "," << it_sess->wStopTime << "," << it_sess->wSettlementTime << ","
            << it_sess->wDribbleTime << "," << it_sess->wReset;
    }
    // init session instances from session string
    valid_ = parseString(sstr.str());
}


inline bool ExtSessions::process_command(CommandTypes command, int attributes)
{
    for each(auto& week_session in weeklySessions) {
        if (!week_session->process_command(command, attributes))
            return false;
    }
    return true;
}


inline int ExtSessions::getSessionCount(SessionCounter counter) const {
    ExtWeeklySession::ptr current_session(get_current_session());

    if (!current_session)
        return 0;

    return current_session->getSessionCount(counter);
}


inline ExtWeeklySession::ptr ExtSessions::get_current_session(const __time64_t date_time) const {
    for each (auto& week_session in weeklySessions) {
        if (week_session->within_date_range(date_time))
            return week_session;
    }
    return ExtWeeklySession::ptr();
}


inline WORD ExtSessions::convertSessionTime(short session_time)
{
    WORD wHour = WORD(session_time & 0xFF00) >> 8;
    return (WORD)((wHour * 60) + (session_time & 0x00ff));
}


inline void ExtSessions::adjust_date_range()
{
    if (weeklySessions.size() > 0) {
        const string wildcard = "*";
        weeklySessions.front()->setStartDate(wildcard);
        weeklySessions.back()->setEndDate(wildcard);
    }

    if (weeklySessions.size() <= 1)
        return;

    __time64_t last_end(0);
    for each (auto& item in weeklySessions) {
        if (last_end) {
            item->setStartDate(last_end);
        }
        else {
            last_end = item->getEndDate();
        }
    }
}


// Find the next session block containing a reset based on the given date/time parameter, returning the offset from this parameter to the next session period
inline bool ExtSessions::get_session_info(const ResetType type, const tm& date_time, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const
{
    if (!valid_ || weeklySessions.empty())
        return false;

    auto week_t = get_week_offset_in_seconds(date_time);

    switch (type) {
        case ResetMonthly: // special case
            if (!get_session_info_monthly(date_time, start_offset, end_offset, status, flags))
                return false;
            break;

        default:
        {
            auto current_session = get_current_session(make_time(date_time));
            if (!current_session) {
                assert(false);  // we should always have a week session covering date range!
                return false;
            }

            // figure out the current time within our session week
            if (!current_session->get_session_info(type, week_t, start_offset, end_offset, status, flags))
                return false;
        }
        break;
    }

    switch (type) {
        case ResetWeekly:
        case ResetMonthly: // special case for status handling
            if (status == NotInAnyTimePeriod) {
                // special case - if datetime within start/end offset - consider InTimePeriodNotTrading
                if (start_offset<=0 && end_offset>0)
                    status = InTimePeriodNotTrading;
            }
            flags |= CurrentSessionReset | PreviousSessionReset;
            break;

        case ResetDaily:
            flags |= PreviousSessionReset;
            break;
    }
    return true;
}


// Find the previous session block containing a reset based on the given date/time parameter, returning the offset from this parameter to the previous session period
inline bool ExtSessions::get_previous_daily_reset(const tm& date_time, int& start_offset, int& end_offset) const
{
    if (!valid_ || weeklySessions.empty())
        return false;

    auto current_session = get_current_session(make_time(date_time));
    if (!current_session) {
        assert(false);  // we should always have a week session covering date range!
        return false;
    }

    // figure out the current time within our session week
    auto week_t = get_week_offset_in_seconds(date_time);
    return current_session->get_previous_daily_reset(week_t, start_offset, end_offset);
}


// Calculate the bar time based on the seconds resolution and date_time, returning the offset to bar close & session end
inline bool ExtSessions::calculate_bar_time(unsigned long seconds_span, const tm& date_time, int& bar_offset, int& end_offset) const
{
    if (!valid_ || weeklySessions.empty() || !seconds_span || (seconds_span > SecondsInADay))
        return false;

    // assuming date_time is within session boundaries
    auto current_session = get_current_session(make_time(date_time));
    if (!current_session) {
        assert(false);  // we should always have a week session covering date range!
        return false;
    }

    // figure out the current time within our session week
    auto week_t = get_week_offset_in_seconds(date_time);
    return current_session->calculate_bar_time(seconds_span, week_t, bar_offset, end_offset);
}



// We need to find the next (or current) monthly session start/end offsets!
// start of first day that has close within the month.
// stop of last complete trading day within the month.
inline bool ExtSessions::get_session_info_monthly(const tm& date_time, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const
{
    static const double var_date_seconds = 1 / double(SecondsInADay);
    if (!valid_ || weeklySessions.empty())
        return false;

    auto last_day_of_month = max_day(date_time.tm_mon+1, date_time.tm_year+1900);
    int seconds_from_next_month = SecondsInADay - ((date_time.tm_hour*SecondsInHour) + (date_time.tm_min*60) + date_time.tm_sec) + SecondsInADay * (last_day_of_month - date_time.tm_mday);

    // grab the next daily reset - from our current date time
    get_session_info(ResetDaily, date_time, start_offset, end_offset, status, flags);

    // verify if our next reset occurs in the next month - if so, our next monthly reset is also in the next month
    Status unused_status;
    if (end_offset >= seconds_from_next_month) {
        int offset = end_offset;

        tm next_month_date(apply_date_offset(date_time, offset));
        if (!get_session_info_monthly(next_month_date, start_offset, end_offset, unused_status, flags))
            return false;

        // need to adjust offset based on additional days pushed forward
        start_offset += offset;
        end_offset += offset;
        return true;
    }

    int unused_end_offset(0), unused_start_offset(0);

    // find start of the month offset
    int bom_offset = (1-date_time.tm_mday)*SecondsInADay - (date_time.tm_hour*SecondsInHour) - (date_time.tm_min*60) - (date_time.tm_sec);
    tm bom_date(apply_date_offset(date_time, bom_offset));
    if (!get_session_info(ResetDaily, bom_date, start_offset, unused_end_offset, unused_status, flags))
        return false;

    start_offset += bom_offset;

    // find end of the month offset
    if (date_time.tm_mday == last_day_of_month) {
        // our current date is on the last day of the month - and the reset is also within this month ...
        return true;
    }

    // We will start at the last day of the month, and work our way backwards, until we find the very last reset of the month!
    seconds_from_next_month = SecondsInADay - ((date_time.tm_hour*SecondsInHour) + (date_time.tm_min*60) + date_time.tm_sec);

    // Setup our last day of the month, including day of the week ...
    tm eom_date(apply_date_offset(date_time, (last_day_of_month-date_time.tm_mday)*SecondsInADay));

    for (; eom_date.tm_mday>=date_time.tm_mday; eom_date.tm_mday--) {
        if (!get_session_info(ResetDaily, eom_date, unused_start_offset, end_offset, unused_status, flags))
            return false;
        if (end_offset < seconds_from_next_month)
            break;

        if (eom_date.tm_wday)
            --eom_date.tm_wday;
        else
            eom_date.tm_wday = 6;

        seconds_from_next_month+=SecondsInADay;
    }

    // adjust offset by difference in days
    end_offset += (eom_date.tm_mday - date_time.tm_mday)*SecondsInADay;
    assert(eom_date.tm_mday>=date_time.tm_mday);
    return true;
}


//
// Weekly
//
inline ExtWeeklySession::ExtWeeklySession(const string& datastr, int version)
{
    reset();

    // initialize weekly session instance from weekly session string
    valid_ = parseString(datastr, version);
}


inline void ExtWeeklySession::setStartDate(const string& datestr)
{
    __time64_t date_t(0);
    str_start_date = datestr;
    parseSessionDateStr(datestr, date_t, __time64_t(0));
    setStartDate(date_t);
}


inline void ExtWeeklySession::setEndDate(const string& datestr)
{
    __time64_t date_t(0);
    str_end_date = datestr;
    parseSessionDateStr(datestr, date_t, max_date);
    setEndDate(date_t);
}


inline bool ExtWeeklySession::parseString(const string& datastr, int version)
{
    vector<string> tokens;
    tokenizer(datastr, "()", tokens);
    if (tokens.empty())
        return false;

    auto token(tokens.begin());
    if (!parseWeeklySessionString(*token, version))
        return false;

    // setup default date ranges
    start_date = min_date;
    end_date = max_date;

    // effective date range only applies to extended session definition versions
    if ((version > 0) && (++token != tokens.end())) {
        // validate date range
        return parseEffectiveDateRange(*token);
    }
    return true;
}


inline bool ExtWeeklySession::parseWeeklySessionString(const string& datastr, int version)
{
    if (!version) {
        // current generation session string format
        return parseWeeklySessionStringV0(datastr);
    }
    // extended session string format
    return parseWeeklySessionStringExt(datastr, version);
}

inline bool ExtWeeklySession::parseEffectiveDateRange(const string& datastr)
{
    vector<string> tokens;
    tokenizer(datastr, "-", tokens);
    if (tokens.empty())
        return false;

    auto token(tokens.begin());

    // parse start date
    str_start_date = *token;
    if (!parseSessionDateStr(*token, start_date, __time64_t(0)))
        return false;

    // parse end date
    if (++token == tokens.end())
        return false;

    str_end_date = *token;
    return parseSessionDateStr(*token, end_date, max_date);
}


inline bool ExtWeeklySession::parseSessionDateStr(const string& datastr, __time64_t& date_t, __time64_t default_t)
{
    // value of default parameter indicates start/end setup
    if (datastr.empty())
        return false;

    const char* p = datastr.c_str();
    if (*p == '*')
        date_t = default_t;
    else {
        int year, month, day;
        if (sscanf_s(p, "%d/%d/%d", &year, &month, &day) != 3)
            return false;

        struct tm d; memset(&d, 0, sizeof(d));
        d.tm_year = year - 1900, d.tm_mon = month - 1, d.tm_mday = day;
        if (default_t) {
            // ending date - make sure to include daily hours - adjust to end of day
            d.tm_hour = 23; d.tm_min = 59; d.tm_sec = 59;
        }

        date_t = _mkgmtime64(&d);

        if (default_t) {
            // adjust the end to last valid session
            int start_offset(0), end_offset(0);
            auto week_t = get_week_offset_in_seconds(d);
            get_previous_daily_reset(week_t, start_offset, end_offset);
            date_t += end_offset;
        }
    }
    return true;
}


inline bool ExtWeeklySession::parseWeeklySessionStringV0(const string& datastr)
{
    // remove the number of session field
    vector<string> tokens;
    tokenizer(datastr, ":", tokens);
    if (tokens.empty())
        return false;

    // get the number of sessions
    auto token(tokens.begin());
    unsigned int num_sessions = atoi(token->c_str());
    if (++token == tokens.end())
        return false;

    string strWeeklySessions(*token);

    // building day sessions
    vector<string> day_tokens;
    tokenizer(strWeeklySessions, ";", day_tokens);
    if (num_sessions != day_tokens.size())
        return false;

    const char daily_reset('1');
    ExtDailySession::ptr daysession;

    for (auto day_token(day_tokens.begin()); day_token != day_tokens.end(); ++day_token) {
        if (day_token->back() == daily_reset) {
            // single-session reset flag
            daysession.reset(new ExtDailySession(*day_token, 0));
        }
        else {
            // multiple-sessions within same day - combine them
            string strDay (*day_token);
            while ((day_token->back() != daily_reset) && (++day_token != day_tokens.end())) {
                strDay += ";"; strDay += *day_token;
            }
            if (day_token == day_tokens.end())
                return false; // did not find daily_reset

            daysession.reset(new ExtDailySession(strDay, 0));
        }
        if (!daysession->isValid())
            return false;
        appendDailySession(daysession);
    }
    return true;
}


inline bool ExtWeeklySession::appendRepetitiveDaySessions(const string& daysession, const string& attrs, int version)
{
    if (attrs.empty())
        return false;

    // iterate through repetitive offset attributes
    vector<string> tokens;
    tokenizer(attrs, ",", tokens);

    for (auto token(tokens.begin()); token != tokens.end(); token++) {
        ExtDailySession::ptr daysession(new ExtDailySession(daysession, __time64_t(atoi(token->c_str())), version));
        if (!daysession->isValid())
            return false;
        appendDailySession(daysession);
    }
    return true;
}


inline void ExtDailySession::appendSingleSession(WeekDay day, WORD start, WORD length, WORD settlement, WORD dribble, WORD reset, int flag)
{
    ExtSingleSession::ptr single(new ExtSingleSession);
    single->setValid(true);

    WORD offset = static_cast<WORD>((day - Sunday)*MinutesInADay + (start/100)*60 + (start%100));

    single->setStartTime(offset);
    single->setLength(length);
    single->setStopTime((offset + length) % 10080); // wrap on weekly boundary
    single->setSettlementTime(settlement);
    single->setDribbleTime(dribble);
    single->setReset(reset);
    single->setFlags(flag);

    appendSingleSession(single);
}


inline bool ExtWeeklySession::parseWeeklySessionStringExt(const string& datastr, int version)
{
    // TODO: we should build a parsing function map based on version numbers
    //       for now, by default we are parsing extended session string format version 1.

    vector<string> tokens;
    tokenizer(datastr, ">", tokens);

    if (tokens.empty())
        return false;

    // iterate through day sessions
    for (auto tok_iter(tokens.begin()); tok_iter != tokens.end(); tok_iter++) {
        const string& str_tok = *tok_iter;

        // check if repetitive attributes are available
        bool hasAttrs = (str_tok.front() == '[');

        if (!hasAttrs) {
            // single day session
            ExtDailySession::ptr daysession_ptr(new ExtDailySession(str_tok.substr(1), version));
            if (!daysession_ptr->isValid())
                return false;
            appendDailySession(daysession_ptr);
        }
        else {
            vector<string> attr_tokens;
            tokenizer(str_tok, "[]<>", attr_tokens);
            if (attr_tokens.size()<2)
                return false;

            auto attributes(attr_tokens.begin());
            auto day_session(attr_tokens.begin()+1);

            // day session with repetitive attributes
            if (!appendRepetitiveDaySessions(*day_session, *attributes, version))
                return false;
        }
    }
    return true;
}


inline int ExtWeeklySession::getSessionCount(SessionCounter counter) const
{
    int count = 0;

    switch (counter) {
        case counter_resets:
            return dailySessions.size();

        default:
            for each (auto& daily_session in dailySessions) {
                count += daily_session->getSessionCount(counter);
            }
    }
    return count;
}


inline const string ExtWeeklySession::makeStringV0() const
{
    //
    // Supported Version: Current Generate Session Definition Version 0
    //
    assert(dailySessions.size() > 0);

    ostringstream sstr;
    for each (auto& daily_session in dailySessions) {
        sstr << daily_session->getString(SESSION_VERSION_V0);
    }
    string strWeekly = sstr.str();
    if (strWeekly.size() > 0)
        strWeekly.pop_back(); // removing last delimiter

    return strWeekly;
}


inline const string ExtWeeklySession::makeStringV1() const
{
    // insert weekly block
    ostringstream sstr;
    for each (auto& daily_session in dailySessions) {
        string strWeekly = daily_session->getString(SESSION_VERSION_V1);
        if (strWeekly.size() > 0)
            strWeekly.pop_back(); // removing last delimiter
        sstr << "<" << strWeekly << ">";
    }

    // insert effective date range
    sstr << "(" << makeEffectiveDateRangeString() << ")";
    return sstr.str();
}


inline const string ExtWeeklySession::makeEffectiveDateRangeString() const
{
    ostringstream rangeStr;
    rangeStr << str_start_date << "-" << str_end_date;
    //rangeStr << makeEffectiveDateStamp(getStartDate()) << "-" << makeEffectiveDateStamp(getEndDate());
    return rangeStr.str();
}

inline const string ExtWeeklySession::makeEffectiveDateStamp(__time64_t t) const
{
    if (t == min_date || t == max_date)
        return string("*");

    struct tm gmt_tm;
    _gmtime64_s(&gmt_tm, &t);

    ostringstream sstr;
    sstr << setfill('0') << setw(4) << gmt_tm.tm_year + 1900;
    sstr << "/";
    sstr << setfill('0') << setw(2) << gmt_tm.tm_mon + 1;
    sstr << "/";
    sstr << setfill('0') << setw(2) << gmt_tm.tm_mday;
    return sstr.str();
}


inline const ORGS_SESSION& ExtWeeklySession::getOrgsSession()
{
    if (!orgsSession.empty())
        return orgsSession;

    makeOrgsSession();

    // empty ORGS_SESSION_INFO vector will be returned if the data model is invalid
    return orgsSession;
}

inline void ExtWeeklySession::makeOrgsSession()
{
    assert(valid_);

    orgsSession.clear();
    for each (auto& daily_session in dailySessions) {
        auto & single_sessions = daily_session->getSingleSessions();
        for each (auto& single_session in single_sessions) {
            orgsSession.add_session(*(single_session.get()));
        }
    }
}

inline bool ExtWeeklySession::get_trading_day_hours(const int week_t, WORD& sHour, WORD& sMin, WORD& eHour, WORD& eMin) const
{
    sHour = sMin = eHour = eMin = 0;

    auto daily_ptr(get_session(ResetDaily, week_t));
    if (!daily_ptr)
        return false;

    auto start_t = daily_ptr->start_offset()/60; // in minutes
    auto end_t = daily_ptr->end_offset()/60;

    sHour = (start_t % MinutesInADay) / 60;
    sMin = (start_t % MinutesInADay) % 60;
    eHour = (end_t % MinutesInADay) / 60;
    eMin = (end_t % MinutesInADay) % 60;
    return true;
}



inline ExtDailySession::ptr ExtWeeklySession::get_session(const ResetType type, const int week_t, unsigned short flags, session_placement position) const
{
    int prev_end_offset = 0;
    auto day_session_it(dailySessions.begin());

    // walk through daily sessions until we find our target period
    for (; day_session_it != dailySessions.end(); ++day_session_it) {

        if ((*day_session_it)->within_session(week_t, flags) & inside_session_mask)
            break;

        // verify if in-between sessions
        auto current_end_offset = (*day_session_it)->end_offset();
        if (!(flags & ApplyNoDribbleOffset))
            current_end_offset += max((*day_session_it)->dribble(), (*day_session_it)->settlement());

        if (prev_end_offset) {
            if ((week_t>=prev_end_offset) && (week_t<current_end_offset))
                break;

            // we could be in a session crossing sunday's threshold
            if (prev_end_offset > current_end_offset) {
                if (week_t < current_end_offset) {
                    break;
                }
            }
        }
        prev_end_offset = current_end_offset;
    }
    if (day_session_it == dailySessions.end()) {
        day_session_it = dailySessions.begin(); // default to first session - offset outside week boundary
    }

    switch (type) {
        case ResetDaily:
            if (position == previous) {
                if (day_session_it == dailySessions.begin()) {
                    // what if we have a single session?
                    return dailySessions.back();
                }
                day_session_it--;
            }
            break;
    }
    return (*day_session_it);
}


inline bool ExtWeeklySession::operator==(ExtWeeklySession& session) const
{
    if (dailySessions.size() != session.dailySessions.size())
        return false;
    if (start_date != session.getStartDate())
        return false;
    if (end_date != session.getEndDate())
        return false;

    //  the day session order presented in the <WeeklySessions>
    //  defines the natural order of each trading day in a week
    //
    vector<ExtDailySession::ptr>::const_iterator it_this = dailySessions.begin();
    vector<ExtDailySession::ptr>::const_iterator it_that = session.getDailySessions().begin();

    for (; it_this != dailySessions.end() && it_that != session.getDailySessions().end(); it_this++, it_that++)
        if (!(*it_this->get() == *it_that->get())) return false;
    return true;
}

inline ExtWeeklySession::ExtWeeklySession(const ExtWeeklySession& obj) : ExtSessionsBase(obj)
{
    start_date = obj.start_date;
    end_date = obj.end_date;
    dailySessions = obj.dailySessions;
    orgsSession = obj.orgsSession;
}


// Given a weekly-bound second-based time parameter - returns offset until the next (or current) RESET session start/end period
inline bool ExtWeeklySession::get_session_info(const ResetType type, const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const
{
    status = NotInAnyTimePeriod;
    if (dailySessions.empty())
        return false;

    switch (type) {
        case ResetNone:
            return get_session_info_none(week_t, start_offset, end_offset, status, flags);

        case ResetDaily:
            return get_session_info_daily(week_t, start_offset, end_offset, status, flags);

        case ResetWeekly:
            return get_session_info_weekly(week_t, start_offset, end_offset, status, flags);

        case ResetMonthly: // unhandled here!
            assert(false);
            break;
    }
    return false;
}


// Calculate session offsets based on single session periods
inline bool ExtWeeklySession::get_session_info_none(const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const
{
    // find which session this week time offset (week_t) is part of ...
    auto day_session_ptr = get_session(ResetNone, week_t, flags);
    if (!day_session_ptr)
        return false;

    // find the single session - and apply start/end offsets
    return day_session_ptr->get_session_info_none(week_t, start_offset, end_offset, status, flags);
}


// Calculate session offsets based on daily reset
inline bool ExtWeeklySession::get_session_info_daily(const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const
{
    // find which session this week time offset (week_t) is part of ...
    auto day_session_ptr = get_session(ResetDaily, week_t, flags);
    if (!day_session_ptr)
        return false;

    return day_session_ptr->get_session_info_daily(week_t, start_offset, end_offset, status, flags);
}


// Calculate session offsets based on weekly reset
inline bool ExtWeeklySession::get_session_info_weekly(const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const
{
    // find which session this week time offset (week_t) is part of ...
    auto day_session_ptr = get_session(ResetWeekly, week_t, flags);
    if (!day_session_ptr)
        return false;

    // need to factor in start/end of week!
    int unused_start_offset(0), unused_end_offset(0);
    int bow_session_type = dailySessions.front()->calculate_daily_session_offsets(week_t, flags, start_offset, unused_end_offset);
    int eow_session_type = dailySessions.back()->calculate_daily_session_offsets(week_t, flags, unused_start_offset, end_offset);

    // In some cases - the starting offset might need to be moved back
    // (The above will calculate the next weekly session start (from our given week_t offset) - which can be in the next week (while our week ending period is current)!
    if (start_offset > end_offset) {
        start_offset -= SecondsInAWeek;
    }

    auto session_type = (day_session_ptr == dailySessions.front()) ? bow_session_type :
                        (day_session_ptr == dailySessions.back()) ? eow_session_type :
                        day_session_ptr->calculate_daily_session_offsets(week_t, flags, unused_start_offset, unused_end_offset);

    if (session_type & inside_session_mask)
        status = day_session_ptr->get_session_status(ResetWeekly, week_t, flags);

    return true;
}


// Given a weekly-bound second-based time parameter - returns offset to the previous daily RESET session start/end period
inline bool ExtWeeklySession::get_previous_daily_reset(const int week_t, int& start_offset, int& end_offset) const
{
    if (dailySessions.empty())
        return false;

    auto day_session_ptr(get_session(ResetDaily, week_t, ApplyNoDribbleOffset, previous));
    if (!day_session_ptr)
        return false;

    start_offset = day_session_ptr->start_offset();
    end_offset = day_session_ptr->end_offset();

    // Adjust offset - based on current weekly time period
    calculate_previous_session_offsets(week_t, start_offset, end_offset);
    return true;
}


// Given a weekly-bound second-based time parameter - returns offset to bar & session offset based on resolution (seconds)
inline bool ExtWeeklySession::calculate_bar_time(unsigned long seconds_span, const int week_t, int& bar_offset, int& end_offset) const
{
    if (dailySessions.empty())
        return false;

    auto day_session_ptr = get_session(ResetNone, week_t);
    if (!day_session_ptr)
        return false;

    return day_session_ptr->calculate_bar_time(seconds_span, week_t, bar_offset, end_offset);
}



inline bool ExtWeeklySession::process_command(CommandTypes command, int attributes)
{
    for each (auto& daily_session in dailySessions) {
        if (!daily_session->process_command(command, attributes))
            return false;
    }
    makeOrgsSession(); // update our local ORGS sessions
    return true;
}


// adjust previous start/end session distance based on offset
inline bool ExtWeeklySession::calculate_previous_session_offsets(int offset_t, int& start, int& end) const
{
    if (start<end) {
        // regular session  (ex. Monday 9AM to 4PM)
        if (offset_t>=start) {
            if (offset_t < end) {
                // this occurs only if we have a single session! fall back one full week!
                start -= (offset_t + SecondsInAWeek); end -= (offset_t + SecondsInAWeek);
            }
            else {
                // offset ahead of the session ...
                start -= offset_t;
                end -= offset_t;
            }
        }
        else {
            // offset_t < start
            start -= (SecondsInAWeek+offset_t);
            end -= (SecondsInAWeek+offset_t);
        }
    }
    else {
        ////////////////////////////////////////////////////
        // session crossing weekly threshold (ex. Friday to Monday)
        if ((offset_t>=start) || (offset_t <= end)) {
            // this occurs only if we have a single session! fall back one full week!
            start -= (offset_t + SecondsInAWeek);
            end -= offset_t;
        }
        else {
            // ahead of session
            start -= (SecondsInAWeek + offset_t);
            end -= offset_t;
        }
    }
    return true;
}


//
// Daily
//

inline ExtDailySession::ExtDailySession(const string& datastr, int version)
{
    reset();

    // parse daily session string
    valid_ = parseString(datastr, version, 0);
}


inline ExtDailySession::ExtDailySession(const string& datastr, __time64_t offset, int version)
{
    reset();

    // parse daily session string
    valid_ = parseString(datastr, version, offset);
}


inline bool ExtDailySession::isValid() const {
    // must have a reset as last single session!
    // verify that dribble/settlement only applies to reset session
    for each (auto& single_session in singleSessions) {
        if (single_session->getReset()) {
            // only last session should have a reset attribute!
            if (single_session != singleSessions.back())
                return false;
        }
        else {
            // if a session doesn't have a reset - it should not have dribble/settlement values
            if (single_session->getDribbleTime() || single_session->getSettlementTime())
                return false;
        }
    }
    return ExtSessionsBase::isValid();
}

inline bool ExtDailySession::parseString(const string& datastr, int version, __time64_t offset)
{
    if (datastr.empty())
        return false;

    vector<string> stokens;
    if (version > 0) {
        // remove the number of session field
        vector<string> tokens;
        tokenizer(datastr, ":", tokens);

        if (tokens.size() < 2)  // number of sessions + daily sessions
            return false;

        // verify numeric only
        if (tokens.front().find_first_not_of("0123456789") != std::string::npos)
            return false;

        tokenizer(*(tokens.begin()+1), ";", stokens); // skip the number of sessions
    }
    else {
        tokenizer(datastr, ";", stokens);
    }

    for (auto stok_iter(stokens.begin()); stok_iter != stokens.end(); stok_iter++) {
        ExtSingleSession::ptr singleSession(new ExtSingleSession(*stok_iter, version, offset));
        if (!singleSession->isValid())
            return false;
        appendSingleSession(singleSession);
    }

    if (singleSessions.empty())
        return false;

    // make sure last session contains a reset!
    if (!singleSessions.back()->getReset())
        return false;

    return true;
}


inline const string ExtDailySession::makeStringV0() const
{
    ostringstream sstr;
    for each (auto& single_session in singleSessions) {
        sstr << single_session->getString(SESSION_VERSION_V0);
    }
    return sstr.str();
}


inline const string ExtDailySession::makeStringV1() const
{
    // insert daily session count
    ostringstream sstr;
    sstr << singleSessions.size() << ":";

    // insert daily sessions
    for each (auto& single_session in singleSessions) {
        sstr << single_session->getString(SESSION_VERSION_V1);
    }
    return sstr.str();
}

inline bool ExtDailySession::operator==(ExtDailySession& sess) const
{
    if (singleSessions.size() != sess.getSingleSessions().size())
        return false;

    // the order of the single session could be random in the data model
    vector<ExtSingleSession::ptr>::const_iterator lhs = singleSessions.begin();
    for (; lhs != singleSessions.end(); lhs++) {
        vector<ExtSingleSession::ptr>::iterator rhs = sess.getSingleSessions().begin();
        for (; rhs != sess.getSingleSessions().end(); rhs++) {
            if (*lhs->get() == *rhs->get())
                break;
        }
        if (rhs == sess.getSingleSessions().end())
            return false;
    }
    return true;
}

inline ExtDailySession::ExtDailySession(const ExtDailySession& obj) : ExtSessionsBase(obj)
{
    singleSessions = obj.singleSessions;
}


inline ExtSingleSession::ptr ExtDailySession::get_session_reset() const {
    // find the single session with reset
    for (auto it(singleSessions.rbegin()); it != singleSessions.rend(); ++it) {
        if ((*it)->getReset()) {
            return (*it);
        }
    }
    return ExtSingleSession::ptr();
}


inline int ExtDailySession::within_session(int offset_t, unsigned short flags) const { // value in seconds
    return within_session_range(offset_t, start_offset(), end_offset(), (flags & ApplyNoDribbleOffset)? 0 : dribble(), (flags & ApplyNoDribbleOffset)? 0 : settlement());
}


inline bool ExtDailySession::process_command(CommandTypes command, int attributes) {
    for each (auto& single_session in singleSessions) {
        if (!single_session->process_command(command, attributes))
            return false;
    }
    return true;
}


inline bool ExtDailySession::get_session_info_none(const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const {
    // find which single session contains our week offset
    ExtSingleSession::ptr session;
    status = get_session_status(ResetNone, week_t, flags, &session);
    if (!session) 
    {
        // We can't find the offset within our daily session, thus we're in between - return first session
        if (!singleSessions.empty()) 
            session = singleSessions.front();
    }

    if (session) {
        calculate_session_offsets(week_t, session->getStartTime(seconds), session->getStopTime(seconds), session->getDribbleTime(seconds), session->getSettlementTime(seconds), start_offset, end_offset);
    }
    else {
        status = NotInAnyTimePeriod;
        return false; // unexpected result
    }
    return true;
}


inline bool ExtDailySession::get_session_info_daily(const int week_t, int& start_offset, int& end_offset, Status& status, unsigned short& flags) const {
    // Adjust start/end offset - against current week time offset
    auto session_type = calculate_daily_session_offsets(week_t, flags, start_offset, end_offset);

    if (session_type & inside_session_mask)
        status = get_session_status(ResetDaily, week_t, flags);

    return true;
}


// Adjust next (or current) start/end daily session distance based on offset!
inline int ExtDailySession::calculate_daily_session_offsets(int offset_t, unsigned short flags, int& start, int& end) const
{
    int dribble_adj = (flags & ApplyNoDribbleOffset) ? 0 : dribble();
    int settlement_adj = (flags & ApplyNoDribbleOffset) ? 0 : settlement();
    return calculate_session_offsets(offset_t, start_offset(), end_offset(), dribble_adj, settlement_adj, start, end);
}


// Given a weekly-bound second-based time parameter - returns offset to sampled bar & session reset, based on resolution (seconds)
inline bool ExtDailySession::calculate_bar_time(unsigned long seconds_span, const int week_t, int& bar_offset, int& end_offset) const
{
    bool within_prev_session(false);

    int prev_end_t_diff = 0;
    bar_offset = end_offset = 0;

    for each (auto& ss in singleSessions) {
        int bar_span = static_cast<int>(seconds_span);
        int end_t = 0, end_t_diff = 0;
        
        auto start_t = ss->getStartTime(seconds); 
        auto stop_t = ss->getStopTime(seconds);

        if (bar_span > prev_end_t_diff + ss->getLength(seconds))
        {
            if (ss->hasFlag(EXTSESSION_ALLOW_CROSS_SESSION_BARS)) 
            {
                // our span is greater than session ... we need to jump over it
                prev_end_t_diff += ss->getLength(seconds);
                if (!within_prev_session) 
                {
                    // verify if this offset is within the full session - so we know it needs to be merged within next session(s)
                    within_prev_session = ((within_session_range(week_t, start_t, stop_t, ss->getDribbleTime(seconds), ss->getSettlementTime(seconds)) & inside_session_mask)>0);
                }
                continue;
            }
            bar_span = ss->getLength(seconds); // max it to current session length
        }

        if (prev_end_t_diff) {
            // adjust starting offset due to left-over seconds from previous session
            assert (bar_span > prev_end_t_diff);

            start_t = start_t + (bar_span - prev_end_t_diff); 

            if (start_t >= SecondsInAWeek) {
                start_t -= SecondsInAWeek;
            }
        }

        if (!within_prev_session)
        {
            // calculate last bar (end_t) of the given resolution within this session
            if (start_t>stop_t) 
            {
                end_t = start_t + ((stop_t + ((SecondsInAWeek - start_t)))/bar_span)*bar_span;

                // verify if our last sampled bar crosses over the sunday threshold
                if (end_t >= SecondsInAWeek) {
                    end_t -= SecondsInAWeek;
                    end_t_diff = stop_t - end_t;
                }
                else 
                {
                    end_t_diff = (SecondsInAWeek - end_t) + stop_t;
                }
            }
            else {
                end_t = start_t + ((stop_t - start_t)/bar_span)*bar_span;
                assert(stop_t >= end_t);
                end_t_diff = stop_t - end_t;
            }
            prev_end_t_diff = end_t_diff;
        }

        // figure out where our current week_t offset falls
        auto session_type = (within_prev_session ? inside_session : within_session_range(week_t, ss->getStartTime(seconds), end_t, 0, 0));
        if (!(session_type & inside_session_mask)) 
        {
            // verify if this offset is within the full session - so we know it needs to be merged within next session(s)
            within_prev_session = ((within_session_range(week_t, ss->getStartTime(seconds), ss->getStopTime(seconds), ss->getDribbleTime(seconds), ss->getSettlementTime(seconds)) & inside_session_mask)>0);
        }
        else 
        {
            if (!within_prev_session) 
            {
                // need to verify if the sampled bar time falls before or after sunday threshold
                if ((start_t>stop_t) && (week_t < start_t))
                {
                    // means our offset is after sunday threshold - move over
                    while (start_t < SecondsInAWeek) start_t += bar_span;
                    start_t -= SecondsInAWeek;
                }

                while (week_t >= start_t) start_t += bar_span;
                if (start_t > SecondsInAWeek) start_t -= SecondsInAWeek;
            }

            bar_offset = start_t;
            end_offset = this->end_offset();
            break;
        }

        if (!ss->hasFlag(EXTSESSION_ALLOW_CROSS_SESSION_BARS))
        {
            prev_end_t_diff = 0;  

            if (within_prev_session) 
            {
                // do not allow merge with next session bar
                bar_offset = ss->getStopTime(seconds);
                end_offset = this->end_offset();
                break;
            }
        }
    }
    
    if (!bar_offset && (week_t <= this->end_offset())) 
    {
        bar_offset = end_offset = this->end_offset();
    }

    if (bar_offset) 
    {
        calculate_session_offsets(week_t, bar_offset, end_offset, 0, 0, bar_offset, end_offset);
        return true;
    }
    return false;
}



// From an offset potentially already within the daily session - need to see if it falls within a single session
inline ExtSessionsBase::Status ExtDailySession::get_session_status(const ResetType type, int offset_t, unsigned short& flags, ExtSingleSession::ptr* session_ptr) const {
    ExtSingleSession::ptr prev_session;
    ExtSessionsBase::Status status((type == ResetNone) ? NotInAnyTimePeriod : InTimePeriodNotTrading);

    for each (auto& ss in singleSessions) {
        auto session_type = within_session_range(offset_t, ss->getStartTime(seconds), ss->getStopTime(seconds), ss->getDribbleTime(seconds), ss->getSettlementTime(seconds));
        if (session_type & inside_session_mask) {
            if (session_ptr) *session_ptr = ss;

            if (ss->getReset())
                flags |= CurrentSessionReset;

            if ((type == ResetNone) && (ss->hasFlag(EXTSESSION_ALLOW_CROSS_SESSION_BARS)))
                flags |= AllowCrossSessionBars;

            if (session_type & inside_dribble) {
                status= InDribbleTimePeriod;
            }
            else if (session_type & inside_settlement) {
                status = InSettlementTimePeriod;
            }
            else {
                status = InSessionTimePeriod;
            }
            break;
        }
        if (prev_session) {
            // verify if in-between sessions
            if (prev_session->getStopTime() < ss->getStartTime()) {
                if (offset_t >= prev_session->getAdjustedEndTime(seconds) && offset_t < ss->getStartTime(seconds)) {
                    if (session_ptr) *session_ptr = ss; // return next session in this case ...
                    if ((type == ResetNone) && (ss->hasFlag(EXTSESSION_ALLOW_CROSS_SESSION_BARS)))
                        flags |= AllowCrossSessionBars;
                    status = InTimePeriodNotTrading;
                    break;
                }
            }
            else {
                if (offset_t >= prev_session->getAdjustedEndTime(seconds) || offset_t < ss->getStartTime(seconds)) {
                    if (session_ptr) *session_ptr = ss; // return next session in this case ...
                    if ((type == ResetNone) && (ss->hasFlag(EXTSESSION_ALLOW_CROSS_SESSION_BARS)))
                        flags |= AllowCrossSessionBars;
                    status = InTimePeriodNotTrading;
                    break;
                }
            }
        }
        prev_session = ss;
    }

    if (!prev_session || prev_session->getReset())
        flags |= PreviousSessionReset;

    return status;
}


//
// Single
//

inline bool ExtSingleSession::parseSingleSessionStringV0(const string& datastr, __time64_t offset) {
    vector<string> tokens;
    tokenizer(datastr, ",", tokens);
    if (tokens.empty())
        return false;

    auto tok_iter(tokens.begin());

    // start time
    wStartTime = WORD(atoi(tok_iter->c_str()));

    // stop time
    if (++tok_iter == tokens.end())
        return false;
    wStopTime = WORD(atoi(tok_iter->c_str()));

    // for current-gen session definition, start time should always be smaller than stop time
    if (wStopTime < wStartTime)
        return false;

    length_ = wStopTime - wStartTime;

    // apply offset
    wStartTime = (wStartTime + WORD(offset)) % WORD(10080);
    wStopTime = (wStopTime + WORD(offset)) % WORD(10080);

    // settlement time
    if (++tok_iter == tokens.end())
        return false;

    wSettlementTime = WORD(atoi(tok_iter->c_str()));

    // dribble time
    if (++tok_iter == tokens.end())
        return false;

    wDribbleTime = WORD(atoi(tok_iter->c_str()));

    // reset flag
    if (++tok_iter == tokens.end())
        return false;

    wReset = WORD(atoi(tok_iter->c_str()));
    return true;
}


inline bool ExtSingleSession::parseSingleSessionStringExt(const string& datastr, int /*version*/, __time64_t offset) {
    vector<string> tokens;
    tokenizer(datastr, ",", tokens);
    if (tokens.empty())
        return false;

    auto tok_iter(tokens.begin());

    // start time
    wStartTime = (WORD(atoi(tok_iter->c_str())) + WORD(offset)) % WORD(10080);

    // length
    if (++tok_iter == tokens.end())
        return false;
    length_ = WORD(atoi(tok_iter->c_str()));
    wStopTime = (wStartTime + length_) % WORD(10080);

    // dribble time
    if (++tok_iter == tokens.end())
        return false;
    wDribbleTime = WORD(atoi(tok_iter->c_str()));

    // settlement time
    if (++tok_iter == tokens.end())
        return false;
    wSettlementTime = WORD(atoi(tok_iter->c_str()));

    // reset flag
    if (++tok_iter == tokens.end())
        return false;
    wReset = WORD(atoi(tok_iter->c_str()));

    flags_ = EXTSESSION_NO_FLAG; // default value

    // single setting flag
    if (++tok_iter != tokens.end()) {
        flags_ = static_cast<unsigned long>(atol(tok_iter->c_str()));
    }
    return true;
}


inline const string ExtSingleSession::makeStringV0(void) const
{
    ostringstream sstr;
    sstr << getStartTime() << ",";
    sstr << getStopTime() << ",";
    sstr << getSettlementTime() << ",";
    sstr << getDribbleTime() << ",";
    sstr << getReset() << ";";
    return sstr.str();
}


inline const string ExtSingleSession::makeStringV1(void) const
{
    // insert daily session count
    ostringstream sstr;
    sstr << getStartTime() << ",";
    sstr << getLength() << ",";
    sstr << getDribbleTime() << ",";
    sstr << getSettlementTime() << ",";
    sstr << getReset() << ",";
    sstr << getFlags() << ";";
    return sstr.str();
}


inline bool ExtSingleSession::process_command(CommandTypes command, int attributes) {
    switch (command) {
        case command_apply_offset:
        {
            //
            // Move the start/end time of each session according to the offset
            // (Note: We should use the 'timezone' attribute instead ...  but due to the 'default' timezone - we have no way of knowing where we stand)
            //
            auto offset(attributes);
            setStartTime((getStartTime() + MinutesInAWeek + offset) % MinutesInAWeek);
            setStopTime((getStopTime() + MinutesInAWeek + offset) % MinutesInAWeek);
        }
        break;

        case command_filter_dribble:
            setDribbleTime(0);
            break;

        case command_resolution_check:
        {
            auto time_span_in_seconds(attributes);
            if (((getStartTime(seconds)) % time_span_in_seconds) || ((getStopTime(seconds)) % time_span_in_seconds))
                return false;
        }
        break;
    }
    return true;
}


#pragma pack( pop, rt_strct_Session_h )



#endif
