#pragma once
#include "BaseMessage.h"
#include "MessageChain.h"

//--chenhui
#include "DirectorSignatures.h"
#include <boost/algorithm/string.hpp>
#include <boost/unordered_map.hpp>
#define PERIODIC_MESSAGE_INTERVAL               20
//--end

// Archive Information Attributes
struct ArchiveInfoAttrs {
	HISTORYINFO m_HistInfo;
	ACKARCHIVEINFO m_ArchiveInfo;
};

// Local MOCK messages
struct BarMsgAttributes { // attributes used in bar building algorithms
	unsigned long   m_BarCount;
	unsigned long   m_Observations;
	unsigned long   m_loadOptions;

	float m_PriceOffset;
	bool m_IncrementUp;

	std::wstring m_ArchiveSymbol;
	ArchiveInfoAttrs m_ArchiveAttrs;

	bool m_bArchiveAvailable;

	//  Bar Type ID is used to support custom types of tick/bar requests
	//
	//  It uses string format to indicate the type of custom type of tick/bar to be returned 
	//  by data provider. For example, "Turnover". If the Bar Type ID is empty string, the 
	//  regular price tick/bar should be returned to TS/CAL.
	//
	std::wstring m_CustomBarId;

	//  Mock Data Provider Errors
	bool errorTicksPresented;
	vector<TICKREC_BASE> mockDupTicks;

	BarMsgAttributes() {
		m_BarCount = 0;
		m_Observations = 0;
		m_loadOptions = 0;
		m_PriceOffset = float(0);
		m_IncrementUp = false;
		m_ArchiveSymbol = L"";
		memset(&m_ArchiveAttrs, 0, sizeof(m_ArchiveAttrs));
		m_bArchiveAvailable = false;
		m_CustomBarId = L"";
		errorTicksPresented = false;
		mockDupTicks.clear();
	}
};

//  Helper Scanning Dictionary Entry Class
//
class HelperScanningInfoEntry {
public:
	HelperScanningInfoEntry(const std::wstring& id, const std::wstring& label, const std::wstring& backend_id, const short data_type,
		const unsigned long f_property, const std::wstring& description) :
		field_id_(id), field_label_(label), field_backend_id_(backend_id),
		field_data_type_(data_type), field_property_(f_property), field_description_(description) {}

	const std::wstring& getEntryString() {
		std::wostringstream buf;
		buf << field_id_ << std::wstring(L";");
		buf << field_label_ << std::wstring(L";");
		buf << field_backend_id_ << std::wstring(L";");
		buf << int(field_data_type_) << std::wstring(L";");
		buf << field_property_ << std::wstring(L";");
		buf << field_description_;
		field_entry_string_ = buf.str();
		return field_entry_string_;
	}

private:
	// data fields
	std::wstring field_id_;
	std::wstring field_label_;
	std::wstring field_backend_id_;
	short field_data_type_;
	unsigned long field_property_;
	std::wstring field_description_;

	// complete dictionary entry string
	std::wstring field_entry_string_;
};

// Class to append fields to the data buffer
class CStringUtility
{
public:
	static void append_quote_header(std::string& msg_buf, unsigned char field_id, unsigned char field_size, unsigned char field_type);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, std::string const & sValue);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, std::wstring const & sValue);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, unsigned short value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, long value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, unsigned long value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, unsigned long long value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, float value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, double value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, unsigned char value);

	// Utility functions w/o field type
	static void append_quote_header(std::string& msg_buf, unsigned char field_id);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, std::string const & sValue);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, std::wstring const & sValue);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned short value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, long value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned long value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned long long value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, float value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, double value);
	static void append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char value);
public:
	static const int QuoteFieldHeaderSize = 3;
};

//fields used in quote requests  chenhui
enum eFieldTypeByte {
	SECFIELD_EXPIRATION_STYLE = RT_SECFIELD_EXPIRATION_STYLE,
	SECFIELD_EXPIRY_TYPE = RT_SECFIELD_EXPIRY_TYPE,
	SECFIELD_OPTIONTYPE = RT_SECFIELD_OPTIONTYPE
};

enum eFieldTypeDouble {
	SECFIELD_ASK_EX = RT_SECFIELD_ASK_EX,
	SECFIELD_BID_EX = RT_SECFIELD_BID_EX,
	SECFIELD_LASTTRADE = RT_SECFIELD_LASTTRADE,
	SECFIELD_MARGIN = RT_SECFIELD_MARGIN,
	SECFIELD_VWAP = RT_SECFIELD_VWAP,
	SECFIELD_TWAP = RT_SECFIELD_TWAP,
	SECFIELD_HOTLIST_CRITERIA = RT_SECFIELD_HOTLIST_CRITERIA
};

