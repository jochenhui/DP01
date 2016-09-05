#include "stdafx.h"
#include "Logger.h"
#include "ApiHandle.h"
#include "BaseMessage.h"
using namespace NS_FEIMA;
using namespace DP_MESSAGE;
static const double dBasePrice = 1.54321;

void RLog(const char *s);

// 
//  String Buffer Utility for QuoteBuffer
//
void CStringUtility::append_quote_header(std::string& msg_buf, unsigned char field_id, unsigned char field_size, unsigned char field_type)
{
	msg_buf.append(1, field_size); msg_buf.append(1, field_id);  msg_buf.append(1, field_type);
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, std::string const & sValue)
{
	append_quote_header(msg_buf, field_id, QuoteFieldHeaderSize + sValue.size() + 1, field_type);//压入包头的三个字节:[size,field_id,field_type,......]
	msg_buf.append(sValue); msg_buf.append(1, 0);//压入包体数据 和 包尾一个字节的 0 全包 [size,field_id,field_type,...Body...,0]
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, unsigned short value)
{
	append_quote_header(msg_buf, field_id, QuoteFieldHeaderSize + sizeof(unsigned short)+1, field_type);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(unsigned short)); msg_buf.append(1, 0);
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, unsigned char value)
{
	append_quote_header(msg_buf, field_id, QuoteFieldHeaderSize + sizeof(unsigned char)+1, field_type);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(unsigned char)); msg_buf.append(1, 0);
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, long value)
{
	append_quote_header(msg_buf, field_id, QuoteFieldHeaderSize + sizeof(long)+1, field_type);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(long)); msg_buf.append(1, 0);
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, unsigned long value)
{
	append_quote_header(msg_buf, field_id, QuoteFieldHeaderSize + sizeof(unsigned long)+1, field_type);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(unsigned long)); msg_buf.append(1, 0);
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, unsigned long long value)
{
	append_quote_header(msg_buf, field_id, QuoteFieldHeaderSize + sizeof(unsigned long long) + 1, field_type);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(unsigned long long)); msg_buf.append(1, 0);
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, float value)
{
	append_quote_header(msg_buf, field_id, QuoteFieldHeaderSize + sizeof(float)+1, field_type);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(float)); msg_buf.append(1, 0);
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, double value)
{
	append_quote_header(msg_buf, field_id, QuoteFieldHeaderSize + sizeof(double)+1, field_type);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(double)); msg_buf.append(1, 0);
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char field_type, std::wstring const & value)
{
	append_quote_header(msg_buf, field_id, QuoteFieldHeaderSize + (value.size() + 1) * sizeof(wchar_t), field_type);
	msg_buf.append(reinterpret_cast<char*>(const_cast<wchar_t*>(value.c_str())), value.size()*sizeof(wchar_t)); msg_buf.append(sizeof(wchar_t), 0);
}


// 
//  String Buffer Utility for QuoteBuffer (No Field Types)
//
void CStringUtility::append_quote_header(std::string& msg_buf, unsigned char field_id)
{
	msg_buf.append(1, field_id);
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, std::string const & sValue)
{
	append_quote_header(msg_buf, field_id);
	msg_buf.append(sValue);

	// need to null-terminating ANSI strings
	msg_buf.append(1, 0);
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned short value)
{
	append_quote_header(msg_buf, field_id);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(unsigned short));
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned char value)
{
	append_quote_header(msg_buf, field_id);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(unsigned char));
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, long value)
{
	append_quote_header(msg_buf, field_id);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(long));
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned long value)
{
	append_quote_header(msg_buf, field_id);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(unsigned long));
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, unsigned long long value)
{
	append_quote_header(msg_buf, field_id);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(unsigned long long));
}


void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, float value)
{
	append_quote_header(msg_buf, field_id);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(float));
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, double value)
{
	append_quote_header(msg_buf, field_id);
	msg_buf.append(reinterpret_cast<char*>(&value), sizeof(double));
}

void CStringUtility::append_quote_field(std::string& msg_buf, unsigned char field_id, std::wstring const & value)
{
	append_quote_header(msg_buf, field_id);
	msg_buf.append(reinterpret_cast<char*>(const_cast<wchar_t*>(value.c_str())), value.size()*sizeof(wchar_t));

	// need to null-terminating UNICODE strings
	msg_buf.append(sizeof(wchar_t), 0);
}

//
//  QuoteBuffer
//
int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeFloat FieldName, float fValue)
{
	CStringUtility::append_quote_field(m_sBuffer, FieldName, FIELD_FLOAT, fValue);
	return 1;
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeLong FieldName, long lValue)
{
	CStringUtility::append_quote_field(m_sBuffer, FieldName, FIELD_LONG, lValue);
	return 1;
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeULong FieldName, unsigned long lValue)
{
	CStringUtility::append_quote_field(m_sBuffer, FieldName, FIELD_ULONG, lValue);
	return 1;
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeULongLong FieldName, unsigned long long llValue)
{
	CStringUtility::append_quote_field(m_sBuffer, FieldName, FIELD_ULONGLONG, llValue);
	return 1;
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeSecType FieldName, long lValue)
{
	CStringUtility::append_quote_field(m_sBuffer, FieldName, FIELD_SECTYPE, lValue);
	return 1;
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeShort FieldName, unsigned short siValue)
{
	CStringUtility::append_quote_field(m_sBuffer, FieldName, FIELD_SHORT, siValue);
	return 1;
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeByte FieldName, BYTE siValue)
{
	CStringUtility::append_quote_field(m_sBuffer, FieldName, FIELD_BYTE, siValue);
	return 1;
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeString FieldName, string const & rsValue)
{
	CStringUtility::append_quote_field(m_sBuffer, FieldName, FIELD_LPSTR, rsValue);
	return 1;
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeString FieldName, PCSTR rsValue)
{
	return AddQuoteItemToBuffer(FieldName, string(rsValue));
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeWString FieldName, wstring const & rsValue)
{
	CStringUtility::append_quote_field(m_sBuffer, FieldName, FIELD_LPWSTR, rsValue);
	return 1;
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeWString FieldName, PCWSTR rsValue)
{
	return AddQuoteItemToBuffer(FieldName, wstring(rsValue));
}

int QuoteBuffer::AddQuoteItemToBuffer(eFieldTypeDouble FieldName, double dValue)
{
	CStringUtility::append_quote_field(m_sBuffer, FieldName, FIELD_DOUBLE, dValue);
	return 1;
}

//
//---ApiHandle
//
DWORD WINAPI ApiHandle::ThreadEntry(PVOID pParam)
{
	ApiHandle *pThis;
	pThis = (ApiHandle *)pParam;
	RLog("Thread entry.");
	pThis->Run();
	RLog("Thread exit.");
	return 0;
}

void  ApiHandle::ProcessRealtimeMsg()
{
	RLog(" ---- ProcessRealtimeMsg ---- ");
	CBaseMessage *pm;
	bool bQuit;
	bool bRet;

	bQuit = false;
	while (bQuit == false)
	{
		bRet = m_pProcChain->WaitNew(&bQuit, m_hQuitThread);
		if (bRet == false)
		{
			RLog("Wait new found quit.");
			continue;
		}
		RLog("get something.");
		bRet = m_pProcChain->Lock(&bQuit, m_hQuitThread);
		if (bRet == false)
		{
			continue;
		}
		pm = m_pProcChain->Pop_NoLock();
		if (pm)
		{

			switch (pm->m_msgType)
			{
			case CBaseMessage::Generic:  //消息处理
				proc_generic_message(pm);
				break;
			case CBaseMessage::ConnectionStatus:
				proc_connectionstatus_message(pm);
				break;
			case CBaseMessage::quote:
				ProcessQuoteMsg(pm, false);
				break;
			}
		}
		else
		{
			RLog("Popnothing!");
		}
		m_pProcChain->UnLock();
		pm->SetFreeMessage();
		m_pFreeChain->Push(pm);
	}
	m_pProcChain->UnLock();
}

