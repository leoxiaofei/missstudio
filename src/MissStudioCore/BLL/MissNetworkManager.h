#ifndef MISSNETWORKMANAGER_H__
#define MISSNETWORKMANAGER_H__

#include <memory>

class MissNetworkManager
{
	class Impl;
public:
	static MissNetworkManager& Instance()
	{
		static MissNetworkManager theSingleton;
		return theSingleton;
	}

	

private:
	MissNetworkManager();
	~MissNetworkManager();
	MissNetworkManager(const MissNetworkManager&);
	MissNetworkManager& operator=(const MissNetworkManager&);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // MISSNETWORKMANAGER_H__
