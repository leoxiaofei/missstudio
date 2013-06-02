#include "MissUdpCon.h"
#include "MissAPI\interface\IMissNetwork.h"

#include <wx/mstream.h>
#include <wx/txtstrm.h>
#include <wx/sstream.h>
#include <iostream>
class MissUdpCon::Impl
{
public:
	std::tr1::shared_ptr<IMissUDP>  ptUDP;
	wxEvtHandler                    hHandler;
	MissIPAddress					addrListen;
};

MissUdpCon::MissUdpCon()
: m_pImpl(new Impl)
{

}

MissUdpCon::~MissUdpCon()
{

}


void MissUdpCon::Receive( const MissIPAddress& addr, const wxMemoryOutputStream& data )
{
	std::cout<<(char*)data.GetOutputStreamBuffer()->GetBufferStart()<<std::endl;

}

void MissUdpCon::InitNet( const std::tr1::shared_ptr<IMissUDP>& ptUDP, unsigned short sPort )
{
	m_pImpl->ptUDP = ptUDP;
	
	m_pImpl->addrListen.sPort = sPort;
	ptUDP->Listen(m_pImpl->addrListen, this);

}

wxEvtHandler* MissUdpCon::GetHandle() const
{
	return &m_pImpl->hHandler;
}

void MissUdpCon::SendMsg( const MissIPAddress& addr, const wxMemoryOutputStream& sMsg )
{
	m_pImpl->ptUDP->SendTo(m_pImpl->addrListen, addr, sMsg);
}
