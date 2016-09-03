#include "stdafx.h"
#include "Logger.h"
#include "ApiHandle.h"
#include "Logon.h"

using namespace std;
using namespace std::tr1;

using namespace NS_FEIMA;
using namespace DP_MESSAGE;
ApiHandle::ApiHandle()
{
	init_currencies();
	init_messageChain();
	init_procthread();

	/* ----------------------------------------------------------------------------------- */
	/* exchanges等等不能在这里初始化，因为要Initialize调用之后才能初始化 */
	ProcessMessageCallback_ = nullptr;
}

ApiHandle::~ApiHandle()
{
	wait_procthread();
	delete m_pFreeChain;
	delete m_pProcChain;
}
static CLogger *sg_log = NULL;
void InitLogger()
{
	if (sg_log)
		return;
	sg_log = new CLogger();
	if (sg_log)
	{
		char m_sPath[1024];
		sprintf_s(m_sPath, "%s\\dev\\", getenv("HOMEPATH"));
		sg_log->InitLogger(m_sPath, "tslog", "log", NULL);
		sg_log->OpenLogger();
		sg_log->ReportEvents(LOG_INFO, "Info", "Logger Initialized");
	}
}

void RLog(const char *s)
{
	if (sg_log == NULL)
		InitLogger();
	sg_log->ReportEvents(LOG_INFO, "Info", s);
}

ApiHandle *api = NULL;
void InitApiHandle()
{
	api = new ApiHandle();
}


int ApiHandle::process_attribute_string_get(DirectorMessages::MSG& msg)
{
	int type = 0;
	char m_sRet[2048];
	char m_sTmp[1024];

	strcpy_s(m_sRet, "Enter process_attribute_string_get ");
	if (!msg.get_attribute(DirectorTags::AttributeType, type))
	{
		strcat_s(m_sRet, ": Can not find DirectorTags:AttributeType.");
		RLog(m_sRet);
		return 0;
	}
	
	sprintf_s(m_sTmp, ": Type[%1d]", type);
	strcat_s(m_sRet, m_sTmp);

	switch (type) {
	case SERVER_GENERIC_INFO_TYPE_CONVERSION_RULES:
		// Examples:  <long, short> rates
		// EURUSD	1*(EURUSD),1*(EURUSD.A)
		// HKDCAD	(USDCAD)/(USDHKD.A),(USDCAD.A)/(USDHKD)
		// JPYUSD	1/(USDJPY.A),1/(USDJPY)
	{
		strcat_s(m_sRet, "SERVER_GENERIC_INFO_TYPE_CONVERSION_RULES ");

		std::wstring forex_pair;
		std::wstring attr_str;

		if (msg.get_attribute(DirectorTags::AttributeName, forex_pair)) 
		{

			strcat_s(m_sRet, ",DirectorTags::AttributeName:");
			strcat_s(m_sRet, CW2A(forex_pair.c_str()));
			attr_str = L"1/(MOC:USDCNY.A),1/(MOC:USDCNY)";
			strcat_s(m_sRet, "-->");
			strcat_s(m_sRet, CW2A(attr_str.c_str()));
			strcat_s(m_sRet, "OK");

			// based on the forex pair above - you can define your own custom conversion rules
			// in this code sample - we always return the same formula, regardless of the forex pair for testing purposes
			msg.add_attribute(DirectorTags::AttributeWString, attr_str);
			RLog(m_sRet);
			return 1;
		}
	}
	break;
	}
	strcat(m_sRet, "Unknown:Failed");
	return 0;
}


