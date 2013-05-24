#ifndef IMISSNETWORK_H__
#define IMISSNETWORK_H__

#include "..\MissApiDef.h"
#include <memory>
#include <wx/string.h>

class IMissUDP;

INTERFACE_BEGIN(IMissNetwork)

IDEF(std::tr1::shared_ptr<IMissUDP> GetUDP())
	
INTERFACE_END

class wxMemoryOutputStream;
class MissNetMessageBase;

struct MissIPAddress
{
	wxString       strSrcAddr;
	unsigned short sSrcPort;
	wxString       strDesAddr;
	unsigned short sDesPort;
};

INTERFACE_BEGIN(IMissUDP)

	IDEF( bool Listen(const MissIPAddress& addr, MissNetMessageBase* pMessage) )
	IDEF( bool UnListen(MissNetMessageBase* pMessage) )

	IDEF( bool SendTo(const MissIPAddress& addr, const wxMemoryOutputStream& data) )

INTERFACE_END

#endif // IMISSNETWORK_H__
