#include "eventcallback.h"
#include <wx\mstream.h>
#include <wx\string.h>

wxDEFINE_EVENT(wxEVT_COMMUN_MESSAGE, MissMessageEvent);


class EventCallBack::Impl
{
public:
	Impl(wxEvtHandler& hnd)
	: hHandler(hnd)
	{}
	wxEvtHandler& hHandler;
};

EventCallBack::EventCallBack(wxEvtHandler& hHandler)
: m_pImpl(new Impl(hHandler))
{

}

EventCallBack::~EventCallBack()
{

}

void EventCallBack::ReceiveData( void* szData, unsigned int uPacketBytes, 
								const std::string& addr, unsigned short portNo )
{
	MissMessageEvent* pEvent = new MissMessageEvent(szData, uPacketBytes, addr, portNo);
	m_pImpl->hHandler.QueueEvent(pEvent);
}


class MissMessageEvent::Impl
{
public:
	wxMemoryOutputStream stream;
	wxString       strAddr;
	unsigned short uPortNo;
};

MissMessageEvent::MissMessageEvent(void* szData, unsigned int uPacketBytes,
								const wxString& addr, unsigned short uPortNo)
: wxEvent(0, wxEVT_COMMUN_MESSAGE)
, m_pImpl(new Impl)
{
	m_pImpl->stream.GetOutputStreamBuffer()->Write(szData, uPacketBytes);
	m_pImpl->strAddr = addr;
	m_pImpl->uPortNo = uPortNo;
}

MissMessageEvent::MissMessageEvent( const MissMessageEvent& other )
: wxEvent(0, wxEVT_COMMUN_MESSAGE)
, m_pImpl(new Impl)
{
	wxStreamBuffer *pBuffer = other.m_pImpl->stream.GetOutputStreamBuffer();
	m_pImpl->stream.GetOutputStreamBuffer()->Write(
		pBuffer->GetBufferStart(),
		pBuffer->GetBufferSize());

	m_pImpl->strAddr = other.m_pImpl->strAddr;
	m_pImpl->uPortNo  = other.m_pImpl->uPortNo;
}

MissMessageEvent::~MissMessageEvent()
{

}

wxEvent* MissMessageEvent::Clone() const
{
	MissMessageEvent* pRet = new MissMessageEvent(*this);
	return pRet;
}

wxString& MissMessageEvent::GetAddr()
{
	return m_pImpl->strAddr;
}

unsigned short MissMessageEvent::GetPortNo()
{
	return m_pImpl->uPortNo;
}

wxMemoryOutputStream& MissMessageEvent::GetStream()
{
	return m_pImpl->stream;
}
