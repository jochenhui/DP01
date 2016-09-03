#include "stdafx.h"
#pragma warning(disable: 4503) // boost variant
#include <algorithm>    // for max()
#include "DirectorSignatures.h"
#include "ApiHandle.h"

using namespace std;
using namespace std::tr1;
using namespace DirectorSignatures;

///////////////// 1. Exported functions
extern "C" {

__declspec(dllexport) long AttributeNumericGet(unsigned long type, int index, int field, long defaultValue) {
	api->AttributeNumericGet(type, index, field, defaultValue);
   return 0;
}

__declspec(dllexport) bool AttributeStringGet(unsigned long type, int index, int field, std::wstring& sAttributeValue) {
    RLog("AttributeStringGet");
    return true;
}

__declspec(dllexport) unsigned long BarsGet(PCWSTR pSymbol, int AssetType, PTICKDATA pTickData, CallbackBarsGet pCB, DWORD UserData) {
    RLog("BarsGet");
    return 0;
}

__declspec(dllexport) unsigned long CCAGet(PCWSTR pSymbol, unsigned long dwCorpActionNo, unsigned long dwCorrectionNo, CallbackCCAGet pCB, unsigned long dwUserData) {
    RLog("CCAGet");
    return 0;
}

__declspec(dllexport) void Deinitialize(BOOL bBackup) {
    RLog("Deinitialize");
}

__declspec(dllexport) DWORD DailyBarsGet(PCWSTR pSymbol, int AssetType, EODDATA* pData, CallbackDailyBarsGet pCB, DWORD UserData, BOOL bPeriodic) {
    RLog("DailyBarsGet");
    return 0;
}

__declspec(dllexport) int EventRelease(unsigned long event, bool bConnected) {
    RLog("EventRelease");
    return 0;
}

__declspec(dllexport) int ExchangeIndexGet (PCWSTR exchangeName) {
    RLog("AttributeExchangeIndexGetNumericGet");
    return 0;
}

__declspec(dllexport) void ExchangesGet(std::map<unsigned short, std::wstring>& ex_map) {
	return api->ExchangesGet(ex_map);
}

__declspec(dllexport) bool Initialize(PCWSTR szLogDirectory, unsigned long ulDataProviderID, DirectorSignatures::CallbackProcessMessage pCB) {
	return api->Initialize(szLogDirectory, ulDataProviderID, pCB);
}

__declspec(dllexport) int ProcessMessage(DirectorMessages::MSG& msg) {
	try //--增加异常捕获
	{
		return api->ProcessMesssage(msg);
	}
	catch (exception e)
	{
		RLog("Exception ");
		return 0;
	}
}

__declspec(dllexport) int ProcessSyncMessage(DirectorMessages::MSG& msg) {
	return api->ProcessSyncMessage(msg);
}


__declspec(dllexport) unsigned long QuoteGet(PCWSTR pSymbol,int AssetType,PBYTE pFields, LCID locale_id, CallbackQuoteGet pCB, unsigned long UserData, bool bPeriodic) {
    RLog("QuoteGet");
	api->QuoteGet(pSymbol, AssetType, pFields, locale_id, pCB, UserData, bPeriodic);
    return 0;
}

__declspec(dllexport) int QuoteModify(unsigned long event, unsigned char* pFields, LCID locale_id) {
    RLog("QuoteModify");
    return 0;
}

__declspec(dllexport) unsigned long SecurityListGet(PCWSTR pSymbol, int AssetType, PBYTE pFields, RTSec_OptionFilter* pOptionFilter, DirectorSignatures::CallbackSecurityListGet pCB, DWORD UserData, unsigned char currency, short ExchID, LCID locale_id, int flags) {
    RLog("SecurityListGet");
    return 0;
}

__declspec(dllexport) unsigned long SessionGet(PCWSTR pSymbol, int AssetType, CallbackSessionGet pCB, unsigned long UserData) {
    RLog("SessionGet");
    return 0;
}

__declspec(dllexport) void TestDialog(void) {
	RLog("TestDialog");
	api->testDlg();
	return ;
}

}

