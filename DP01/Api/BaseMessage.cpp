#include "StdAfx.h"
#include "BaseMessage.h"

using namespace DP_MESSAGE;


// void CBaseMessage::SetFreeMessage(CBaseMessage *pPackage)
// {
// 	pPackage->m_pNext = NULL;
// 	pPackage->msg.clear_attributes();
// 	pPackage->msg.add_attribute(DirectorTags::Version, pPackage->msg.Version);
// }
// 
// void CBaseMessage::SetFreeMessage()
// {
// 	SetFreeMessage(this);
// }

/* ---- Generic Msg ---- */
void CGenericMsg::SetFreeMessage()//初始构造时
{
	CBaseMessage::SetFreeMessage();
}

void CGenericMsg::SetGenericMessage(DirectorMessages::MSG &m)//回收利用时重新赋值
{
	m_msgType = Generic;
	msg = m;
	CBaseMessage::SetFreeMessage();
}


/* ---- ConnectionStation Msg ---- */
void CConnectionStatusMsg::SetFreeMessage()
{
	CBaseMessage::SetFreeMessage();
}


void CConnectionStatusMsg::SetConnectionStatus(DirectorStatus::State stat)
{
	m_msgType = ConnectionStatus;
	m_ConnectionStatus = stat;
	_time32(&m_StatusTime);
	CBaseMessage::SetFreeMessage();
}

/* ---- CQuote Msg ---- */
void CQuoteMsg::SetFreeMessage()
{
	CBaseMessage::SetFreeMessage();
}
void CQuoteMsg::SetQuoteMsg(MsgTypes i_type, std::wstring& i_symbol, int i_asset_type, unsigned long i_msg_event, unsigned long i_msg_arg, std::string & i_field, DirectorSignatures::CallbackQuoteGet& i_cb, bool i_periodic, LCID i_locale_id)
{
	m_msgType = i_type;
	symbol = i_symbol;
	asset_type = i_asset_type;
	event = i_msg_event;
	callback_argument = i_msg_arg;
	fields = i_field;

	callback = i_cb;
	periodic = i_periodic;
	locale_id_ = i_locale_id;
	
}