void  ApiHandle::ProcessPerodicMsg()
{
	RLog(" ---- ProcessPerodicMsg ---- ");
	CBaseMessage *pm;
	bool bQuit;
	bool bRet;

	bQuit = false;
	while (bQuit == false)
	{
		bRet = m_pPeriodicProcChain->WaitNew(&bQuit, m_hQuitThread);
		if (bRet == false)
		{
			RLog("Wait new found quit.");
			continue;
		}
		RLog("get something.");
		bRet = m_pPeriodicProcChain->Lock(&bQuit, m_hQuitThread);
		if (bRet == false)
		{
			continue;
		}
		pm = m_pPeriodicProcChain->Pop_NoLock();
		if (pm)
		{

			switch (pm->m_msgType)
			{
			case CBaseMessage::Generic:  //消息处理
				proc_generic_message(pm);
				break;
			case CBaseMessage::ConnectionStatus:
				proc_connectionstatus_message(pm);
				break;
			case CBaseMessage::quote:
				ProcessQuoteMsg(pm, false);
				break;
			}
		}
		else
		{
			RLog("Popnothing!");
		}
		m_pPeriodicProcChain->UnLock();
		pm->SetFreeMessage();
		m_pPeriodicFreeChain->Push(pm);
	}
	m_pPeriodicProcChain->UnLock();
}
void ApiHandle::Run(void)
{
	ProcessRealtimeMsg();
	if (!(periodic_intervals % PERIODIC_MESSAGE_INTERVAL) && (ConnectionState_ == DirectorStatus::Online)) 
	{
		ProcessPerodicMsg();
	}

}
void ApiHandle::initialize_CustomBarIDs()
{
	//
	//  Adding supported custom bar types to map
	//  Custom bar type identifiers will be converted to all upper case by TS/CAL
	//

	customBarIDsMap[L"TURNOVER"] = eTURNOVER;
	//  ...
	//  ...
}

ePriceWaveForm ApiHandle::getSymbolType(std::wstring symbol, BarMsgAttributes* bar_msg_attribute)
{
	if (bar_msg_attribute) {
		//
		//  supporting the message driven custom tick/bar types
		//
		map<wstring, ePriceWaveForm>::iterator bar_it = customBarIDsMap.find(bar_msg_attribute->m_CustomBarId);
		if (bar_it != customBarIDsMap.end())
			return bar_it->second;

		// API tick/bar callback options
		if (bar_msg_attribute->m_loadOptions & WOWRT_LOAD_OPEN_INTEREST_BARS)
			return eOPEN_INTEREST;
		if (bar_msg_attribute->m_loadOptions & WOWRT_LOAD_TWAP_BARS)
			return eTWAP;
	}

	if (symbol == L"MOC:CONST")
		return eSYSTEMATIC;
	else if (symbol == L"MOC:SIN")
		return eSIN;
	else if (symbol == L"MOC:LVL2")
		return eLVL2;
	else if (symbol.find(L"MOC:CCA") != std::wstring::npos) //返回=std::wstring::npos表明查找没有匹配
		return eCCA;
	else if (symbol.find(L"MOC:FX") != std::wstring::npos)
		return eFOREX;
	else if (symbol.find(L"MOC:IDX") != std::wstring::npos)
		return eINDEX;

	//  debugging symbols
	else if (symbol.find(L"ERROOO") != std::wstring::npos)
		return eERROOO;
	else if (symbol.find(L"ERRDUP") != std::wstring::npos)
		return eERRDUP;
	else if (symbol.find(L"ERRMISS1") != std::wstring::npos)
		return eERRMISS1;
	else if (symbol.find(L"ERRMISS2") != std::wstring::npos)
		return eERRMISS2;
	else if (symbol.find(L"ERRMISS3") != std::wstring::npos)
		return eERRMISS3;
	else if (symbol.find(L"ERRMISS4") != std::wstring::npos)
		return eERRMISS4;

	return eRANDOM;
}
bool ApiHandle::proc_generic_message(CBaseMessage *pm)
{
	DirectorMessages::MSG &msg = dynamic_cast<CGenericMsg*>(pm)->msg;
	switch (msg.MessageId_)
	{
	case DirectorMessages::Msg_Connect:
		proc_msg_connect(msg);
		break;
	case DirectorMessages::Msg_ReqScanningInfo:
		process_msg_reqscanninginfo(msg);
		break;
	default:
		return false;
	}
	return true;
}

bool ApiHandle::proc_connectionstatus_message(DP_MESSAGE::CBaseMessage * pm)
{
	switch(dynamic_cast<CConnectionStatusMsg*>(pm)->m_ConnectionStatus)
	{
	case DirectorStatus::Online:
		RLog("proc_connectionstatus_message(Online)");
		break;
	case DirectorStatus::Offline: // close our real-time events
		RLog("proc_connectionstatus_message(Offline)");
		break;
	default:
		RLog("proc_connectionstatus_message:Unknown");
	}
	return true;
}

#include "Logon.h"
void ApiHandle::testDlg(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	Logon cDlg(NULL);

	cDlg.DoModal();
	return ;
}

static int mockdebug = 1;//--增加登录模式 20160831