enum eFieldTypeFloat {
	SECFIELD_OPEN = RT_SECFIELD_OPEN,
	SECFIELD_HIGH = RT_SECFIELD_HIGH,
	SECFIELD_LOW = RT_SECFIELD_LOW,
	SECFIELD_CLOSE = RT_SECFIELD_CLOSE,
	SECFIELD_PREVCLOSE = RT_SECFIELD_PREVCLOSE,
	SECFIELD_12MONTHHIGH = RT_SECFIELD_12MONTHHIGH,
	SECFIELD_12MONTHLOW = RT_SECFIELD_12MONTHLOW,
	SECFIELD_STRIKE = RT_SECFIELD_STRIKE,
	SECFIELD_MINMOVE = RT_SECFIELD_MINMOVE,
	SECFIELD_POINTVALUE = RT_SECFIELD_POINTVALUE,
	SECFIELD_OPEN_GAP = RT_SECFIELD_OPEN_GAP,
	SECFIELD_PUT_CALL_VOLUME_RATIO = RT_SECFIELD_PUT_CALL_VOLUME_RATIO,
	SECFIELD_TURNOVER_RATE = RT_SECFIELD_TURNOVER_RATE,
	SECFIELD_DYNAMIC_PE = RT_SECFIELD_DYNAMIC_PE,
	SECFIELD_IOPV = RT_SECFIELD_IOPV,
	SECFIELD_TURNOVER = RT_SECFIELD_TURNOVER
};

enum eFieldTypeLong {
	SECFIELD_BASECODE = RT_SECFIELD_BASECODE,
	SECFIELD_BASE_LOCALE_ID = RT_SECFIELD_BASE_LOCALE_ID,
	SECFIELD_LOCALE_ID = RT_SECFIELD_LOCALE_ID,
	SECFIELD_TOTALVOL = RT_SECFIELD_TOTALVOL,
	SECFIELD_LASTTRADETIME = RT_SECFIELD_LASTTRADETIME,
	SECFIELD_LASTBIDTIME = RT_SECFIELD_LASTBIDTIME,
	SECFIELD_LASTASKTIME = RT_SECFIELD_LASTASKTIME,
	SECFIELD_CURRENCY = RT_SECFIELD_CURRENCY,
	SECFIELD_ASKSIZE = RT_SECFIELD_ASKSIZE,
	SECFIELD_BIDSIZE = RT_SECFIELD_BIDSIZE,
	SECFIELD_TRADEVOL = RT_SECFIELD_TRADEVOL,
	SECFIELD_OPENINTEREST = RT_SECFIELD_OPENINTEREST,
	SECFIELD_PUT_OPEN_INTEREST = RT_SECFIELD_PUT_OPEN_INTEREST,
	SECFIELD_CALL_OPEN_INTEREST = RT_SECFIELD_CALL_OPEN_INTEREST
};

enum eFieldTypeSecType {
	SECFIELD_ASSETTYPE = RT_SECFIELD_ASSETTYPE
};

enum eFieldTypeULong {
	SECFIELD_CFI = RT_SECFIELD_CFI,
	SECFIELD_BITFLAGS = RT_SECFIELD_BITFLAGS,
	SECFIELD_DISPLAYTYPE = RT_SECFIELD_DISPLAYTYPE,
	SECFIELD_FIRST_NOTICE_DATE = RT_SECFIELD_FIRST_NOTICE_DATE,
	SECFIELD_DELIVERY_DATE = RT_SECFIELD_DELIVERY_DATE,
	SECFIELD_EXPIRATIONDATE = RT_SECFIELD_EXPIRATIONDATE,
	SECFIELD_LAST_TRADING_DATE = RT_SECFIELD_LAST_TRADING_DATE,
	SECFIELD_NUMOPTIONS = RT_SECFIELD_NUMOPTIONS,
	SECFIELD_CALL_VOLUME = RT_SECFIELD_CALL_VOLUME,
	SECFIELD_PUT_VOLUME = RT_SECFIELD_PUT_VOLUME,
	SECFIELD_NUMTRADES = RT_SECFIELD_NUMTRADES
};

enum eFieldTypeULongLong {
	SECFIELD_PRICE_LOWLIMIT = RT_SECFIELD_PRICE_LOWLIMIT,
	SECFIELD_PRICE_HIGHLIMIT = RT_SECFIELD_PRICE_HIGHLIMIT
};

