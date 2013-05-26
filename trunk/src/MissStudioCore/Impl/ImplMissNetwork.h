#ifndef IMPLMISSNETWORK_H__
#define IMPLMISSNETWORK_H__

#include "MissAPI\interface\IMissNetwork.h"

class MissPluginBase;

class ImplMissNetwork : public IMissNetwork
{
public:
	ImplMissNetwork(MissPluginBase* pPluginBase);
	~ImplMissNetwork();

	virtual std::tr1::shared_ptr<IMissUDP> GetUDP();

private:
	MissPluginBase* m_pPluginBase;
};


class ImplMissUDP : public IMissUDP
{
public:
	ImplMissUDP(MissPluginBase* pPluginBase);
	~ImplMissUDP();

	virtual bool Listen( const MissIPAddress& addr, MissNetMessageBase* pMessage );

	virtual bool UnListen( MissNetMessageBase* pMessage );

	virtual bool SendTo( const MissIPAddress& addrSrc, const MissIPAddress& addrDes, 
						 const wxMemoryOutputStream& data );

private:
	MissPluginBase* m_pPluginBase;
};

#endif // IMPLMISSNETWORK_H__