bool ApiHandle::proc_msg_connect(DirectorMessages::MSG &msg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	wchar_t m_csUserID[20];
	wchar_t m_csPassword[20];
	int iDlgRet;

	if (mockdebug)
	{
		wcscpy_s(m_csUserID, L"cffexmock01");
		wcscpy_s(m_csPassword, L"b2btesting");
		iDlgRet = IDOK;
	}
	else
	{
		Logon cDlg(CWnd::FromHandle(::IsWindow(TS_ParentHWND_) ? TS_ParentHWND_ : GetForegroundWindow()));
		iDlgRet = cDlg.DoModal();
		if (iDlgRet == IDOK)
		{
			wcscpy_s(m_csUserID, (LPCWSTR)cDlg.m_csUserID);
			wcscpy_s(m_csPassword, (LPCWSTR)cDlg.m_csPassword);
		}
	}

	char m_sRet[2048];
	char m_sTmp[1024];

	sprintf_s(m_sRet, "proc_msg_connect(");
	Info_.clear_attributes();
	if (iDlgRet == IDOK) 
	{
		Info_.MessageId_ = DirectorMessages::Msg_Connect;
		Info_.add_attribute(DirectorTags::UserName, (LPCWSTR)m_csUserID);
		Info_.add_attribute(DirectorTags::Password, (LPCWSTR)m_csPassword);

		USES_CONVERSION;
		sprintf_s(m_sTmp, "IDOK,%s,", T2A(m_csUserID));
		strcat_s(m_sRet, m_sTmp);
		sprintf_s(m_sTmp, "%s)", T2A(m_csPassword));
		strcat_s(m_sRet, m_sTmp);
		RLog(m_sRet);

		std::string token("12345678-1234-1234-1234-0123456789AB");
		token.push_back(0); // if you absolutely need a null terminated character to be passed ...
		Info_.add_attribute(DirectorTags::AuthToken, token); // place your own token here!
	}
	else 
	{
		strcat_s(m_sRet, "IDCancel)");
		RLog(m_sRet);

		Info_.MessageId_ = DirectorMessages::Msg_ConnectionStatus;
		Info_.add_attribute(DirectorTags::ConnectionStatus, DirectorStatus::Shutdown);
	}
	if (ProcessMessageCallback_ != nullptr)
	{
		ProcessMessageCallback_(Info_);
	}
	return true;
}
void ApiHandle::process_msg_reqscanninginfo(DirectorMessages::MSG &msg)
{
	char m_sRet[2048];
	//char m_sTmp[1024];

	sprintf_s(m_sRet, "process_msg_reqscanninginfo");
	RLog(m_sRet);

	int event = 0;
	msg.get_attribute(DirectorTags::Msg_Event, event);//bug here!!

	LCID locale_id = LCID(1033);
	msg.get_attribute(DirectorTags::Msg_LocaleId, locale_id);

	unsigned long UserData;
	msg.get_attribute(DirectorTags::Msg_Data, UserData);

	// return mock scanning dictionary
	vector<HelperScanningInfoEntry> entries;
	vector<wstring> scanning_dictionary;


	switch (locale_id) {
	case 2052:
		// mock scanning dictionary in Simplified Chinese
		entries.push_back(HelperScanningInfoEntry(L"代码说明", L"公司信息|代码说明", L"^2", FIELD_LPWSTR, SCANNING_FIELD_PROPERTY_DISPLAY_ONLY, L"代码说明"));
		entries.push_back(HelperScanningInfoEntry(L"下季度分红发放日", L"分红派息|下季度分红发放日", L"DIVNQPDT", FIELD_DATE_TIME, SCANNING_FIELD_PROPERTY_NONE, L"下季度分红发放日期"));
		entries.push_back(HelperScanningInfoEntry(L"卖价", L"价格|卖价", L"^85", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"卖价"));
		entries.push_back(HelperScanningInfoEntry(L"买价", L"价格|买价", L"^84", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"买价"));
		entries.push_back(HelperScanningInfoEntry(L"市价", L"价格|市价", L"^4", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"市价"));
		entries.push_back(HelperScanningInfoEntry(L"收盘价", L"价格|收盘价|收盘价", L"^78", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"当天收盘价"));
		entries.push_back(HelperScanningInfoEntry(L"收盘价-1d", L"价格|收盘价|收盘价 (1 天前)", L"^5", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"收盘价 1 天前"));
		entries.push_back(HelperScanningInfoEntry(L"收盘价-2d", L"价格|收盘价|收盘价 (2 天前)", L"^78[2]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"收盘价 2 天前"));
		entries.push_back(HelperScanningInfoEntry(L"收盘价-3d", L"价格|收盘价|收盘价 (3 天前)", L"^78[3]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"收盘价 3 天前"));
		entries.push_back(HelperScanningInfoEntry(L"收盘价-4d", L"价格|收盘价|收盘价 (4 天前)", L"^78[4]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"收盘价 4 天前"));
		entries.push_back(HelperScanningInfoEntry(L"收盘价-5d", L"价格|收盘价|收盘价 (5 天前)", L"^78[5]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"收盘价 5 天前"));
		entries.push_back(HelperScanningInfoEntry(L"收盘价-10d", L"价格|收盘价|收盘价 (10 天前)", L"^78[10]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"收盘价 10 天前"));
		entries.push_back(HelperScanningInfoEntry(L"开盘价", L"价格|开盘价|开盘价", L"^12", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"当天开盘价"));
		entries.push_back(HelperScanningInfoEntry(L"开盘价-1d", L"价格|开盘价|开盘价 (1 天前)", L"^12[1]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"开盘价 1 天前"));
		entries.push_back(HelperScanningInfoEntry(L"开盘价-2d", L"价格|开盘价|开盘价 (2 天前)", L"^12[2]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"开盘价 2 天前"));
		entries.push_back(HelperScanningInfoEntry(L"开盘价-3d", L"价格|开盘价|开盘价 (3 天前)", L"^12[3]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"开盘价 3 天前"));
		entries.push_back(HelperScanningInfoEntry(L"开盘价-4d", L"价格|开盘价|开盘价 (4 天前)", L"^12[4]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"开盘价 4 天前"));
		entries.push_back(HelperScanningInfoEntry(L"开盘价-5d", L"价格|开盘价|开盘价 (5 天前)", L"^12[5]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"开盘价 5 天前"));
		entries.push_back(HelperScanningInfoEntry(L"开盘价-10d", L"价格|开盘价|开盘价 (10 天前)", L"^12[10]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"开盘价 10 天前"));
		break;
	case 1033:
	default:
		// mock scanning dictionary in English
		entries.push_back(HelperScanningInfoEntry(L"Description", L"Company Profile|Description", L"^2", FIELD_LPWSTR, SCANNING_FIELD_PROPERTY_DISPLAY_ONLY, L"Symbol Description"));
		entries.push_back(HelperScanningInfoEntry(L"DivNxtQtrPayDate", L"Dividends|Dividend Next Qtr Pay Date", L"DIVNQPDT", FIELD_DATE_TIME, SCANNING_FIELD_PROPERTY_NONE, L"Dividend Next Quarter Pay Date"));
		entries.push_back(HelperScanningInfoEntry(L"Ask", L"Price|Ask", L"^85", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Ask price"));
		entries.push_back(HelperScanningInfoEntry(L"Bid", L"Price|Bid", L"^84", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Bid price"));
		entries.push_back(HelperScanningInfoEntry(L"Last", L"Price|Last", L"^4", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Last price"));
		entries.push_back(HelperScanningInfoEntry(L"Close", L"Price|Close|Close", L"^78", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Close price"));
		entries.push_back(HelperScanningInfoEntry(L"Close-1d", L"Price|Close|Close (1 Day Ago)", L"^5", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Close price 1 day ago"));
		entries.push_back(HelperScanningInfoEntry(L"Close-2d", L"Price|Close|Close (2 Days Ago)", L"78[2]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Close price 2 days ago"));
		entries.push_back(HelperScanningInfoEntry(L"Close-3d", L"Price|Close|Close (3 Days Ago)", L"78[3]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Close price 3 days ago"));
		entries.push_back(HelperScanningInfoEntry(L"Close-4d", L"Price|Close|Close (4 Days Ago)", L"78[4]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Close price 4 days ago"));
		entries.push_back(HelperScanningInfoEntry(L"Close-5d", L"Price|Close|Close (5 Days Ago)", L"78[5]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Close price 5 days ago"));
		entries.push_back(HelperScanningInfoEntry(L"Close-10d", L"Price|Close|Close (10 Days Ago)", L"78[10]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Close price 10 days ago"));
		entries.push_back(HelperScanningInfoEntry(L"Open", L"Price|Open|Open", L"^12", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Open price"));
		entries.push_back(HelperScanningInfoEntry(L"Open-1d", L"Price|Open|Open (1 Day Ago)", L"^12[1]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Open price 1 days ago"));
		entries.push_back(HelperScanningInfoEntry(L"Open-2d", L"Price|Open|Open (2 Day Ago)", L"^12[2]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Open price 2 days ago"));
		entries.push_back(HelperScanningInfoEntry(L"Open-3d", L"Price|Open|Open (3 Day Ago)", L"^12[3]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Open price 3 days ago"));
		entries.push_back(HelperScanningInfoEntry(L"Open-4d", L"Price|Open|Open (4 Day Ago)", L"^12[4]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Open price 4 days ago"));
		entries.push_back(HelperScanningInfoEntry(L"Open-5d", L"Price|Open|Open (5 Day Ago)", L"^12[5]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Open price 5 days ago"));
		entries.push_back(HelperScanningInfoEntry(L"Open-10d", L"Price|Open|Open (10 Day Ago)", L"^12[10]", FIELD_DOUBLE, SCANNING_FIELD_PROPERTY_NONE, L"Open price 10 days ago"));
		break;
	}

	for (auto it_entry(entries.begin()); it_entry != entries.end(); it_entry++) {
		scanning_dictionary.push_back(it_entry->getEntryString());
	}

	//
	//  Return Extended Session string and Holiday data to TS/CAL
	//
	DirectorMessages::MSG m(DirectorMessages::Msg_ReqScanningInfo);

	// link request event identifier
	m.add_attribute(DirectorTags::Msg_Event, event);

	// attach return code
	int err_code = ERR_SUCCESS;

	m.add_attribute(DirectorTags::Msg_ErrorCode, CErrorCode(err_code));

	// attach scanning dictionary
	m.add_attribute(DirectorTags::Msg_VectorUnicodeString, scanning_dictionary);

	// attach user data
	m.add_attribute(DirectorTags::Msg_Data, UserData);

	// callback
	if (ProcessMessageCallback_ != nullptr) {
		ProcessMessageCallback_(m);
	}
}
void ApiHandle::ProcessFieldsInMsg(DP_MESSAGE::CBaseMessage* msg, QuoteBuffer& QB, int iResultIndex, LCID locale_id, double criteria)
{
	char pszBuf[1000] = { "---- ProcessFieldsInMsg ----" };
	RLog(pszBuf);
	for (auto it = msg->fields.begin(); it != msg->fields.end(); ++it) 
	{
		unsigned char field_id = static_cast<unsigned char>(*it);
		map<int, string>::iterator secfield_iter = secfieldMap.find(field_id);
		switch (field_id) {
		case RT_SECFIELD_NAME: // string
		{
			ostringstream osSymbolExtended;
			osSymbolExtended << CW2A(msg->symbol.c_str());

			//
			// If TradeStation queries security list with partial symbol name,
			// - MockShim check if the query uses exact symbol name. For this case, 
			//   orginal symbol name in the request is returned.
			// - If the query uses partial symbol name to get a list of symbols, 
			//   MockShim returns different symbol names with numeric appendixes.
			//
			// If TradeStation queries quote with unique symbol name,
			// - MockShim returns the original symbol name in the request.
			//
			if (msg->m_msgType == CBaseMessage::SecurityList) {
				if (msg->callback_argument != SYMBOL_LIST_EXACT_NAME) {
					osSymbolExtended << setfill('0') << setw(2) << iResultIndex;
				}
			}
			QB.AddQuoteItemToBuffer(SECFIELD_NAME, osSymbolExtended.str());
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), (osSymbolExtended.str()).c_str());
			RLog(pszBuf);
		}
			break;

		case RT_SECFIELD_COUNTRY_CODE:
			QB.AddQuoteItemToBuffer(SECFIELD_COUNTRY_CODE, "KR");
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "KR");
			RLog(pszBuf);
			break;

		case RT_SECFIELD_CURRDESC: // string
		case RT_SECFIELD_ROOTSYMBOL:
		{
			switch (field_id) {
				case RT_SECFIELD_CURRDESC:
					QB.AddQuoteItemToBuffer(SECFIELD_CURRDESC, "MOCK Symbol Description");
					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "MOCK Symbol Description");
					RLog(pszBuf);
					break;
				case RT_SECFIELD_ROOTSYMBOL:
					QB.AddQuoteItemToBuffer(SECFIELD_ROOTSYMBOL, CW2A(msg->symbol.c_str()));
					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), CW2A(msg->symbol.c_str()));
					RLog(pszBuf);
					break;
			}
		}
			break;

		case RT_SECFIELD_DESCRIPTION: // wstring
		switch (locale_id) {
			case 1041:  // Japanese
				QB.AddQuoteItemToBuffer(SECFIELD_DESCRIPTION, L"[Unicode] コード説明");
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "[Unicode] コード説明");
				RLog(pszBuf);
				break;
			case 1042:  // Korean
				QB.AddQuoteItemToBuffer(SECFIELD_DESCRIPTION, L"[Unicode] 코드 설명");
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "[Unicode] 코드 설명");
				RLog(pszBuf);
				break;
			case 1028:  // Traditional Chinese
				QB.AddQuoteItemToBuffer(SECFIELD_DESCRIPTION, L"[Unicode] 代碼描述");
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "[Unicode] 代碼描述");
				RLog(pszBuf);
				break;
			case 2052:  // Simplified Chinese
				QB.AddQuoteItemToBuffer(SECFIELD_DESCRIPTION, L"[Unicode] 代码描述");
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "[Unicode] 代码描述");
				RLog(pszBuf);
				break;
			default:    // 1033 - US English
				QB.AddQuoteItemToBuffer(SECFIELD_DESCRIPTION, L"[Unicode] Symbol Description");
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "[Unicode] Symbol Description");
				RLog(pszBuf);
		}
		break;

		case RT_SECFIELD_EXCHANGEINDEX: // short
		case RT_SECFIELD_DAILY_LIMIT:
		{
			unsigned short value = 0;
			switch (field_id) {
			case RT_SECFIELD_EXCHANGEINDEX: value = TICKREC_BASE::MakeLocalExchangeIndex(m_Exchanges[0].m_cIndex);
				QB.AddQuoteItemToBuffer(SECFIELD_EXCHANGEINDEX, value);
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%u", field_id, secfield_iter->second.c_str(), value);
				RLog(pszBuf);
				break;
			case RT_SECFIELD_DAILY_LIMIT: value = 10000;
				QB.AddQuoteItemToBuffer(SECFIELD_DAILY_LIMIT, value);
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%u", field_id, secfield_iter->second.c_str(), value);
				RLog(pszBuf);
				break;
			}
		}
			break;

		case RT_SECFIELD_TRADE_EXCHANGE: // unsigned short
		{
			unsigned short value = EXCHANGE_NYSE;
			QB.AddQuoteItemToBuffer(SECFIELD_TRADEEXCHANGE, value);
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "EXCHANGE_NYSE");
			RLog(pszBuf);
		}
		break;

		case RT_SECFIELD_BID_EXCHANGE: // unsigned short
		{
			unsigned short value = EXCHANGE_USBA;
			QB.AddQuoteItemToBuffer(SECFIELD_BIDEXCHANGE, value);
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "EXCHANGE_USBA");
			RLog(pszBuf);
		}
		break;

		case RT_SECFIELD_ASK_EXCHANGE: // unsigned short
		{
			unsigned short value = EXCHANGE_NASDQ;
			QB.AddQuoteItemToBuffer(SECFIELD_ASKEXCHANGE, value);
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "EXCHANGE_NASDQ");
			RLog(pszBuf);
		}
		break;

		case RT_SECFIELD_NAME_EXT_W:
		{
			//
			// Name Extension field is REQUIRED to use Unicode format.
			//
			QB.AddQuoteItemToBuffer(SECFIELD_NAME_EXT, L"(实时[Unicode])");
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "(实时[Unicode])");
			RLog(pszBuf);
		}
		break;

		case RT_SECFIELD_HIGH:
		case RT_SECFIELD_LOW:
		case RT_SECFIELD_OPEN:
		case RT_SECFIELD_CLOSE:
		case RT_SECFIELD_12MONTHHIGH:
		case RT_SECFIELD_12MONTHLOW:
		case RT_SECFIELD_PREVCLOSE:
		{
			float fValue = float(rand() % 1000) / float(100);//0~9.99
			QB.AddQuoteItemToBuffer(eFieldTypeFloat(field_id), fValue);
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), fValue);
			RLog(pszBuf);
		}
		break;

		case RT_SECFIELD_ASSETTYPE: // long
		case RT_SECFIELD_BASECODE:
		case RT_SECFIELD_BASE_LOCALE_ID:
		case RT_SECFIELD_BITFLAGS:
		case RT_SECFIELD_CURRENCY:
		case RT_SECFIELD_LOCALE_ID:
		case RT_SECFIELD_MINMOVE:
		case RT_SECFIELD_POINTVALUE:
		case RT_SECFIELD_TOTALVOL:
		{
			unsigned long dwValue = 0;

			switch (field_id) {
			case RT_SECFIELD_LOCALE_ID:  { // also used for defining symbol's price data currency 
				unsigned long USD = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
				unsigned long JPY = MAKELCID(MAKELANGID(LANG_JAPANESE, SUBLANG_DEFAULT), SORT_DEFAULT);
				unsigned long CNY = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SINGAPORE), SORT_DEFAULT);
				unsigned long EUR = MAKELCID(MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN), SORT_DEFAULT);
				unsigned long SAR = MAKELCID(MAKELANGID(LANG_ARABIC, SUBLANG_DEFAULT), SORT_DEFAULT);
				unsigned long KRW = MAKELCID(MAKELANGID(LANG_KOREAN, SUBLANG_DEFAULT), SORT_DEFAULT);
				QB.AddQuoteItemToBuffer(SECFIELD_LOCALE_ID, KRW);
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), KRW);
				RLog(pszBuf);
				break; }
			case RT_SECFIELD_ASSETTYPE: {
				ePriceWaveForm assetType = getSymbolType(msg->symbol.c_str());
				switch (assetType) {
				case eFOREX:
					dwValue = RTType_Forex;
					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "RTType_Forex");
					break;
				case eINDEX:
					dwValue = RTType_Index;
					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "RTType_Index");
					break;
				default:
					dwValue = RTType_Stock;
					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), "RTType_Stock");
				}
				RLog(pszBuf);
				QB.AddQuoteItemToBuffer(SECFIELD_ASSETTYPE, dwValue);//资产类型						
			}
			break;
			case RT_SECFIELD_BASE_LOCALE_ID: // only used for forex symbols - defines the base currency (ex. EURUSD => EUR)
				// dwValue = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT); 
				dwValue = MAKELCID(MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN), SORT_DEFAULT);
				QB.AddQuoteItemToBuffer(SECFIELD_BASE_LOCALE_ID, dwValue);
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), dwValue);
				RLog(pszBuf);
				break;
			case RT_SECFIELD_BASECODE:
				dwValue = E2DECIMALS | BASECODE_DISPLAY_REDUCE_FRACTION;
				QB.AddQuoteItemToBuffer(SECFIELD_BASECODE, dwValue);
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), dwValue);
				RLog(pszBuf);
				break;
			case RT_SECFIELD_CURRENCY:
				dwValue = FDS_CURRENCY_KRW; // usually should match symbol's Locale_ID country's currency
				QB.AddQuoteItemToBuffer(SECFIELD_CURRENCY, dwValue);
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), dwValue);
				RLog(pszBuf);
				break;
			case RT_SECFIELD_MINMOVE:
				QB.AddQuoteItemToBuffer(SECFIELD_MINMOVE, float(1.0));
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), float(1.0));
				RLog(pszBuf);
				break;
			case RT_SECFIELD_POINTVALUE: // leave dwValue at 0..     
				QB.AddQuoteItemToBuffer(SECFIELD_POINTVALUE, float(dwValue));
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), dwValue);
				RLog(pszBuf);
				break;
			case RT_SECFIELD_TOTALVOL:
				dwValue = (unsigned long)(1000.00 * fmod(rand() % 100, dBasePrice)); // should eventually be tied with symbology (ex. MOC:SIN100, MOC:RW500, etc.);  
				QB.AddQuoteItemToBuffer(SECFIELD_TOTALVOL, dwValue);
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), dwValue);
				RLog(pszBuf);
				break;
			}
		}
		break;

		case RT_SECFIELD_CALL_VOLUME:
			QB.AddQuoteItemToBuffer(SECFIELD_CALL_VOLUME, DWORD(rand() % 1000));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%ld", field_id, secfield_iter->second.c_str(), DWORD(rand() % 1000));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_PUT_VOLUME:
			QB.AddQuoteItemToBuffer(SECFIELD_PUT_VOLUME, DWORD(rand() % 1000));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%ld", field_id, secfield_iter->second.c_str(), DWORD(rand() % 1000));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_LASTASKTIME:
		case RT_SECFIELD_LASTBIDTIME:
		case RT_SECFIELD_LASTTRADETIME:
		{
			eFieldTypeLong eType = SECFIELD_LASTTRADETIME;

			switch (field_id) {
			case RT_SECFIELD_LASTASKTIME: eType = SECFIELD_LASTASKTIME; break;
			case RT_SECFIELD_LASTBIDTIME: eType = SECFIELD_LASTBIDTIME; break;
			}

			DWORD dwValue = ADJUST_FROM_1970_TO_1900(get_current_utc_time());
			QB.AddQuoteItemToBuffer(eType, dwValue);
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), dwValue);
			RLog(pszBuf);
		}
			break;

		case RT_SECFIELD_ASKSIZE:
		case RT_SECFIELD_BIDSIZE:
		case RT_SECFIELD_TRADEVOL:
		{
			eFieldTypeLong eType = SECFIELD_TRADEVOL;
			switch (field_id) {
			case RT_SECFIELD_BIDSIZE: eType = SECFIELD_BIDSIZE; break;
			case RT_SECFIELD_ASKSIZE: eType = SECFIELD_ASKSIZE; break;
			}
			unsigned long lValue = static_cast<long>(rand() % 50);
			QB.AddQuoteItemToBuffer(eType, lValue);
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), lValue);
			RLog(pszBuf);
		}
		break;
		case RT_SECFIELD_ASK_EX:
		case RT_SECFIELD_BID_EX:
		case RT_SECFIELD_LASTTRADE:
		case RT_SECFIELD_VWAP:
		case RT_SECFIELD_TWAP:
		case RT_SECFIELD_PRICE_LOWLIMIT:
		case RT_SECFIELD_PRICE_HIGHLIMIT:
		{
			static long quote_value = 0;
			static bool quote_incr = true;
			double value = 0;
			eFieldTypeDouble eType = SECFIELD_LASTTRADE;

			// In MockShim, market price limitations are put together with last trade to emulate the range.
			eFieldTypeULongLong eTypeLimit = SECFIELD_PRICE_LOWLIMIT;

			switch (field_id) {
			case RT_SECFIELD_ASK_EX: eType = SECFIELD_ASK_EX; break;
			case RT_SECFIELD_BID_EX: eType = SECFIELD_BID_EX; break;
			case RT_SECFIELD_VWAP: eType = SECFIELD_VWAP; break;
			case RT_SECFIELD_TWAP: eType = SECFIELD_TWAP; break;
			case RT_SECFIELD_PRICE_LOWLIMIT: eTypeLimit = SECFIELD_PRICE_LOWLIMIT; break;
			case RT_SECFIELD_PRICE_HIGHLIMIT: eTypeLimit = SECFIELD_PRICE_HIGHLIMIT; break;
			}

			// Simulate quotes here.
			//  If the symbol is "MOC:SIN", generate a sine wave. Otherwise, generate a (pseudo) random number.
			if (msg->symbol == L"MOC:SIN") {
				value = 1;
			}
			else if (msg->symbol == L"MOC:SQR1") {
				switch (eType) {
				case SECFIELD_LASTTRADE:
				case SECFIELD_VWAP:
				case SECFIELD_TWAP:   value = (quote_value == 10) ? quote_incr = false, --quote_value : (quote_value == 1) ? quote_incr = true, ++quote_value : quote_incr ? ++quote_value : --quote_value; break;
				case SECFIELD_ASK_EX: value = (quote_value)+1; break;
				case SECFIELD_BID_EX: value = (quote_value)-1; break;
				default:
					if (field_id == RT_SECFIELD_PRICE_LOWLIMIT || field_id == RT_SECFIELD_PRICE_HIGHLIMIT) {
						value = (quote_value == 10) ? quote_incr = false, --quote_value : (quote_value == 1) ? quote_incr = true, ++quote_value : quote_incr ? ++quote_value : --quote_value;
					}
					break;
				}
			}
			else if (msg->symbol == L"MOC:LVL2") {
				switch (eType) {
				case SECFIELD_LASTTRADE:
				case SECFIELD_PRICE_LOWLIMIT:
				case SECFIELD_PRICE_HIGHLIMIT:
				case SECFIELD_VWAP:
				case SECFIELD_TWAP:   value = 5; break;
				case SECFIELD_ASK_EX: value =10; break;
				case SECFIELD_BID_EX: value = 11; break;
				default:
					if (field_id == RT_SECFIELD_PRICE_LOWLIMIT || field_id == RT_SECFIELD_PRICE_HIGHLIMIT) {
						value = 5;
					}
					break;
				}
			}
			else // other symbols generate
				value = 1;//+ fmod(rand()%100, dBasePrice); // should eventually be tied with symbology (ex. MOC:SIN100, MOC:RW500, etc.)

			// supply random VWAP value for symbol data query
			if ((eType == SECFIELD_VWAP) || (eType == SECFIELD_TWAP)) {
				value *= 1.0 + ((rand() % 2) ? 1 : -1) * double(rand() % 100) / double(100);//1.0~1.99
			}

			// supply mock trading price low/high limits (unsigned long long type)
			if (field_id == RT_SECFIELD_PRICE_LOWLIMIT || field_id == RT_SECFIELD_PRICE_HIGHLIMIT) {
				unsigned long long limit = (unsigned long long)0;
				if (eTypeLimit == SECFIELD_PRICE_LOWLIMIT)
					limit = (unsigned long long)(value * 0.9 * 100000.0); // 10% below last trade price in integer form
				else if (eTypeLimit == SECFIELD_PRICE_HIGHLIMIT)
					limit = (unsigned long long)(value * 1.1 * 100000.0); // 10% above last trade price in integer form
				QB.AddQuoteItemToBuffer(eTypeLimit, limit);
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%llu", field_id, secfield_iter->second.c_str(), limit);
				RLog(pszBuf);
			}
			else{
				QB.AddQuoteItemToBuffer(eType, value);
				sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), value);
				RLog(pszBuf);
			}
		}
			break;

			// double
		case RT_SECFIELD_MARGIN:
			QB.AddQuoteItemToBuffer(SECFIELD_MARGIN, 0.02);
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), 0.02);
			RLog(pszBuf);
			break;

		case RT_SECFIELD_HOTLIST_CRITERIA:
			//
			//  For Hot Lists
			//  -------------
			//  RT_SECFIELD_HOTLIST_CRITERIA represents the value of criteria field that used by server side 
			//  ranking service to sort the symbols in the Hot List. The Hot List criteria field could be a 
			//  simple data field or a calculated field (such as a technical indicator).
			//  
			QB.AddQuoteItemToBuffer(SECFIELD_HOTLIST_CRITERIA, criteria);
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), criteria);
			RLog(pszBuf);
			break;

		case RT_SECFIELD_PUT_CALL_VOLUME_RATIO:
			QB.AddQuoteItemToBuffer(SECFIELD_PUT_CALL_VOLUME_RATIO, float(rand() % 100) / float(100));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), float(rand() % 100) / float(100));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_OPEN_GAP:
			QB.AddQuoteItemToBuffer(SECFIELD_OPEN_GAP, float(0));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), float(0));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_TURNOVER_RATE:
			QB.AddQuoteItemToBuffer(SECFIELD_TURNOVER_RATE, float(rand() % 100) / float(100));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), float(rand() % 100) / float(100));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_DYNAMIC_PE:
			QB.AddQuoteItemToBuffer(SECFIELD_DYNAMIC_PE, float(rand() % 200) / float(1000));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), float(rand() % 200) / float(1000));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_IOPV:
			QB.AddQuoteItemToBuffer(SECFIELD_IOPV, float(500) + float(rand() % 200));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), float(500) + float(rand() % 200));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_TURNOVER:
			QB.AddQuoteItemToBuffer(SECFIELD_TURNOVER, float(500000) + float(rand() % 500000));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), float(500000) + float(rand() % 500000));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_STRIKE:
		case RT_SECFIELD_UNDERLYINGSYMBOL:
		case RT_SECFIELD_OPTIONTYPE:
		case RT_SECFIELD_EXPIRATIONDATE:
		case RT_SECFIELD_DELIVERABLE:
		case RT_SECFIELD_CFI:
		{
// 			std::string symbol = std::string(CW2A(msg->symbol.c_str()));
// 			std::string suffix = MockStockOptionChain::getOptionSymbolSuffix(symbol);
// 			std::string root = MockStockOptionChain::getOptionSymbolRoot(symbol);
// 			MockStockOptionPtr option = mockoptionchain->findOption(suffix);
// 			if (option) {
// 				option->updateOption(root);
// 				switch (field_id) {
// 				case RT_SECFIELD_STRIKE:
// 					QB.AddQuoteItemToBuffer(SECFIELD_STRIKE, option->strikePrice);
// 					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%f", field_id, secfield_iter->second.c_str(), option->strikePrice);
// 					break;
// 				case RT_SECFIELD_UNDERLYINGSYMBOL:
// 					QB.AddQuoteItemToBuffer(SECFIELD_UNDERLYINGSYMBOL, option->rootname);
// 					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), option->rootname.c_str());
// 					break;
// 				case RT_SECFIELD_OPTIONTYPE:
// 					QB.AddQuoteItemToBuffer(SECFIELD_OPTIONTYPE, option->optionType);
// 					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%u", field_id, secfield_iter->second.c_str(), option->optionType);
// 					break;
// 				case RT_SECFIELD_EXPIRATIONDATE:
// 					QB.AddQuoteItemToBuffer(SECFIELD_EXPIRATIONDATE, static_cast<DWORD>(option->expirationDate));
// 					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), static_cast<DWORD>(option->expirationDate));
// 					break;
// 				case RT_SECFIELD_DELIVERABLE:
// 					QB.AddQuoteItemToBuffer(SECFIELD_DELIVERABLE, option->deliverable);
// 					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%s", field_id, secfield_iter->second.c_str(), option->deliverable.c_str());
// 					break;
// 				case RT_SECFIELD_CFI:
// 					QB.AddQuoteItemToBuffer(SECFIELD_CFI, option->cfi);
// 					sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), option->cfi);
// 					break;
// 				}
// 			}
		//	LOG_SERVICE_HEADER_(pszBuf);
		}
		break;

		case RT_SECFIELD_LASTASKARROW:
			QB.AddQuoteItemToBuffer(SECFIELD_LASTASKARROW, (unsigned short)((rand() % 2) ? 1 : -1));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%u", field_id, secfield_iter->second.c_str(), (unsigned short)((rand() % 2) ? 1 : -1));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_LASTBIDARROW:
			QB.AddQuoteItemToBuffer(SECFIELD_LASTBIDARROW, (unsigned short)((rand() % 2) ? 1 : -1));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%u", field_id, secfield_iter->second.c_str(), (unsigned short)((rand() % 2) ? 1 : -1));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_OPENINTEREST:
		case RT_SECFIELD_CALL_OPEN_INTEREST:
		case RT_SECFIELD_PUT_OPEN_INTEREST:
			QB.AddQuoteItemToBuffer(SECFIELD_OPENINTEREST, long(rand() % 500));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%ld", field_id, secfield_iter->second.c_str(), long(rand() % 500));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_DISPLAYTYPE:
			QB.AddQuoteItemToBuffer(SECFIELD_DISPLAYTYPE, (unsigned long)0);
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%ld", field_id, secfield_iter->second.c_str(), long(0));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_NUMTRADES:
			QB.AddQuoteItemToBuffer(SECFIELD_NUMTRADES, (unsigned long)(rand() % 500));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%ld", field_id, secfield_iter->second.c_str(), long(rand() % 500));
			RLog(pszBuf);
			break;

		case RT_SECFIELD_FIRST_NOTICE_DATE:
			QB.AddQuoteItemToBuffer(SECFIELD_FIRST_NOTICE_DATE, ADJUST_FROM_1970_TO_1900(get_current_utc_time()));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), ADJUST_FROM_1970_TO_1900(get_current_utc_time()));
			RLog(pszBuf);
			break;
		case RT_SECFIELD_DELIVERY_DATE:
			QB.AddQuoteItemToBuffer(SECFIELD_DELIVERY_DATE, ADJUST_FROM_1970_TO_1900(get_current_utc_time()));
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%lu", field_id, secfield_iter->second.c_str(), ADJUST_FROM_1970_TO_1900(get_current_utc_time()));
			RLog(pszBuf);
			break;
		case RT_SECFIELD_8UPDOWNBITPAIRS:
		{
			// generate random 8 pairs of last trade directions for demo
			WORD td8pairs = 0;
			for (int i = 0; i < 8; i++) {
				int td8direction = rand() % 8;
				WORD dirpair = 0;
				if (td8direction < 4) {
					dirpair = TRADE_DIRECTION_NOCHANGE;
				}
				else if (td8direction < 6) {
					dirpair = TRADE_DIRECTION_UPTICK;
				}
				else {
					dirpair = TRADE_DIRECTION_DOWNTICK;
				}
				td8pairs += dirpair << (i * 2);
			}
			QB.AddQuoteItemToBuffer(SECFIELD_8UPDOWNBITPAIRS, td8pairs);
			sprintf(pszBuf, "QuoteGet:fid=%d,fieldname=%s,getvalue=%d", field_id, secfield_iter->second.c_str(), td8pairs);
			RLog(pszBuf);
			}
			break;
		}
	}

}
void ApiHandle::filter_static_fields(DP_MESSAGE::CQuoteMsg* quote_msg)
{

}
void ApiHandle::ProcessQuoteMsg(DP_MESSAGE::CBaseMessage* msg, bool periodic)
{
	static const int FieldHeaderSize = sizeof(unsigned char)* 3;

	CQuoteMsg* quote_msg = dynamic_cast<DP_MESSAGE::CQuoteMsg*>(msg);
	LCID locale_id = quote_msg->locale_id_;

	QuoteBuffer QB;
	ProcessFieldsInMsg(msg, QB, 0, locale_id);
	if (!QB.empty())
	{
		if (!periodic && quote_msg->periodic) 
		{
			// only allow non-static fields
			filter_static_fields(quote_msg);
			//--push to periodic_message
			CBaseMessage *pmsg;
			pmsg = m_pFreeChain->AllocatePop(CBaseMessage::quote);
			if (NULL == pmsg){
				pmsg = new CQuoteMsg(quote_msg->symbol, quote_msg->asset_type, (unsigned char*)quote_msg->fields.c_str(), quote_msg->locale_id_,quote_msg->event,quote_msg->periodic,quote_msg->callback_argument,quote_msg->callback);
			}
			else{
				(dynamic_cast<CQuoteMsg*>(pmsg))->SetQuoteMsg(*quote_msg);
			}
			m_pPeriodicProcChain->Push(pmsg);
			//--push end
		}
		QB.CompleteQuote();
		quote_msg->callback(quote_msg->event, CErrorCode(), Quote_Update, FIELD_UNKNOWN, QB.Get(), 0, quote_msg->callback_argument);
		RLog("  --- quote_msg->callback ---");
	}
	else if (!periodic)
	{
		quote_msg->callback(quote_msg->event, CErrorCode(ERR_INVALID), Quote_Complete, FIELD_UNKNOWN, 0, 0, quote_msg->callback_argument); // cancel event
		RLog("  --- quote_msg->callback ---");
	}
}

