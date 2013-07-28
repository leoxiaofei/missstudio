#ifndef EVENTCALLBACK_H__
#define EVENTCALLBACK_H__

#include "msgcallbackbase.h"

#include <memory>
#include <wx\event.h>

class wxString;
class wxEvtHandler;

class EventCallBack : public MsgCallBackBase
{
	class Impl;
public:
	EventCallBack(wxEvtHandler& hHandler);
	~EventCallBack();

	virtual void ReceiveData( void* szData, unsigned int uPacketBytes,
		const std::string& addr, unsigned short portNo);


private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

class wxMemoryOutputStream;

class MissMessageEvent : public wxEvent
{
	class Impl;
public:
	MissMessageEvent(void* szData, unsigned int uPacketBytes,
		const wxString& addr, unsigned short portNo);
	MissMessageEvent(const MissMessageEvent& other);
	~MissMessageEvent();

	virtual wxEvent * Clone() const;

	wxMemoryOutputStream& GetStream();;
	wxString&	          GetAddr();
	unsigned short        GetPortNo();
private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

wxDECLARE_EVENT(wxEVT_COMMUN_MESSAGE, MissMessageEvent);

#endif // EVENTCALLBACK_H__
