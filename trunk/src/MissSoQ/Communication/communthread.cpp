#include "communthread.h"

#include "detector.h"

#include <boost\thread.hpp>
#include <boost\bind.hpp>
#include <boost\asio\io_service.hpp>
#include "eventcallback.h"
#include <wx/mstream.h>

wxDEFINE_EVENT(wxEVT_COMMUN_NOTIFY, wxEvent);

using namespace boost::asio;

class CommunThread::Impl
{
public:
	Impl(wxEvtHandler& hnd)
	: hHandler(hnd)
	{}
	wxEvtHandler& hHandler;
	std::tr1::shared_ptr<boost::thread> pThread;
	Detector*     pDetector;
	io_service*   pIos;
};

CommunThread::CommunThread(wxEvtHandler& hHandler)
: m_pImpl(new Impl(hHandler))
{

}

CommunThread::~CommunThread()
{

}

void CommunThread::Start()
{
	m_pImpl->pThread = std::tr1::shared_ptr<boost::thread>(
		new boost::thread( boost::bind(&CommunThread::Run, this) ) );
}

void CommunThread::Run()
{
	try
	{
		io_service ios;
		m_pImpl->pIos = &ios;

		Detector detector(ios);
		m_pImpl->pDetector = &detector;
		std::tr1::shared_ptr<EventCallBack> ptCallBack(new EventCallBack(m_pImpl->hHandler));
		detector.SetCallBack(ptCallBack);

		wxCommandEvent *pEvent = new wxCommandEvent(wxEVT_COMMUN_NOTIFY);
		m_pImpl->hHandler.QueueEvent(pEvent);
		ios.run();
		std::cout<<"Server End"<<std::endl;
		m_pImpl->pIos      = NULL;
		m_pImpl->pDetector = NULL;
	}
	catch (std::exception& e)
	{
		std::cout<<"CommunThread Error: "<< e.what() <<std::endl;
		m_pImpl->pIos      = NULL;
		m_pImpl->pDetector = NULL;
	}
	catch(...)
	{
		std::cout<<"CommunThread Error: Unknow"<<std::endl;
		m_pImpl->pIos      = NULL;
		m_pImpl->pDetector = NULL;
	}
}

void CommunThread::Broadcast( const wxMemoryOutputStream& sData, unsigned short uPort /*= 2425*/)
{
	m_pImpl->pDetector->Broadcast(
		sData.GetOutputStreamBuffer()->GetBufferStart(),
		sData.GetOutputStreamBuffer()->GetBufferSize(), uPort);
}

void CommunThread::Exit()
{
	if (m_pImpl->pIos)
	{
		m_pImpl->pIos->stop();
	}
	m_pImpl->pThread->join();
}

void CommunThread::SendTo( const wxMemoryOutputStream& sData,
						  const wxString& strAddr, unsigned short uPort /*= 2425*/ )
{
	m_pImpl->pDetector->SendTo(
		sData.GetOutputStreamBuffer()->GetBufferStart(),
		sData.GetOutputStreamBuffer()->GetBufferSize(),
		strAddr.ToStdString(), uPort);
}