void ApiHandle::initialize_secfield_types()
{
#define SECFIELD_MAP_DEFINE(name) secfieldMap.insert(pair<int,string>(name,#name))

	// BYTE fields
	secfield_types[RT_SECFIELD_EXPIRATION_STYLE] = FIELD_BYTE;//77
	secfield_types[RT_SECFIELD_EXPIRY_TYPE] = FIELD_BYTE;//101
	secfield_types[RT_SECFIELD_OPTIONTYPE] = FIELD_BYTE;//44

	// DOUBLE fields
	secfield_types[RT_SECFIELD_ASK_EX] = FIELD_DOUBLE;//85
	secfield_types[RT_SECFIELD_BID_EX] = FIELD_DOUBLE;//84
	secfield_types[RT_SECFIELD_LASTTRADE] = FIELD_DOUBLE;//4
	secfield_types[RT_SECFIELD_MARGIN] = FIELD_DOUBLE;//73
	secfield_types[RT_SECFIELD_VWAP] = FIELD_DOUBLE;//81
	secfield_types[RT_SECFIELD_TWAP] = FIELD_DOUBLE;//129
	secfield_types[RT_SECFIELD_HOTLIST_CRITERIA] = FIELD_DOUBLE;//128

	// FLOAT fields
	secfield_types[RT_SECFIELD_OPEN] = FIELD_FLOAT;//12
	secfield_types[RT_SECFIELD_HIGH] = FIELD_FLOAT;//10
	secfield_types[RT_SECFIELD_LOW] = FIELD_FLOAT;//11
	secfield_types[RT_SECFIELD_CLOSE] = FIELD_FLOAT;//78
	secfield_types[RT_SECFIELD_PREVCLOSE] = FIELD_FLOAT;//5
	secfield_types[RT_SECFIELD_12MONTHHIGH] = FIELD_FLOAT;//27
	secfield_types[RT_SECFIELD_12MONTHLOW] = FIELD_FLOAT;//28
	secfield_types[RT_SECFIELD_STRIKE] = FIELD_FLOAT;//37
	secfield_types[RT_SECFIELD_MINMOVE] = FIELD_FLOAT;//62
	secfield_types[RT_SECFIELD_POINTVALUE] = FIELD_FLOAT;//61
	secfield_types[RT_SECFIELD_OPEN_GAP] = FIELD_FLOAT;//32
	secfield_types[RT_SECFIELD_PUT_CALL_VOLUME_RATIO] = FIELD_FLOAT;//194
	secfield_types[RT_SECFIELD_TURNOVER_RATE] = FIELD_FLOAT;//139
	secfield_types[RT_SECFIELD_DYNAMIC_PE] = FIELD_FLOAT;//138
	secfield_types[RT_SECFIELD_IOPV] = FIELD_FLOAT;//140
	secfield_types[RT_SECFIELD_TURNOVER] = FIELD_FLOAT;//141

	// LONG fields
	secfield_types[RT_SECFIELD_BASECODE] = FIELD_LONG;//60
	secfield_types[RT_SECFIELD_BASE_LOCALE_ID] = FIELD_LONG;//97
	secfield_types[RT_SECFIELD_LOCALE_ID] = FIELD_LONG;//92
	secfield_types[RT_SECFIELD_TOTALVOL] = FIELD_LONG;//15
	secfield_types[RT_SECFIELD_LASTTRADETIME] = FIELD_LONG;//57
	secfield_types[RT_SECFIELD_LASTBIDTIME] = FIELD_LONG;//70
	secfield_types[RT_SECFIELD_LASTASKTIME] = FIELD_LONG;//71
	secfield_types[RT_SECFIELD_CURRENCY] = FIELD_LONG;//34
	secfield_types[RT_SECFIELD_ASKSIZE] = FIELD_LONG;//18
	secfield_types[RT_SECFIELD_BIDSIZE] = FIELD_LONG;//17
	secfield_types[RT_SECFIELD_TRADEVOL] = FIELD_LONG;//16
	secfield_types[RT_SECFIELD_OPENINTEREST] = FIELD_LONG;//39
	secfield_types[RT_SECFIELD_PUT_OPEN_INTEREST] = FIELD_LONG;//195
	secfield_types[RT_SECFIELD_CALL_OPEN_INTEREST] = FIELD_LONG;//196


	// SECTYPE fields
	secfield_types[RT_SECFIELD_ASSETTYPE] = FIELD_SECTYPE;//3

	// ULONG fields
	secfield_types[RT_SECFIELD_CFI] = FIELD_ULONG;//100
	secfield_types[RT_SECFIELD_BITFLAGS] = FIELD_ULONG;//7
	secfield_types[RT_SECFIELD_DISPLAYTYPE] = FIELD_ULONG;//58
	secfield_types[RT_SECFIELD_FIRST_NOTICE_DATE] = FIELD_ULONG;//74
	secfield_types[RT_SECFIELD_DELIVERY_DATE] = FIELD_ULONG;//76
	secfield_types[RT_SECFIELD_EXPIRATIONDATE] = FIELD_ULONG;//47
	secfield_types[RT_SECFIELD_LAST_TRADING_DATE] = FIELD_ULONG;//75
	secfield_types[RT_SECFIELD_NUMOPTIONS] = FIELD_ULONG;//48
	secfield_types[RT_SECFIELD_CALL_VOLUME] = FIELD_ULONG;//193
	secfield_types[RT_SECFIELD_PUT_VOLUME] = FIELD_ULONG;//192
	secfield_types[RT_SECFIELD_NUMTRADES] = FIELD_ULONG;//26


	// SHORT fields
	secfield_types[RT_SECFIELD_EXCHANGEINDEX] = FIELD_SHORT;//8
	secfield_types[RT_SECFIELD_DAILY_LIMIT] = FIELD_SHORT;//63
	secfield_types[RT_SECFIELD_TRADE_EXCHANGE] = FIELD_SHORT;//120
	secfield_types[RT_SECFIELD_BID_EXCHANGE] = FIELD_SHORT;//121
	secfield_types[RT_SECFIELD_ASK_EXCHANGE] = FIELD_SHORT;//122
	secfield_types[RT_SECFIELD_LASTASKARROW] = FIELD_SHORT;//56
	secfield_types[RT_SECFIELD_LASTBIDARROW] = FIELD_SHORT;//59
	secfield_types[RT_SECFIELD_8UPDOWNBITPAIRS] = FIELD_SHORT;//21


	// LPSTR fields
	secfield_types[RT_SECFIELD_NAME] = FIELD_LPSTR;//1
	secfield_types[RT_SECFIELD_CURRDESC] = FIELD_LPSTR;//2
	secfield_types[RT_SECFIELD_ROOTSYMBOL] = FIELD_LPSTR;//41
	secfield_types[RT_SECFIELD_CONVERSION_FORMULAS] = FIELD_LPSTR;//95
	secfield_types[RT_SECFIELD_COUNTRY_CODE] = FIELD_LPSTR;//94
	secfield_types[RT_SECFIELD_DELIVERABLE] = FIELD_LPSTR;//93
	secfield_types[RT_SECFIELD_UNDERLYINGSYMBOL] = FIELD_LPSTR;//42


	// LPWSTR fields
	secfield_types[RT_SECFIELD_DESCRIPTION] = FIELD_LPWSTR;//14
	secfield_types[RT_SECFIELD_NAME_EXT_W] = FIELD_LPWSTR;//119

	// UNSIGNED LONG LONG fields
	secfield_types[RT_SECFIELD_PRICE_LOWLIMIT] = FIELD_ULONGLONG;//144
	secfield_types[RT_SECFIELD_PRICE_HIGHLIMIT] = FIELD_ULONGLONG;//145

	//----
	SECFIELD_MAP_DEFINE(RT_SECFIELD_NAME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CURRDESC);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ASSETTYPE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LASTTRADE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_PREVCLOSE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LASTCHGTIME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_BITFLAGS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_EXCHANGEINDEX);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TRADEEXCHANGE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_HIGH);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LOW);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_OPEN);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CLIENT_LOCALE_ID);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_DESCRIPTION);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TOTALVOL);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TRADEVOL);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_BIDSIZE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ASKSIZE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_BIDEXCHANGE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ASKEXCHANGE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_8UPDOWNBITPAIRS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TRADESTARTTIME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TRADEENDTIME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_EODKEEPDAYS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TICKKEEPDAYS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_NUMTRADES);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_12MONTHHIGH);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_12MONTHLOW);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_NUMNEWSITEMS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_NEWSKEEPDAYS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LASTTRADE_UNDERLYING);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_OPEN_GAP);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_OPEN_GAP_PERCENT);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CURRENCY);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_MINBAR_OPEN);        // backend only - scanner
	SECFIELD_MAP_DEFINE(RT_SECFIELD_MINBAR_CLOSE);       // backend only - scanner
	SECFIELD_MAP_DEFINE(RT_SECFIELD_STRIKE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_MINBAR_VOLUME);      // backend only - scanner
	SECFIELD_MAP_DEFINE(RT_SECFIELD_OPENINTEREST);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_SETTLEMENT);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ROOTSYMBOL);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_UNDERLYINGSYMBOL);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CONTRACTSIZE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_OPTIONTYPE);         // recycle the ID for call put
	SECFIELD_MAP_DEFINE(RT_SECFIELD_OPTLEAPYEAR);        // used to distinguish LEAP or normal option
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ENTITLEEXCHANGE);    // obsolete
	SECFIELD_MAP_DEFINE(RT_SECFIELD_EXPIRATIONDATE);     // qdg change from YEAR to DATE
	SECFIELD_MAP_DEFINE(RT_SECFIELD_NUMOPTIONS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_12MOHIGHMONTH);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_12MOHIGHDAY);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_12MOLOWMONTH);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_12MOLOWDAY);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_DAYS_TO_EXPIRATION);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_OPTION_VALUE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ENTITLEEXCHANGE_EX);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LASTASKARROW);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LASTTRADETIME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_DISPLAYTYPE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LASTBIDARROW);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_BASECODE);   // DisplayType version for TS.COM
	SECFIELD_MAP_DEFINE(RT_SECFIELD_POINTVALUE); // TS.COM
	SECFIELD_MAP_DEFINE(RT_SECFIELD_MINMOVE);    // TS.COM
	SECFIELD_MAP_DEFINE(RT_SECFIELD_DAILY_LIMIT);// TS.COM
	SECFIELD_MAP_DEFINE(RT_SECFIELD_UP_VOLUME);          //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_DOWN_VOLUME);        //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_UNCHANGED_VOLUME);   //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_UP_TICKS);           //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_DOWN_TICKS);         //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_UNCHANGED_TICKS);    //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LASTBIDTIME);        //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LASTASKTIME);        //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CUSIP);              //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_MARGIN);             //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_FIRST_NOTICE_DATE);  //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LAST_TRADING_DATE);  //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_DELIVERY_DATE);      //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_EXPIRATION_STYLE);   //TS.com
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CLOSE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_PREV_OPENINTEREST);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_PREV_TOTALVOL);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_VWAP);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_FUTURETYPE);          // TS.com = Electronic); Pit or Combined
	SECFIELD_MAP_DEFINE(RT_SECFIELD_NAME_EXT);           // retired - used by TS9.2 and older - Ticker name extension i.e. 'delayed); easy-to-borrow); etc..'
	SECFIELD_MAP_DEFINE(RT_SECFIELD_BID_EX); // double support - need to add new field for backward compatibility
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ASK_EX); // double support - need to add new field for backward compatibility
	SECFIELD_MAP_DEFINE(RT_SECFIELD_FILE_RESOLUTION);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_FILE_RESN_QTY);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_FUTVALIDMONTHS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_STRIKE_MULTIPLIER);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_FILE_LASTAVLDATE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_VENDOR_ID);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LOCALE_ID);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_DELIVERABLE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_COUNTRY_CODE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CONVERSION_FORMULAS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CONVERSION_BARS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_BASE_LOCALE_ID);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_DELIVERABLE_QTY);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CONVERSION_FACTOR);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CFI);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_EXPIRY_TYPE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_INDUSTRY_CODE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_SECTOR_NAME); // UNICODE
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_INDUSTRY_NAME); // UNICODE
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_SECTCLASS_CODE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_SECTCLASS_NAME); // UNICODE
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_OPENTIME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_HIGHTIME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_LOWTIME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_LASTTIME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_MINPRICE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_MAXPRICE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_UNITOFTRADE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_TURNOVER);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_BIDTYPE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ASKTYPE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TRADETYPE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_EX_RIGHT);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_NAME_EXT_W);         // Ticker name extension i.e. 'delayed); easy-to-borrow); etc..'
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TRADE_EXCHANGE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_BID_EXCHANGE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ASK_EXCHANGE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_EXCHANGE_SUFFIX);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_TICK_SIZE_TABLE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ABBREVIATION); // UNICODE
	SECFIELD_MAP_DEFINE(RT_SECFIELD_SHORT_DESCRIPTION); // UNICODE
	SECFIELD_MAP_DEFINE(RT_SECFIELD_ALIAS); // UNICODE
	SECFIELD_MAP_DEFINE(RT_SECFIELD_HOTLIST_CRITERIA); // 128
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TWAP);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_AM_CLOSE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_PM_OPEN);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_AM_VOLUME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_AM_TRADES);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_AM_UP_TICKS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_AM_DOWN_TICKS);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_AM_TURNOVER);

	SECFIELD_MAP_DEFINE(RT_SECFIELD_MARKET_CAP);

	SECFIELD_MAP_DEFINE(RT_SECFIELD_DYNAMIC_PE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TURNOVER_RATE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_IOPV);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_TURNOVER);

	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_EST_PRICE);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_JP_EST_PRICE_TYPE); // see ORGSFieldValues.h ORGS_ESTPRICE_TYPE_OPEN and ORGS_ESTPRICE_TYPE_CLOSE

	SECFIELD_MAP_DEFINE(RT_SECFIELD_PRICE_LOWLIMIT);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_PRICE_HIGHLIMIT);

	SECFIELD_MAP_DEFINE(RT_SECFIELD_CAL_SIMULATED);	// This is the begin of sec fields simulated by CAL/WowRT. Server don't handle them.
	SECFIELD_MAP_DEFINE(RT_SECFIELD_PUT_VOLUME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CALL_VOLUME);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_PUT_CALL_VOLUME_RATIO);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_PUT_OPEN_INTEREST);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_CALL_OPEN_INTEREST);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_IMPLIED_VOLATILITY);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LAST_CCC_NOTIFY);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_LAST_AUTO_NOTIFY);
	SECFIELD_MAP_DEFINE(RT_SECFIELD_MAX_VALUE);
	//---
}