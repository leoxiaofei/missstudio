#include "MissCommunicate.h"
#include "MissAPI\interface\IMissNetwork.h"

#include <wx/mstream.h>

class MissCommunicate::Impl
{
public:
	std::tr1::shared_ptr<IMissUDP> ptUDP;
};

MissCommunicate::MissCommunicate()
: m_pImpl(new Impl)
{

}

MissCommunicate::~MissCommunicate()
{

}


void MissCommunicate::Receive( const MissIPAddress& addr, const wxMemoryOutputStream& data )
{
	
}

void MissCommunicate::InitNet( const std::tr1::shared_ptr<IMissUDP>& ptUDP )
{
	m_pImpl->ptUDP = ptUDP;
	
	MissIPAddress addr;
	addr.sPort = 2425;
	ptUDP->Listen(addr, this);

	SendMsg(wxT("1:100:flyingzl:flyingzl:32:纵我不往，子宁不嗣音？"));
}

void MissCommunicate::SendMsg( const wxString& strMsg )
{
	MissIPAddress addr;
	addr.strAddr = wxT("192.168.50.49");
	addr.sPort = 2425;
	wxMemoryOutputStream data;
	data.Write(strMsg.c_str(), wcslen(strMsg.c_str())*2);
	m_pImpl->ptUDP->SendTo(addr, data);
}