int ApiHandle::process_attribute_vstring_get(DirectorMessages::MSG& msg)
{
	int type = 0;
	char m_sRet[2048];
	char m_sTmp[1024];

	strcpy_s(m_sRet, "Enter process_attribute_vstring_get ");
	if (!msg.get_attribute(DirectorTags::AttributeType, type))
	{
		strcat_s(m_sRet, ": Can not find DirectorTags:AttributeType.");
		RLog(m_sRet);
		return 0;
	}

	vector<string> v; ostringstream osBuf;
	sprintf_s(m_sTmp, ": Type[%1d]", type);
	strcat_s(m_sRet, m_sTmp);

	switch (type) {
	case SERVER_GENERIC_INFO_TYPE_CURRENCY: {
		// expects a vector of comma-delimited string values of the format <currency name>,<currency code>
		strcat_s(m_sRet, "SERVER_GENERIC_INFO_TYPE_CURRENCY");
		RLog(m_sRet);
		for each (const auto& item in currencies_) {
			osBuf << CW2A(item.second.c_str()) << "," << item.first;
			v.push_back(osBuf.str());

			strcpy_s(m_sRet, "   Currencies:");
			strcat_s(m_sRet, osBuf.str().c_str());
			RLog(m_sRet);

			osBuf.clear(); osBuf.str("");
		}
		msg.add_attribute(DirectorTags::AttributeVString, v);
		return 1; }

	case SERVER_GENERIC_INFO_TYPE_COUNTRY: {
		strcat_s(m_sRet, "SERVER_GENERIC_INFO_TYPE_COUNTRY(US,United States;CN,China)");
		RLog(m_sRet);

		// expects a vector of comma-delimited supported countries <country code>,<country name> [-AssetType] (optionally with the RTType asset category) 
		v.push_back("US,United States"); // all assets supported
		v.push_back("CN,China"); // JP forex only  [RTType_Forex]
		msg.add_attribute(DirectorTags::AttributeVString, v);
		return 1; }

	case SERVER_GENERIC_INFO_TYPE_NEWS_COUNTRIES:
		strcat_s(m_sRet, "SERVER_GENERIC_INFO_TYPE_NEWS_COUNTRIES(US,CN)");
		RLog(m_sRet);
		v.push_back("US");
		v.push_back("CN");
		msg.add_attribute(DirectorTags::AttributeVString, v);
		return 1;
	}
	strcat_s(m_sRet, "Unknown");
	RLog(m_sRet);
	return 0;
}

int ApiHandle::process_attribute_apiversion_get(DirectorMessages::MSG& msg)
{
	int ts_api_major_version = -1;
	int ts_api_minor_version = -1;
	char m_sRet[2048];
	char m_sTmp[1024];

	strcpy_s(m_sRet, "Enter process_attribute_apiversion_get ");

#if 0
	int i;
	for (i = 0; i <= DirectorTags::Msg_periodic; i++)
	{
		if (!msg.get_attribute((DirectorTags::TagType)i, ts_api_major_version))
			continue;
		sprintf_s(m_sTmp, "TagInfo:%d", i);
		RLog(m_sTmp);
	}
#endif
	//
	// get TradeStation API SDK major/minor versions
	//
	if (!msg.get_attribute(DirectorTags::Msg_API_Version_Major, ts_api_major_version))
	{
		strcat_s(m_sRet, "Can not find:DirectorTags::Msg_API_Version_Major");
		RLog(m_sRet);
		return 0;
	}
	if (!msg.get_attribute(DirectorTags::Msg_API_Version_Minor, ts_api_minor_version))
	{
		strcat_s(m_sRet, "Can not find:DirectorTags::Msg_API_Version_Minor");
		RLog(m_sRet);
		return 0;
	}

	//
	// Return 3rd-Party API SDK major/minor versions
	//
	DirectorMessages::MSG apiver_3pdp = DirectorMessages::MSG(DirectorMessages::Msg_Attribute_API_Version_Get);
	apiver_3pdp.add_attribute(DirectorTags::Msg_API_Version_Major, TS_APISDK_MAJOR_VERSION);
	apiver_3pdp.add_attribute(DirectorTags::Msg_API_Version_Minor, TS_APISDK_MINOR_VERSION);
	msg = apiver_3pdp;
	sprintf_s(m_sTmp, "Major:%d,Minor:%d", TS_APISDK_MAJOR_VERSION, TS_APISDK_MINOR_VERSION);
	strcat_s(m_sRet, m_sTmp);
	RLog(m_sRet);
	return 0;
}

