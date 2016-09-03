#pragma once

namespace DP_MESSAGE
{

class CBaseMessage
{
public:
	enum MsgTypes {
		Bars, 
		CCA, 
		Connect, 
		ConnectionStatus, 
		DailyBars, 
		quote, 
		session, 
		SecurityList, 
		TickBars, 
		Generic, 
		GlobalNews 
	};

	CBaseMessage(MsgTypes type, std::wstring& symbol, int asset_type, unsigned long msg_event, unsigned long msg_arg) :
		m_msgType(type), symbol(symbol), asset_type(asset_type), event(msg_event), callback_argument(msg_arg) {}

	CBaseMessage(MsgTypes type, std::wstring& symbol, int asset_type, unsigned long msg_event, unsigned long msg_arg, std::string & fields) :
		m_msgType(type), symbol(symbol), asset_type(asset_type), event(msg_event), callback_argument(msg_arg), fields(fields) {}

	CBaseMessage(MsgTypes type) : m_msgType(type) {}

	~CBaseMessage(){}

	/*----------------------------------------------------------------*/
	/* 用于无锁队列 */
	CBaseMessage	*m_pNext;

	MsgTypes		 m_msgType;
	//--add chenhui
	unsigned long event;
	unsigned long callback_argument;
	int asset_type;
	std::wstring symbol;
	std::string fields;
	//--add end

/*	DirectorMessages::MSG msg;*/

	/*----------------------------------------------------------------*/
// 	DirectorStatus::State	m_ConnectionStatus;
// 	__time32_t				m_StatusTime;


//	virtual	CBaseMessage * New(MsgTypes& msgType) { CBaseMessage *p; p = new CBaseMessage(msgType); p->SetFreeMessage(); return p; };
/*	virtual void SetFreeMessage(CBaseMessage *pPackage)=0;*/
	virtual void SetFreeMessage(){ m_pNext = nullptr; }

// 	void SetGenericMessage(DirectorMessages::MSG &m);
// 	void SetConnectionStatus(DirectorMessages::MSG &m, DirectorStatus::State stat);
};

/* ---- Generic Message ---- */
class CGenericMsg : public CBaseMessage 
{
public:
	CGenericMsg(DirectorMessages::MSG& m) : msg(m), CBaseMessage(Generic) { SetFreeMessage(); }
	
	virtual void SetFreeMessage();
	void SetGenericMessage(DirectorMessages::MSG &m);

    DirectorMessages::MSG msg;
};

/* ---- ConnectionStatus Message ---- */
class CConnectionStatusMsg : public CBaseMessage
{
public:
	//构造函数：当前状态、消息类型、当前状态的时间
	CConnectionStatusMsg(DirectorStatus::State s) : CBaseMessage(ConnectionStatus), m_ConnectionStatus(s) { _time32(&m_StatusTime); SetFreeMessage(); }
	
	virtual void SetFreeMessage();
	void SetConnectionStatus(DirectorStatus::State stat);

	DirectorStatus::State m_ConnectionStatus;//连接状态值
	__time32_t m_StatusTime;//时间
};

/* ---- Quote Message ---- */
class CQuoteMsg : public CBaseMessage {
public:
	CQuoteMsg(std::wstring& symbol, int asset_type, unsigned char* pFields, LCID locale_id, unsigned long msg_event, bool periodic, unsigned long msg_arg, DirectorSignatures::CallbackQuoteGet& cb) :
	CBaseMessage(quote, symbol, asset_type, msg_event, msg_arg, std::string((char const *)pFields)), callback(cb), periodic(periodic), locale_id_(locale_id) {}
	
	virtual void SetFreeMessage();
	void SetQuoteMsg(MsgTypes i_type, std::wstring& i_symbol, int i_asset_type, unsigned long i_msg_event, unsigned long i_msg_arg, std::string & i_field, DirectorSignatures::CallbackQuoteGet& i_cb, bool i_periodic, LCID i_locale_id);
	
	bool periodic;
	LCID locale_id_;
	DirectorSignatures::CallbackQuoteGet callback;
};

}