enum eFieldTypeShort {
	SECFIELD_EXCHANGEINDEX = RT_SECFIELD_EXCHANGEINDEX,
	SECFIELD_DAILY_LIMIT = RT_SECFIELD_DAILY_LIMIT,
	SECFIELD_TRADEEXCHANGE = RT_SECFIELD_TRADE_EXCHANGE,
	SECFIELD_BIDEXCHANGE = RT_SECFIELD_BID_EXCHANGE,
	SECFIELD_ASKEXCHANGE = RT_SECFIELD_ASK_EXCHANGE,
	SECFIELD_LASTASKARROW = RT_SECFIELD_LASTASKARROW,
	SECFIELD_LASTBIDARROW = RT_SECFIELD_LASTBIDARROW,
	SECFIELD_8UPDOWNBITPAIRS = RT_SECFIELD_8UPDOWNBITPAIRS
};

enum eFieldTypeString {
	SECFIELD_NAME = RT_SECFIELD_NAME,
	SECFIELD_CURRDESC = RT_SECFIELD_CURRDESC,
	SECFIELD_ROOTSYMBOL = RT_SECFIELD_ROOTSYMBOL,
	SECFIELD_CONVERSION_FORMULAS = RT_SECFIELD_CONVERSION_FORMULAS,
	SECFIELD_COUNTRY_CODE = RT_SECFIELD_COUNTRY_CODE,
	SECFIELD_DELIVERABLE = RT_SECFIELD_DELIVERABLE,
	SECFIELD_UNDERLYINGSYMBOL = RT_SECFIELD_UNDERLYINGSYMBOL
};

enum eFieldTypeWString {
	SECFIELD_DESCRIPTION = RT_SECFIELD_DESCRIPTION,
	SECFIELD_NAME_EXT = RT_SECFIELD_NAME_EXT_W
};

enum ePriceWaveForm {
	eRANDOM,
	eSIN,
	eSYSTEMATIC,
	eLVL2,
	eCCA,
	eFOREX,
	eINDEX,
	eOPEN_INTEREST,
	eTWAP,
	eTURNOVER,

	// debugging symbol types for data provider errors
	eERROOO,        //  out of order ticks/bars
	eERRDUP,        //  duplicate ticks/bars (NA for real-time tick stream)
	eERRMISS1,      //  number of records returned more than actual data records
	eERRMISS2,      //  number of records returned less than actual data records
	eERRMISS3,      //  missing ticks/bars at the beginning of the requested time range (NA for real-time tick stream)
	eERRMISS4       //  missing ticks/bars at the end of the requested time range (NA for real-time tick stream)
};

// Class to append fields to the data buffer by name.
// Four overloads for the four data types used and the use of an enum to provide a level of type safety.
class QuoteBuffer
{
public:
	virtual int AddQuoteItemToBuffer(eFieldTypeDouble FieldName, double dValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeFloat FieldName, float dValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeLong FieldName, long lValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeULong FieldName, unsigned long lValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeULongLong FieldName, unsigned long long llValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeSecType FieldName, long lValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeShort FieldName, unsigned short siValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeByte FieldName, BYTE siValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeString FieldName, std::string const & rsValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeString FieldName, PCSTR rsValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeWString FieldName, std::wstring const & rsValue);
	virtual int AddQuoteItemToBuffer(eFieldTypeWString FieldName, PCWSTR rsValue);

	template <typename D> void AddHeader(const D& data) {
		m_sBuffer.insert(m_sBuffer.begin(), (BYTE*)&data, (BYTE*)&data + sizeof(D));
	}
	void CompleteQuote() { m_sBuffer.append(1, 0); }
	bool empty() const { return (m_sBuffer.empty()); }
	void * Get() { return m_sBuffer.size() ? reinterpret_cast<void*>(&m_sBuffer[0]) : nullptr; }
	size_t size() { return m_sBuffer.size(); }
	void clear() { m_sBuffer.clear(); }

protected:
	// Data
	std::string m_sBuffer;
};

class ApiHandle
{
	typedef struct st_exchange
	{
		unsigned char m_cIndex;        // unique index identifier
		unsigned char m_cTimeZone;     // as defined in rt_defs=Director.h
		unsigned char m_cStartHour;    // market starting hour
		unsigned char m_cStartMinute;  // market starting minute

		unsigned char m_cCloseHour;    // market closing hour
		unsigned char m_cCloseMinute;  // market closing minute
		unsigned char m_cDaysOfWeek;   // trading days - bitmask (see FDS_DAYBIT in rt_defs=director.h)
		unsigned char m_cDelayMinutes; // default exchange delay - amount of minutes

		unsigned char m_cCurrency;     // base currency for this exchange (see FDS_CURRENCY in rt_defs=director.h)

		wchar_t m_wsShortName[6];          // short description
		wchar_t m_wsLongName[41];          // long description

		//ExchangeDefinition() { memset(this, 0, sizeof *this); }
	}ExchangeStruct;
public:
	ApiHandle();
	~ApiHandle();

