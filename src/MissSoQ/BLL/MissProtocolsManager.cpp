#include "MissProtocolsManager.h"

#include "../Common/MissComDef.h"
#include "../IPMSG/ipmsg.h"

#include <wx/mstream.h>
#include <wx/utils.h> 

#include <time.h>


class MissProtocolsManager::Impl
{
public:
	Impl()
	:uPacketNo(0)
	{}

	wxString strVer;
	HostInfo hostLocal;

	unsigned long uPacketNo;

};

MissProtocolsManager::MissProtocolsManager()
: m_pImpl(new Impl)
{
	InitData();
}

MissProtocolsManager::~MissProtocolsManager()
{

}

void MissProtocolsManager::InitData()
{
	m_pImpl->strVer = "1";
	m_pImpl->hostLocal.strHostName = wxGetHostName();
	m_pImpl->hostLocal.strUserName = wxGetUserName();

}

void MissProtocolsManager::GetOnline( wxMemoryOutputStream& sMsg )
{
	PackMsg(sMsg, IPMSG_BR_ENTRY | HostStatus(), m_pImpl->hostLocal.strUserName);
}

void MissProtocolsManager::GetOffline( wxMemoryOutputStream& sMsg )
{
	PackMsg(sMsg, IPMSG_BR_EXIT | HostStatus(), m_pImpl->hostLocal.strUserName);
}

unsigned long MissProtocolsManager::MakePacketNo()
{
	//unsigned long now;
	time_t now;
	time(&now);

	if (now > m_pImpl->uPacketNo)
	{
		m_pImpl->uPacketNo = now;
	}

	return m_pImpl->uPacketNo++;
}

unsigned long MissProtocolsManager::PackMsg( wxMemoryOutputStream& sMsg,
											 unsigned int uCommand, 
											 const wxString& strContext )
{
	int		cmd			= GET_MODE(uCommand);
	bool	is_br_cmd	=	cmd == IPMSG_BR_ENTRY ||
							cmd == IPMSG_BR_EXIT  ||
							cmd == IPMSG_BR_ABSENCE ||
							cmd == IPMSG_NOOPERATION ? TRUE : FALSE;
	bool	is_utf8		= (uCommand & IPMSG_UTF8OPT) ? true : false;

	unsigned long uPacketNo = MakePacketNo();

	wxString strTemp = wxString::Format("%s:%u:%s:%s:%u:", 
		m_pImpl->strVer,
		uPacketNo, 
		m_pImpl->hostLocal.strUserName,
		m_pImpl->hostLocal.strHostName,
		uCommand
		);
	wxCharBuffer cbf = strTemp.mb_str();
	sMsg.Write(cbf.data(), cbf.length());

	cbf = is_utf8 ? strContext.utf8_str() : strContext.mb_str();
	sMsg.Write(cbf.data(), cbf.length());

	return uPacketNo;
}

unsigned long MissProtocolsManager::HostStatus()
{
	return IPMSG_CAPUTF8OPT;
// 	return	(cfg->DialUpCheck ? IPMSG_DIALUPOPT : 0)
// 		| (cfg->AbsenceCheck ? IPMSG_ABSENCEOPT : 0)
// 		| (msgMng->IsAvailableTCP() ?
// 		(IPMSG_FILEATTACHOPT | ((cfg->ClipMode & CLIP_ENABLE) ? IPMSG_CLIPBOARDOPT : 0)) : 0)
// 		| (GetLocalCapa(cfg) ? IPMSG_ENCRYPTOPT : 0)
// 		| IPMSG_CAPUTF8OPT
// 		| IPMSG_ENCEXTMSGOPT;
}


/*
wxCharBuffer cbf = strMsg.mb_str();
wxMemoryOutputStream data(cbf.data(), cbf.length());
*/