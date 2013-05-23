#ifndef IMISSNETWORK_H__
#define IMISSNETWORK_H__


INTERFACE_BEGIN(IMissNetwork)

	IDEF()
	
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