// ProcessSyncMessage
// Return: 0 failure, 1+ sucess
// Input/Output: msg
int ApiHandle::ProcessSyncMessage(DirectorMessages::MSG& msg)
{
	switch (msg.MessageId_) {
	case DirectorMessages::Msg_Attribute_String_Get:
		RLog("ProcessSyncMessage:Msg_Attribute_String_Get");
		return process_attribute_string_get(msg);

	case DirectorMessages::Msg_Attribute_VString_Get:
		RLog("ProcessSyncMessage:Msg_Attribute_VString_Get");
		return process_attribute_vstring_get(msg);

	case DirectorMessages::Msg_Attribute_API_Version_Get:
		RLog("ProcessSyncMessage:Msg_Attribute_API_Version_Get");
		return process_attribute_apiversion_get(msg);
	}
	char m_sRet[1024];
	sprintf_s(m_sRet, "ProcessSyncMessage:unknown:%d", msg.MessageId_);
	RLog(m_sRet);
	return 0;
}

bool ApiHandle::Initialize(PCWSTR szLogDirectory, unsigned long ulDataProviderID, DirectorSignatures::CallbackProcessMessage pCB) 
{
	char m_sRet[2048];

	sprintf_s(m_sRet, "Initialize(\"%s\",%ul,%p)", (char*)CW2A(szLogDirectory), ulDataProviderID, pCB);
	RLog(m_sRet);
	m_DataProviderID = static_cast<unsigned char>(ulDataProviderID);
	m_ulShiftedDataProviderID = ulDataProviderID << 28;
	ProcessMessageCallback_ = pCB;


	init_exchanges();
	initialize_secfield_types();//--chenhui

	return true;
}
/* ---- Quote Get Func ----*/
unsigned long ApiHandle::QuoteGet(PCWSTR pSymbol, int AssetType, unsigned char* pFields, LCID locale_id, DirectorSignatures::CallbackQuoteGet pCB, unsigned long UserData, bool bPeriodic)
{
	int evID = make_eventid();
	CBaseMessage *pmsg;
	pmsg = m_pFreeChain->AllocatePop(CBaseMessage::quote);
	if (NULL == pmsg){
		pmsg = new CQuoteMsg(wstring(pSymbol), AssetType, pFields, locale_id, evID, bPeriodic, UserData, pCB);
	}
	else{
		(dynamic_cast<CQuoteMsg*>(pmsg))->SetQuoteMsg(CBaseMessage::quote, wstring(pSymbol), AssetType, evID, UserData, std::string((char const *)pFields), pCB, bPeriodic, locale_id );
	}

	m_pProcChain->Push(pmsg);

	/*---------------------------------------------------------*/
	/* add log */
	std::string str;
	char m_sRet[2048];
	sprintf_s(m_sRet, "QuoteGet:evid:%d)", evID);
	RLog(m_sRet);
	/*---------------------------------------------------------*/

	return evID;
}


void ApiHandle::init_currencies()
{
	currencies_[FDS_CURRENCY_USD] = L"USD";
	currencies_[FDS_CURRENCY_CAD] = L"CAD";
	currencies_[FDS_CURRENCY_CNY] = L"CNY";
	currencies_[FDS_CURRENCY_EUR] = L"EUR";
	currencies_[FDS_CURRENCY_HKD] = L"HKD";
	currencies_[FDS_CURRENCY_SAR] = L"SAR";
	currencies_[FDS_CURRENCY_JPY] = L"JPY";
	currencies_[FDS_CURRENCY_KRW] = L"KRW";
}

