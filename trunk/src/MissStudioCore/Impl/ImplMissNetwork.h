#ifndef IMPLMISSNETWORK_H__
#define IMPLMISSNETWORK_H__

#include "MissAPI\interface\IMissNetwork.h"


class ImplMissNetwork : public IMissNetwork
{
public:
	ImplMissNetwork();
	~ImplMissNetwork();

	virtual std::tr1::shared_ptr<IMissUDP> GetUDP();

};


class ImplMissUDP : public IMissUDP
{
public:
	ImplMissUDP();
	~ImplMissUDP();

	virtual bool Listen( const MissIPAddress& addr, MissNetMessageBase* pMessage );

	virtual bool UnListen( MissNetMessageBase* pMessage );

	virtual bool SendTo( const MissIPAddress& addr, const wxMemoryOutputStream& data );

};

#endif // IMPLMISSNETWORK_H__
