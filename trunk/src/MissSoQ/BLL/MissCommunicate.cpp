#include "MissCommunicate.h"
#include "../Impl/MissUdpCon.h"
#include "../Common/MissGlobal.h"
#include "MissAPI/interface/IMissNetwork.h"
#include "MissProtocolsManager.h"
#include <wx/mstream.h>

using std::tr1::shared_ptr;

class MissCommunicate::Impl
{
public:
	wxEvtHandler                    hHandler;
	shared_ptr<MissUdpCon>          pUdpCon;	
	MissProtocolsManager            pm;
};

MissCommunicate::MissCommunicate()
: m_pImpl(new Impl)
{

}

MissCommunicate::~MissCommunicate()
{

}

void MissCommunicate::Init()
{
	m_pImpl->pUdpCon = shared_ptr<MissUdpCon>(new MissUdpCon());
	///创建监听
	if (shared_ptr<IMissNetwork> ptNetwork = MissGlobal::IMain->QueryIF<IMissNetwork>(IF_NETWORK))
	{
		std::tr1::shared_ptr<IMissUDP> ptUDP = ptNetwork->GetUDP();
		///加载通讯功能
		m_pImpl->pUdpCon->InitNet(ptUDP);
	}
}

wxEvtHandler* MissCommunicate::GetHandle() const
{
	return &m_pImpl->hHandler;

}

void MissCommunicate::Online()
{
	MissIPAddress addrSrc;
	addrSrc.sPort = 2425;
	wxMemoryOutputStream sMsg;
	m_pImpl->pm.GetOnline(sMsg);
	m_pImpl->pUdpCon->SendMsg(addrSrc, sMsg);
}

void MissCommunicate::Offline()
{
	MissIPAddress addrSrc;
	addrSrc.sPort = 2425;
	wxMemoryOutputStream sMsg;
	m_pImpl->pm.GetOffline(sMsg);
	m_pImpl->pUdpCon->SendMsg(addrSrc, sMsg);
}