void ApiHandle::init_messageChain()
{
// 	m_pFreeChain = new CMessageChain(new CBaseMessage());
// 	m_pProcChain = new CMessageChain(new CBaseMessage());
	DirectorMessages::MSG msg;
	m_pFreeChain = new CMessageChain(new CGenericMsg(msg));
	m_pProcChain = new CMessageChain(new CGenericMsg(msg));
}
void ApiHandle::init_exchanges()
{
	/* ----------------------------------------------------------------------------------- */
	/* 初始化3个交易所 */
	m_Exchanges[0].m_cIndex = (m_DataProviderID * LOCAL_EXCHANGE_GROUP_SIZE) + 1;
	m_Exchanges[1].m_cIndex = (m_DataProviderID * LOCAL_EXCHANGE_GROUP_SIZE) + 2;
	m_Exchanges[2].m_cIndex = (m_DataProviderID * LOCAL_EXCHANGE_GROUP_SIZE) + 3;

	wcscpy_s(m_Exchanges[0].m_wsShortName, L"MOCK");
	wcscpy_s(m_Exchanges[0].m_wsLongName, L"China Financial Futurs Exchange");
	wcscpy_s(m_Exchanges[1].m_wsShortName, L"SHSE");
	wcscpy_s(m_Exchanges[1].m_wsLongName, L"ShangHai Stock Exchange");
	wcscpy_s(m_Exchanges[2].m_wsShortName, L"SZSE");
	wcscpy_s(m_Exchanges[2].m_wsLongName, L"ShenZhen Stock Exchange");

	m_Exchanges[0].m_cTimeZone = WOWRTINFO_CHINA;
	m_Exchanges[0].m_cStartHour = 9;
	m_Exchanges[0].m_cStartMinute = 15;
	m_Exchanges[0].m_cCloseHour = 15;
	m_Exchanges[0].m_cCloseMinute = 15;
	m_Exchanges[0].m_cDaysOfWeek = FDS_DAYBIT_MONDAY | FDS_DAYBIT_TUESDAY | FDS_DAYBIT_WEDNESDAY | FDS_DAYBIT_THURSDAY | FDS_DAYBIT_FRIDAY;
	m_Exchanges[0].m_cDelayMinutes = 15;
	m_Exchanges[0].m_cCurrency = FDS_CURRENCY_CNY;

	for (int i = 1; i < 3; ++i)
	{
		m_Exchanges[i].m_cTimeZone = WOWRTINFO_CHINA;
		m_Exchanges[i].m_cStartHour = 9;
		m_Exchanges[i].m_cStartMinute = 30;
		m_Exchanges[i].m_cCloseHour = 15;
		m_Exchanges[i].m_cCloseMinute = 0;
		m_Exchanges[i].m_cDaysOfWeek = FDS_DAYBIT_MONDAY | FDS_DAYBIT_TUESDAY | FDS_DAYBIT_WEDNESDAY | FDS_DAYBIT_THURSDAY | FDS_DAYBIT_FRIDAY;
		m_Exchanges[i].m_cDelayMinutes = 15;
		m_Exchanges[i].m_cCurrency = FDS_CURRENCY_CNY;
	}

}
void ApiHandle::init_procthread()
{
	RLog("Create procthread.");
	m_hQuitThread = CreateSemaphore(NULL, 0, 1, NULL);
	m_hThreadHandle = CreateThread(NULL,0,ThreadEntry,this,0,&m_dwThreadID);
}
void ApiHandle::wait_procthread()
{
	RLog("Wait thread quit.");
	ReleaseSemaphore(m_hQuitThread,1,NULL);
	WaitForSingleObject(m_hThreadHandle, INFINITE);
	CloseHandle(m_hQuitThread);
	CloseHandle(m_hThreadHandle);
}

