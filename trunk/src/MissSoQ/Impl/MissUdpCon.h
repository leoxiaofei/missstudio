#ifndef MISSUDPCON_H__
#define MISSUDPCON_H__


#include "MissAPI\plugin\MissNetMessageBase.h"

#include <memory>


#include <wx/event.h>

class IMissUDP;


class MissUdpCon : public MissNetMessageBase
{
	class Impl;
public:
	MissUdpCon();
	~MissUdpCon();

	void InitNet(const std::tr1::shared_ptr<IMissUDP>& ptUDP, unsigned short sPort = 2425);

	virtual void Receive( const MissIPAddress& addr, const wxMemoryOutputStream& data );

	void SendMsg(const MissIPAddress& addr, const wxMemoryOutputStream& sMsg);
	//void SendTo(const MissIPAddress& addr, const wxString& strMsg);

	wxEvtHandler* GetHandle() const;

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

wxDECLARE_EVENT(wxEVT_RECEIVE_UDP, wxCommandEvent);


#endif // MISSUDPCON_H__
