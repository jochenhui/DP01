#pragma once

#include "rt_strct=RTFUND.h"

#pragma pack(push,old_pack,1)

struct SCANNING_RECORD  // Scanning stream consists of SCANNING_INFO + (_records * SCANNING_RECORD) 
{
    unsigned long _size;        // FieldID + Fundamental
    unsigned char _identifier;  // Scanning Identifier associated with this result record

public: // methods
    SCANNING_RECORD() : _size(sizeof(SCANNING_RECORD)) {};

    const unsigned char * begin() const { return (reinterpret_cast<const unsigned char*>(this)); }
    const unsigned char * end() const { return (begin() + _size); }
    const Fundamental* record() const { return reinterpret_cast<const Fundamental*>(begin() + sizeof(SCANNING_RECORD)); }

    bool valid() const { return ((_size>sizeof(SCANNING_RECORD)) && record() && record()->valid()); }
    bool numeric() { return (record()->_type & FundamentalInfo::NUMERIC)>0; }
    bool null() { return (record()->_type & FundamentalInfo::NA)>0; }

    void reset() {
        _size = sizeof(SCANNING_RECORD);
        Fundamental * f = const_cast<Fundamental*>(record());
        f->reset();
    }
    void clear() { reset(); _identifier = 0; }

    void set_identifier(unsigned char id) { _identifier = id; }
    template <typename t> void set_value(t v, unsigned short t = FundamentalInfo::UNKNOWN) {
        Fundamental * f = const_cast<Fundamental*>(record());
        bool adjust_size = !f->valid();
        if (t != FundamentalInfo::UNKNOWN) f->_type = t;
        f->SetValue(v);
        if (adjust_size) _size += f->_size;
    }

    double get_result() {
        if (!numeric()) return 0;
        const Fundamental * f = record();
        return f->_data._val;
    }
    void get_result(std::string &s) {
        if (numeric()) { s.erase(); return; }
        const Fundamental * f = record();
        f->GetValue(s);
    }
};

struct SCANNING_INFO
{
    enum 
    { 
        F_COMPLETE = (1 << 0),        // Indicate end if scanning records
        F_UPDATE = (1 << 1),          // Scanning updadate data
        F_SYMBOLS = (1 << 2),         // Include symbols
        F_DATA_FIELDS = (1 << 3),     // Include data fields
        F_RESET_UNIVERSE = (1 << 5),  // Reset universe
        F_IDENTIFIERS = (1 << 14)     // Scanning identifiers data
    };

    unsigned long   _size;
    unsigned long   _records;

public: // methods
    SCANNING_INFO() : _size(0), _records(0) {}

    unsigned char * begin() { return  (reinterpret_cast<unsigned char*>(this)); }
    unsigned char * end() { return (begin() + _size); }

    void reset() { _size = sizeof(SCANNING_INFO); _records = 0; }

};

struct SCANNING_IDENTIFIER 
{
    struct Header {
        unsigned char _records;       // Number of unique SCANNING_IDENTIFIER records
    };
    unsigned long _size;              // SCANNING_IDENTIFIER + value + \0 
    unsigned char _identifier;        // Identifier position

public: // methods
    SCANNING_IDENTIFIER() : _identifier(0), _size(sizeof(SCANNING_IDENTIFIER)) {}

    const unsigned char * begin() const { return (reinterpret_cast<const unsigned char*>(this)); }
    const unsigned char * end() const { return (begin() + _size); }
    const char* name() { return reinterpret_cast<const char*>(begin() + sizeof(SCANNING_IDENTIFIER)); }
};

#pragma pack(pop,old_pack)