int ApiHandle::ProcessMesssage(DirectorMessages::MSG &msg)
{
	std::string str;
	char m_sRet[2048];
	DWORD evid;

	if (GetMessageIDString(msg, str) == false)
	{
		sprintf_s(m_sRet, "ProcessMessage:Unknown ID:%d", msg.MessageId_);
		RLog(m_sRet);
		return 1;
	}
	sprintf_s(m_sRet, "ProcessMessge:MessageID:%d(%s)", msg.MessageId_, str.c_str());
	RLog(m_sRet);

	switch (msg.MessageId_)
	{
	case DirectorMessages::Msg_TS_Version:
		return process_Msg_TS_Version(msg);
	case DirectorMessages::Msg_TS_LocaleId:
		return process_Msg_TS_LocalId(msg);

	case DirectorMessages::Msg_Connect:
	case DirectorMessages::Msg_FundamentalInfo:
	case DirectorMessages::Msg_Fundamental:
	case DirectorMessages::Msg_EcnBookCodeInfo:
	case DirectorMessages::Msg_ReqMarketMakers:
	case DirectorMessages::Msg_ReqSymbolList:
	case DirectorMessages::Msg_ReqHotList:
	case DirectorMessages::Msg_ReqHist:
	case DirectorMessages::Msg_ReqGlobalNewsProviders:
	case DirectorMessages::Msg_ReqGlobalNewsHeadlines:
	case DirectorMessages::Msg_ReqGlobalNewsStories:
	case DirectorMessages::Msg_ReqArchiveHistory:
	case DirectorMessages::Msg_ReqBars:
	case DirectorMessages::Msg_ReqDailyBars:
	case DirectorMessages::Msg_ReqSession:
	case DirectorMessages::Msg_ReqChartInfo:
	case DirectorMessages::Msg_ReqScanningInfo:
		evid = add_generic_message(msg);
		return (int)evid;
	case DirectorMessages::Msg_ConnectionStatus:
		add_connectionstatus_message(msg);
		return 1;
	}
	return 1;
}
void ApiHandle::ExchangesGet(std::map<unsigned short, std::wstring>& ex_map)
{
	char m_sRet[2048];
	char m_sTmp[1024];

	RLog("ExchangesGet(3 exchanges)");
	sprintf_s(m_sRet, "\tIndex:%d,%s", TICKREC_BASE::MakeLocalExchangeIndex(m_Exchanges[0].m_cIndex), (const char*)CW2A(m_Exchanges[0].m_wsShortName));
	RLog(m_sRet);
//	sprintf_s(m_sRet, "\tIndex:%d,%s", (int)m_Exchanges[1].m_cIndex, (const char*)CW2A(m_Exchanges[1].m_wsShortName));
//	RLog(m_sRet);
//	sprintf_s(m_sRet, "\tIndex:%d,%s", (int)m_Exchanges[2].m_cIndex, (const char*)CW2A(m_Exchanges[2].m_wsShortName));
//	RLog(m_sRet);

	ex_map[TICKREC_BASE::MakeLocalExchangeIndex(m_Exchanges[0].m_cIndex)] = m_Exchanges[0].m_wsShortName;
//	ex_map[TICKREC_BASE::MakeLocalExchangeIndex(m_Exchanges[1].m_cIndex)] = m_Exchanges[1].m_wsShortName;
//	ex_map[TICKREC_BASE::MakeLocalExchangeIndex(m_Exchanges[2].m_cIndex)] = m_Exchanges[2].m_wsShortName;
}
long ApiHandle::AttributeNumericGet(unsigned long type, int index, int field, long defaultValue)//chenhui
{
	/* ------ log ----- */
	char m_sRet[2048];
	char m_sTmp[1024];
	sprintf_s(m_sRet, "AttributeNumericGet(type:%ld, index : %d, field : %d, defaultValue : %ld)", type,index,field,defaultValue);
	//RLog(m_sRet);
	/* ---------------- */

	ApiHandle::ExchangeStruct& local_exchange = m_Exchanges[0];
	switch (type)
	{
	case SERVER_GENERIC_INFO_TYPE_EXCHANGE://根据field类型来获取交易所的相关信息比如时区、开盘时间、收盘时间等
		{
			if (index != TICKREC_BASE::MakeLocalExchangeIndex(local_exchange.m_cIndex))
				return defaultValue;

			switch (field)
			{
			case RT_EXCHFIELD_INDEX:
			case RT_EXCHFIELD_M4_ID:        return index;

			case RT_EXCHFIELD_TIMEZONE:     return local_exchange.m_cTimeZone;
			case RT_EXCHFIELD_STARTHOUR:    return local_exchange.m_cStartHour;
			case RT_EXCHFIELD_STARTMIN:     return local_exchange.m_cStartMinute;
			case RT_EXCHFIELD_CLOSEHOUR:    return local_exchange.m_cCloseHour;
			case RT_EXCHFIELD_CLOSEMIN:     return local_exchange.m_cCloseMinute;
			case RT_EXCHFIELD_DAYSOFWEEK:   return local_exchange.m_cDaysOfWeek;
			case RT_EXCHFIELD_EXCHDELAY:    return local_exchange.m_cDelayMinutes;
			}
		}
		break;
	case SERVER_GENERIC_INFO_TYPE_QUOTES://获取报价(Quote)各个字段的类型值
		switch (index)
		{
		case SERVER_GENERIC_DEFAULT_INDEX:
		{
			boost::unordered_map<int, long>::const_iterator result = secfield_types.find(field);
			if (result != secfield_types.end())
			{
				return (*result).second;
			}
		}
			break;
		default:
			break;
		}
	default:
		break;
	}

	return defaultValue;
}
bool ApiHandle::GetMessageIDString(DirectorMessages::MSG &msg,std::string &str)
{
#define CVTCASE(a)	case DirectorMessages::##a: str = #a; break;
	switch (msg.MessageId_)
	{
		CVTCASE(Msg_Unknown);
		CVTCASE(Msg_Connect);
		CVTCASE(Msg_ConnectionStatus);
		CVTCASE(Msg_TS_Version);
		CVTCASE(Msg_TS_LocaleId);
		CVTCASE(Msg_FundamentalInfo);
		CVTCASE(Msg_Fundamental);
		CVTCASE(Msg_EcnBookCodeInfo);
		CVTCASE(Msg_ReqMarketMakers);
		CVTCASE(Msg_ReqSymbolList);
		CVTCASE(Msg_ReqHotList);
		CVTCASE(Msg_ReqHist);
		CVTCASE(Msg_ReqGlobalNewsProviders);
		CVTCASE(Msg_ReqGlobalNewsHeadlines);
		CVTCASE(Msg_ReqGlobalNewsStories);
		CVTCASE(Msg_ReqArchiveHistory);
		CVTCASE(Msg_ReqBars);
		CVTCASE(Msg_ReqDailyBars);
		CVTCASE(Msg_ReqSession);
		CVTCASE(Msg_ReqChartInfo);
		CVTCASE(Msg_ReqScanningInfo);
		CVTCASE(Msg_ReqScanning);

		// ngCal
		CVTCASE(Msg_QuoteGet);
		CVTCASE(Msg_NoLatency);
		CVTCASE(Msg_Sequence);
		CVTCASE(Msg_Release);

		CVTCASE(Msg_Synchronous_Offset);
		CVTCASE(Msg_Attribute_String_Get);
		CVTCASE(Msg_Attribute_VString_Get);
		CVTCASE(Msg_Attribute_API_Version_Get);
	default:
		str = "unknown";
		return false;
	}
	return true;
}

