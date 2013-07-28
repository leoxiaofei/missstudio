#ifndef MISSPROTOCOLSMANAGER_H__
#define MISSPROTOCOLSMANAGER_H__

#include <memory>
class wxString;
class wxMemoryOutputStream;
class HostInfo;

class MissProtocolsManager
{
	class Impl;
public:
	MissProtocolsManager();
	~MissProtocolsManager();

	void GetNoOperation(wxMemoryOutputStream& sMsg);
	void GetOnline(wxMemoryOutputStream& sMsg);
	void GetOffline(wxMemoryOutputStream& sMsg);
	void GetSendMsg(wxMemoryOutputStream& sMsg, const wxString& strMsg);

	bool Analyse(unsigned long uSerial, unsigned int uCommand, 
				 const wxString& strContext, const wxMemoryOutputStream& sMsg);

	void GetLastUser(HostInfo& info);

	unsigned long HostStatus();

protected:
	void InitData();

	unsigned long PackMsg(wxMemoryOutputStream& sMsg, unsigned int uCommand, const wxString& strContext);
	unsigned long UnPackMsg(unsigned int uCommand, const wxString& strContext, const wxMemoryOutputStream& sMsg);
	
	unsigned long MakePacketNo();


private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSPROTOCOLSMANAGER_H__
