#include "ImplMissNetwork.h"
#include "..\BLL\MissNetworkManager.h"


ImplMissNetwork::ImplMissNetwork(MissPluginBase* pPluginBase)
: m_pPluginBase(pPluginBase)
{

}

ImplMissNetwork::~ImplMissNetwork()
{

}

std::tr1::shared_ptr<IMissUDP> ImplMissNetwork::GetUDP()
{
	return std::tr1::shared_ptr<IMissUDP>(new ImplMissUDP(m_pPluginBase));
}

ImplMissUDP::ImplMissUDP(MissPluginBase* pPluginBase)
: m_pPluginBase(pPluginBase)
{

}

ImplMissUDP::~ImplMissUDP()
{

}

bool ImplMissUDP::Listen( const MissIPAddress& addr, MissNetMessageBase* pMessage )
{
	return MissNetworkManager::Instance().ListenUDP(m_pPluginBase, addr, pMessage);
}

bool ImplMissUDP::UnListen( MissNetMessageBase* pMessage )
{
	return MissNetworkManager::Instance().UnListenUDP(pMessage);
}

bool ImplMissUDP::SendTo( const MissIPAddress& addrSrc, const MissIPAddress& addrDes, 
						  const wxMemoryOutputStream& data )
{
	return MissNetworkManager::Instance().SendUDP(m_pPluginBase, addrSrc, addrDes, data);
}

