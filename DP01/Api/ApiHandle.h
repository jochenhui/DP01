#pragma once
#include "BaseMessage.h"
#include "MessageChain.h"

//--chenhui
#include "DirectorSignatures.h"
#include <boost/algorithm/string.hpp>
#include <boost/unordered_map.hpp>
//--end

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
	//--end

	//--chenhui
	boost::unordered_map<int, long> secfield_types;
	//--end

};

void RLog(const char *str);
void InitApiHandle();

extern ApiHandle *api;