int ApiHandle::process_Msg_TS_Version(DirectorMessages::MSG & msg)
{
	char m_sRet[2048];

	if (msg.get_attribute(DirectorTags::TS_Version, TS_Version_) == false)
	{
		RLog("Can not find TS_VERSION");
		return 1;
	}
	if (msg.get_attribute(DirectorTags::TS_ParentHWND, (int&)TS_ParentHWND_) == false)
	{
		RLog("Can not find TS_ParentHWND");
		return 1;
	}

	sprintf_s(m_sRet, "process_Msg_TS_Version(%s,%x)", (char*)CW2A(TS_Version_.c_str()),(unsigned int) TS_ParentHWND_);
	RLog(m_sRet);
	return 1;
}

int  ApiHandle::process_Msg_TS_LocalId(DirectorMessages::MSG & msg)
{
	char m_sRet[2048];

	msg.get_attribute(DirectorTags::Msg_LocaleId, TS_LocaleId_);
	sprintf_s(m_sRet, "process_Msg_TS_LocalId(%x)", TS_LocaleId_);
	RLog(m_sRet);
	return 1;
}
static DWORD	m_dwEventID = 0;
DWORD ApiHandle::make_eventid(void)
{
	DWORD evid = ++m_dwEventID % 0XFFFFFFF;
	return ((evid) | m_ulShiftedDataProviderID);
}
DWORD ApiHandle::add_generic_message(DirectorMessages::MSG &msg)
{
	int evID = make_eventid();//DWORD -> int  very important!
	CBaseMessage *pmsg;

	msg.add_attribute(DirectorTags::Msg_Event, evID);

// 	pmsg = m_pFreeChain->AllocatePop();
// 	pmsg->SetGenericMessage(msg);

	//--modify chenhui
	pmsg = m_pFreeChain->AllocatePop(CBaseMessage::Generic);
	if (NULL == pmsg){
		pmsg = new CGenericMsg(msg);
	}
	else{
		(dynamic_cast<CGenericMsg*>(pmsg))->SetGenericMessage(msg);
	}
	//--end

	m_pProcChain->Push(pmsg);

	/*---------------------------------------------------------*/
	/* add log */
	std::string str;
	char m_sRet[2048];

	if (GetMessageIDString(msg, str) == false)
	{
		sprintf_s(m_sRet, "add_generic_message:Unknown ID:%d", msg.MessageId_);
		RLog(m_sRet);
		return evID;
	}
	sprintf_s(m_sRet, "add_generic_message:MessageID:%d(%s),evid:%x)", msg.MessageId_, str.c_str(), evID);
	RLog(m_sRet);
	/*---------------------------------------------------------*/

	return evID;
}
DWORD ApiHandle::add_connectionstatus_message(DirectorMessages::MSG &msg)
{
	std::string str;
	char m_sRet[2048];
	DirectorStatus::State stat;

	msg.get_attribute(DirectorTags::ConnectionStatus, stat);
	if ((stat != DirectorStatus::Online) && (stat != DirectorStatus::Offline))
	{
		sprintf_s(m_sRet, "add_connectionstatus_message:Unknownstatus:%d", (int)stat);
		RLog(m_sRet);
		return 0;
	}
//	DWORD evID = ++m_dwEventID;
	CBaseMessage *pmsg;

//	msg.add_attribute(DirectorTags::Msg_Event, evID);
	return 0L;
	
	pmsg = m_pFreeChain->AllocatePop(CBaseMessage::ConnectionStatus);
	if (NULL == pmsg){
		pmsg = new CConnectionStatusMsg(stat);
	}
	else{
		(dynamic_cast<CConnectionStatusMsg*>(pmsg))->SetConnectionStatus(stat);
	}
//	pmsg->SetConnectionStatus(msg,stat);

	m_pProcChain->Push(pmsg);

	/*---------------------------------------------------------*/
	/* add log */

	if (GetMessageIDString(msg, str) == false)
	{
		sprintf_s(m_sRet, "add_connectionstatus_message:Unknown ID:%d", msg.MessageId_);
		RLog(m_sRet);
		return 0;
	}
	sprintf_s(m_sRet, "add_connectionstatus_message:MessageID:%d(%s),%d,", msg.MessageId_, str.c_str(),(int)stat);
	if (stat == DirectorStatus::Online)
	{
		strcat_s(m_sRet, "Online)");
	}
	if (stat == DirectorStatus::Offline)
	{
		strcat_s(m_sRet, "Offline)");
	}
	RLog(m_sRet);
	/*---------------------------------------------------------*/
	return 0;
}
