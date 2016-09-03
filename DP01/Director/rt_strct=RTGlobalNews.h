#pragma once
#pragma warning (disable: 4800)

#pragma pack( push, old_pack, 1 )

//
//  Global News Actions - 0 is the default which means add
//
#define RT_GLOBALNEWS_CHANGESEVENT_DELETE	1

//
//  Global News Flags - bit coded field (DWORD)
//
#define RT_GLOBALNEWS_PROP_REALTIME	        0x0000
#define RT_GLOBALNEWS_PROP_HISTORY	        0x0001
#define RT_GLOBALNEWS_PROP_HOTNEWS	        0x0002
#define RT_GLOBALNEWS_PROP_URGENT           0x0004
#define RT_GLOBALNEWS_PROP_DELETED          0x1000

#define RT_GLOBALNEWS_ACTION_ADD            0x0100
#define RT_GLOBALNEWS_ACTION_DELETE         0x0200

//
//  Flag to indicate last news entry
//
#define RT_GLOBALNEWS_PROP_LASTPROVIDER 	1

//
//  Global News content formats
//
#define RT_GLOBALNEWS_FORMAT_PLAIN_TEXT     0x01
#define RT_GLOBALNEWS_FORMAT_HTML           0x04

#pragma warning (default : 4800 )
#pragma pack(pop,old_pack)
