#include "MissNetworkManager.h"
#include "..\Common\MissFuncFinder.hpp"
#include "..\Common\CustomId.h"
#include "..\Common\IdCreater.hpp"
#include "MissAPI/interface/IMissNetwork.h"
#include "MissAPI/plugin/MissNetMessageBase.h"

#include <wx/frame.h>
#include <wx/socket.h>
#include <wx/mstream.h>

#include <iostream>
#include <winsock2.h>

extern wxFrame* wxAppFrame;


class SocketData
{
public:
	unsigned int					   uSocketID;
	std::tr1::shared_ptr<wxSocketBase> pSocket;
};

typedef std::map<unsigned int, std::vector<MissNetMessageBase*> > MsgMap;

class MissNetworkManager::Impl
{
public:
	Impl():idSocket(DTD::CI_SOCKET_ID_BEGIN){}
	MissFuncFinder<MissNetMessageBase>  funcFinder;
	IdCreater<unsigned int>             idSocket;

	///Socket_ID
	MsgMap mapMess;
	
	///port
	std::map<unsigned short, SocketData>     mapUDP;

	unsigned char buffer[32767];
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
		wxDatagramSocket* pSocket = new wxDatagramSocket(ListenAddress, wxSOCKET_BROADCAST);
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

bool MissNetworkManager::SendUDP( MissPluginBase* pPluginBase, const MissIPAddress& addrSrc,
								 const MissIPAddress& addrDes, const wxMemoryOutputStream& data )
{
	std::map<unsigned short, SocketData>::const_iterator ciFind = 
		m_pImpl->mapUDP.find(addrSrc.sPort);
	if (ciFind != m_pImpl->mapUDP.end())
	{
		wxIPV4address SendAddress;
		if (addrDes.strAddr.IsEmpty())
		{
			//SendAddress.BroadcastAddress();
			//SendAddress.Hostname("192.168.0.20");
		}
		else
		{
			SendAddress.Hostname(addrDes.strAddr);
		}
		SendAddress.Service(addrDes.sPort);
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
	std::cout<<event.GetId()<<std::endl;
	wxUint32 bufferSize(32767);
	wxSocketBase* pSocket = event.GetSocket();
	do 
	{
		pSocket->Read(m_pImpl->buffer, bufferSize);
		bufferSize = pSocket->LastCount();
		m_pImpl->buffer[bufferSize] = '\0';
		MsgMap::const_iterator ciFind = m_pImpl->mapMess.find(event.GetId());
		if (ciFind != m_pImpl->mapMess.end())
		{
			wxIPV4address ipaddr;
			pSocket->GetLocal(ipaddr);
			MissIPAddress addr;
			addr.strAddr = ipaddr.IPAddress();
			addr.sPort   = ipaddr.Service();
			wxMemoryOutputStream steam(m_pImpl->buffer, bufferSize);
			for (std::vector<MissNetMessageBase*>::const_iterator citor = ciFind->second.begin();
				citor != ciFind->second.end(); ++citor)
			{
				(*citor)->Receive(addr, steam);
			}
		}
		if (bufferSize == 2048)
		{
			std::cout<<"bufferSize == 2048"<<std::endl;
		}
	} while (bufferSize == 2048);

}

