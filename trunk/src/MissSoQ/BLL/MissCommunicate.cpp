#include "MissCommunicate.h"
#include "../Common/MissGlobal.h"
#include "MissProtocolsManager.h"
#include <wx/mstream.h>
#include "../Communication/communthread.h"
#include "../Communication/eventcallback.h"

using std::tr1::shared_ptr;

class MissCommunicate::Impl
{
public:
	Impl()
	: ct(hHandler)
	{}
	wxEvtHandler                    hHandler;
	//shared_ptr<MissUdpCon>        pUdpCon;	
	MissProtocolsManager            pm;

	CommunThread                    ct;

	wxString                        strDesAddr;
	unsigned short                  uPort;
};

MissCommunicate::MissCommunicate()
: m_pImpl(new Impl)
{
	m_pImpl->hHandler.Bind(wxEVT_COMMUN_NOTIFY, &MissCommunicate::ConnectReady, this);
	m_pImpl->hHandler.Bind(wxEVT_COMMUN_MESSAGE, &MissCommunicate::ReceiveData, this);
	
}

MissCommunicate::~MissCommunicate()
{

}

void MissCommunicate::Init()
{
	m_pImpl->ct.Start();
// 	m_pImpl->pUdpCon = shared_ptr<MissUdpCon>(new MissUdpCon());
// 	///创建监听
// 	if (shared_ptr<IMissNetwork> ptNetwork = MissGlobal::IMain->QueryIF<IMissNetwork>(IF_NETWORK))
// 	{
// 		std::tr1::shared_ptr<IMissUDP> ptUDP = ptNetwork->GetUDP();
// 		///加载通讯功能
// 		m_pImpl->pUdpCon->InitNet(ptUDP);
// 	}
}

wxEvtHandler* MissCommunicate::GetHandle() const
{
	return &m_pImpl->hHandler;

}

void MissCommunicate::Online()
{
// 	MissIPAddress addrSrc;
// 	addrSrc.sPort = 2425;
 	wxMemoryOutputStream sMsg;
 	m_pImpl->pm.GetOnline(sMsg);
	m_pImpl->ct.Broadcast(sMsg);
	// 	m_pImpl->pUdpCon->SendMsg(addrSrc, sMsg);

}

void MissCommunicate::Offline()
{
	wxMemoryOutputStream sMsg;
	m_pImpl->pm.GetOffline(sMsg);
	m_pImpl->ct.Broadcast(sMsg);
// 	MissIPAddress addrSrc;
// 	addrSrc.sPort = 2425;
// 	wxMemoryOutputStream sMsg;
// 	m_pImpl->pm.GetOffline(sMsg);
// 	m_pImpl->pUdpCon->SendMsg(addrSrc, sMsg);
}

void MissCommunicate::ConnectReady(wxEvent& event)
{
	NoOperation();
	Online();
}

void MissCommunicate::Exit()
{
	m_pImpl->ct.Exit();
}

void MissCommunicate::NoOperation()
{
	wxMemoryOutputStream sMsg;
	m_pImpl->pm.GetNoOperation(sMsg);
	m_pImpl->ct.Broadcast(sMsg);
}

void MissCommunicate::ReceiveData( MissMessageEvent& event )
{
	m_pImpl->strDesAddr = event.GetAddr();
	m_pImpl->uPort      = event.GetPortNo();
	
}

void MissCommunicate::SendMsg()
{
	wxMemoryOutputStream sMsg;
	m_pImpl->pm.GetSendMsg(sMsg, wxT("你好"));
	m_pImpl->ct.SendTo(sMsg, m_pImpl->strDesAddr, m_pImpl->uPort);
}

