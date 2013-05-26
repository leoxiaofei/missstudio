#ifndef MISSCOMMUNICATE_H__
#define MISSCOMMUNICATE_H__

#include "MissAPI\plugin\MissNetMessageBase.h"

#include <memory>


#include <wx/event.h>

class IMissUDP;


class MissCommunicate : public MissNetMessageBase
{
	class Impl;
public:
	MissCommunicate();
	~MissCommunicate();

	void InitNet(const std::tr1::shared_ptr<IMissUDP>& ptUDP);

	virtual void Receive( const MissIPAddress& addr, const wxMemoryOutputStream& data );

	void SendMsg(const wxString& strMsg);

	wxEvtHandler* GetHandle() const;

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSCOMMUNICATE_H__