	int ProcessSyncMessage(DirectorMessages::MSG& msg);
	virtual bool Initialize(PCWSTR szLogDirectory, unsigned long ulDataProviderID, DirectorSignatures::CallbackProcessMessage pCB);
	//--chenhui
	unsigned long QuoteGet(PCWSTR pSymbol, int AssetType, unsigned char* pFields, LCID locale_id, DirectorSignatures::CallbackQuoteGet pCB, unsigned long UserData, bool bPeriodic);
	// time management 
	static __time32_t get_current_utc_time() {
		__time32_t local = _time32(0); // assumes exchange time being local time
		struct tm utc_tm; _gmtime32_s(&utc_tm, &local);
		return _mkgmtime32(&utc_tm);
	}
	//--end
	virtual int ProcessMesssage(DirectorMessages::MSG &msg);
	virtual void ExchangesGet(std::map<unsigned short, std::wstring>& ex_map);
	long AttributeNumericGet(unsigned long type, int index, int field, long defaultValue);//chenhui

	void testDlg();
	static DWORD WINAPI ThreadEntry(PVOID pParam);
	void Run(void);
public:
	std::map<int, std::wstring> currencies_;
	DP_MESSAGE::CMessageChain *m_pFreeChain;
	DP_MESSAGE::CMessageChain *m_pProcChain;

	//--add 20160904
	DP_MESSAGE::CMessageChain *m_pPeriodicFreeChain;
	DP_MESSAGE::CMessageChain *m_pPeriodicProcChain;
	//--add end
protected:
	DirectorSignatures::CallbackProcessMessage ProcessMessageCallback_;
	unsigned char m_DataProviderID;
	unsigned long m_ulShiftedDataProviderID; /// the data provider ID shifted left 28 bits so that it is ready to be ORed in to the event ID

	// 宿主程序的version，以及parenthwnd
	std::wstring TS_Version_;
	HWND TS_ParentHWND_;
	LCID TS_LocaleId_;

	HANDLE	m_hThreadHandle;
	HANDLE	m_hQuitThread;
	DWORD	m_dwThreadID;
	DirectorMessages::MSG	Info_;



	/*---------------------------------------------------*/
	static const int MAXEXCHANGES = 3;
	ExchangeStruct	m_Exchanges[MAXEXCHANGES];
private:

	void init_currencies();
	void init_messageChain();
	void init_exchanges();

	void init_procthread();
	void wait_procthread();

	DWORD make_eventid(void);
	DWORD add_generic_message(DirectorMessages::MSG &msg);
	DWORD add_connectionstatus_message(DirectorMessages::MSG &msg);

	bool GetMessageIDString(DirectorMessages::MSG &msg,std::string &str);
	int process_attribute_string_get(DirectorMessages::MSG& msg);
	int process_attribute_vstring_get(DirectorMessages::MSG& msg);
	int process_attribute_apiversion_get(DirectorMessages::MSG& msg);

	int process_Msg_TS_Version(DirectorMessages::MSG &msg);
	int process_Msg_TS_LocalId(DirectorMessages::MSG &msg);

	/*---------------------------------------------------*/
	bool proc_generic_message(DP_MESSAGE::CBaseMessage *pm);
	bool proc_connectionstatus_message(DP_MESSAGE::CBaseMessage *pm);
	/*---------------------------------------------------*/
	bool proc_msg_connect(DirectorMessages::MSG &msg);

	//--chenhui
	void initialize_secfield_types();
	void process_msg_reqscanninginfo(DirectorMessages::MSG &msg);
	void ProcessQuoteMsg(DP_MESSAGE::CBaseMessage* msg, bool periodic);
	void ProcessFieldsInMsg(DP_MESSAGE::CBaseMessage* msg, QuoteBuffer& QB, int iResultIndex, LCID locale_id, double criteria = double(0));
	void filter_static_fields(DP_MESSAGE::CQuoteMsg* quote_msg);
	void ProcessRealtimeMsg();
	void ProcessPerodicMsg();
	ePriceWaveForm getSymbolType(std::wstring symbol, BarMsgAttributes* bar_msg_attribute=NULL);
	void initialize_CustomBarIDs();
	//--end

	//--chenhui
	boost::unordered_map<int, long> secfield_types;
	int periodic_intervals;
	DirectorStatus::State ConnectionState_;
	map<int, string> secfieldMap;
	//
	//  Sample Custom Bar Type ID Mapping
	//
	map<wstring, ePriceWaveForm> customBarIDsMap;
	//--end

};

void RLog(const char *str);
void InitApiHandle();

extern ApiHandle *api;