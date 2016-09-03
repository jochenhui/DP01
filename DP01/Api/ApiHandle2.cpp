#include "stdafx.h"
#include "Logger.h"
#include "ApiHandle.h"
#include "BaseMessage.h"
using namespace NS_FEIMA;
using namespace DP_MESSAGE;

void RLog(const char *s);

DWORD WINAPI ApiHandle::ThreadEntry(PVOID pParam)
{
	ApiHandle *pThis;
	pThis = (ApiHandle *)pParam;
	RLog("Thread entry.");
	pThis->Run();
	RLog("Thread exit.");
	return 0;
}

void ApiHandle::Run(void)
{
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

	sprintf_s(m_sRet, "Callback: process_msg_reqscanninginfo");
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

void ApiHandle::initialize_secfield_types()
{
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
}