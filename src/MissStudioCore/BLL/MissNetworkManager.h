#ifndef MISSNETWORKMANAGER_H__
#define MISSNETWORKMANAGER_H__

#include <memory>

class MissPluginBase;
class MissNetMessageBase;
struct MissIPAddress;

class wxMemoryOutputStream;
class wxSocketEvent;

class MissNetworkManager
{
	class Impl;
public:
	static MissNetworkManager& Instance()
	{
		static MissNetworkManager theSingleton;
		return theSingleton;
	}

	MissPluginBase* GetPluginBase(MissNetMessageBase* pMessage) const;
	bool UnloadPlugin(MissPluginBase* pPluginBase);

	bool ListenUDP(MissPluginBase* pPluginBase, 
		const MissIPAddress& addr, MissNetMessageBase* pMessage);
	bool UnListenUDP(MissNetMessageBase* pMessage);

	bool SendUDP(MissPluginBase* pPluginBase, const MissIPAddress& addrSrc,
		const MissIPAddress& addrDes, const wxMemoryOutputStream& data);

	void Receive(wxSocketEvent& event);

protected:


private:
	MissNetworkManager();
	~MissNetworkManager();
	MissNetworkManager(const MissNetworkManager&);
	MissNetworkManager& operator=(const MissNetworkManager&);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // MISSNETWORKMANAGER_H__
