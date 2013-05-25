#include "MissNetworkManager.h"
#include "..\Common\MissFuncFinder.hpp"
#include "..\Common\CustomId.h"
#include "..\Common\IdCreater.hpp"
#include "MissAPI/interface/IMissNetwork.h"

#include <wx/frame.h>
#include <wx/socket.h>
#include <wx/mstream.h>

#include <iostream>

extern wxFrame* wxAppFrame;


class SocketData
{
public:
	unsigned int					   uSocketID;
	std::tr1::shared_ptr<wxSocketBase> pSocket;
};

class MissNetworkManager::Impl
{
public:
	Impl():idSocket(DTD::CI_SOCKET_ID_BEGIN){}
	MissFuncFinder<MissNetMessageBase>  funcFinder;
	IdCreater<unsigned int>             idSocket;

	///Socket_ID
	std::map<unsigned int, std::vector<MissNetMessageBase*> > mapMess;
	
	///port
	std::map<unsigned short, SocketData>     mapUDP;

	unsigned char buffer[2048];
};

MissNetworkManager::MissNetworkManager()
: m_pImpl(new Impl)
{

}

MissNetworkManager::~MissNetworkManager()
{

}

MissPluginBase* MissNetworkManager::GetPluginBase( MissNetMessageBase* pMessage ) const
{
	return m_pImpl->funcFinder.QueryPluginByFunc(pMessage);
}

bool MissNetworkManager::UnloadPlugin( MissPluginBase* pPluginBase )
{
// 	std::vector<MissHotKeyFuncBase*> vecFunc;
// 	m_pImpl->funcFinder.QueryFuncByPlugin(pPluginBase, vecFunc);
// 	for (std::vector<MissHotKeyFuncBase*>::size_type ix = 0; ix != vecFunc.size(); ++ix)
// 	{
// 		UnRegHotKeys(vecFunc[ix]);
// 	}
 	return false;
}

bool MissNetworkManager::ListenUDP( MissPluginBase* pPluginBase, 
	const MissIPAddress& addr, MissNetMessageBase* pMessage )
{
	bool bRet(true);
	m_pImpl->funcFinder.RegPluginFunc(pPluginBase, pMessage);
	unsigned int uSocketID(0);
	std::map<unsigned short, SocketData>::const_iterator ciFind 
		= m_pImpl->mapUDP.find(addr.sPort);
	if (ciFind == m_pImpl->mapUDP.end())
	{
		uSocketID = m_pImpl->idSocket();
		SocketData& data = m_pImpl->mapUDP[addr.sPort];
		wxIPV4address ListenAddress;
		if (addr.strAddr.IsEmpty())
		{
			ListenAddress.AnyAddress();
		}
		else
		{
			ListenAddress.Hostname(addr.strAddr);
		}
		ListenAddress.Service(addr.sPort);
		wxDatagramSocket* pSocket = new wxDatagramSocket(ListenAddress);
		pSocket->SetEventHandler(*wxAppFrame, uSocketID);
		pSocket->SetNotify(wxSOCKET_INPUT_FLAG);
		pSocket->Notify(true);
		data.pSocket = std::tr1::shared_ptr<wxSocketBase>(pSocket);
		data.uSocketID = uSocketID;

	}
	else
	{
		uSocketID = ciFind->second.uSocketID;
	}
	
	m_pImpl->mapMess[uSocketID].push_back(pMessage);
	return true;
}

bool MissNetworkManager::UnListenUDP( MissNetMessageBase* pMessage )
{
	return false;
}

bool MissNetworkManager::SendUDP( MissPluginBase* pPluginBase, 
	 const MissIPAddress& addr, const wxMemoryOutputStream& data )
{
	std::map<unsigned short, SocketData>::const_iterator ciFind = 
		m_pImpl->mapUDP.find(addr.sPort);
	if (ciFind != m_pImpl->mapUDP.end())
	{
		wxIPV4address SendAddress;
		SendAddress.Hostname(addr.strAddr);
		SendAddress.Service(addr.sPort);
		std::tr1::static_pointer_cast<wxDatagramSocket>(ciFind->second.pSocket)->
			SendTo(SendAddress,
			data.GetOutputStreamBuffer()->GetBufferStart(),
			data.GetOutputStreamBuffer()->GetBufferSize());
	}
	return true;
}

void MissNetworkManager::Receive( wxSocketEvent& event )
{
	//std::cout<<event.GetSocketEvent()<<std::endl;
	std::cout<<event.GetEventType()<<std::endl;
	
	wxUint32 bufferSize(2048);
	wxSocketBase* pSocket = event.GetSocket();
	do 
	{
		pSocket->Read(m_pImpl->buffer, bufferSize);
		bufferSize = pSocket->LastCount();
		m_pImpl->buffer[bufferSize] = '\0';
		std::cout<<m_pImpl->buffer<<std::endl;
		//m_pImpl->mapMess.find();
	} while (bufferSize == 2048);
}

