#ifndef MISSPROTOCOLSMANAGER_H__
#define MISSPROTOCOLSMANAGER_H__

#include <memory>
class wxString;
class wxMemoryOutputStream;

class MissProtocolsManager
{
	class Impl;
public:
	MissProtocolsManager();
	~MissProtocolsManager();

	void GetOnline(wxMemoryOutputStream& sMsg);
	void GetOffline(wxMemoryOutputStream& sMsg);


	unsigned long HostStatus();
protected:
	void InitData();

	unsigned long PackMsg(wxMemoryOutputStream& sMsg, unsigned int uCommand, const wxString& strContext);
	
	unsigned long MakePacketNo();


private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSPROTOCOLSMANAGER_H__
