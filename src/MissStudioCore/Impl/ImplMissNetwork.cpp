#include "ImplMissNetwork.h"


ImplMissNetwork::ImplMissNetwork()
{

}

ImplMissNetwork::~ImplMissNetwork()
{

}

std::tr1::shared_ptr<IMissUDP> ImplMissNetwork::GetUDP()
{
	return std::tr1::shared_ptr<IMissUDP>(new ImplMissUDP);
}

ImplMissUDP::ImplMissUDP()
{

}

ImplMissUDP::~ImplMissUDP()
{

}

bool ImplMissUDP::Listen( const MissIPAddress& addr, MissNetMessageBase* pMessage )
{

	return false;
}

bool ImplMissUDP::UnListen( MissNetMessageBase* pMessage )
{

	return false;
}

bool ImplMissUDP::SendTo( const MissIPAddress& addr, const wxMemoryOutputStream& data )
{

	return false;
}

