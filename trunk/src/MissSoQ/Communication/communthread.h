#ifndef COMMUNTHREAD_H__
#define COMMUNTHREAD_H__

#include <memory>
#include <wx/event.h>

class wxEvtHandler;
class wxMemoryOutputStream;

class CommunThread
{
	class Impl;
public:
	CommunThread(wxEvtHandler& hHandler);
	~CommunThread();

	void Start();
	void Exit();

	void Broadcast(const wxMemoryOutputStream& sData, unsigned short uPort = 2425);
	void SendTo(const wxMemoryOutputStream& sData, const wxString& strAddr, unsigned short uPort = 2425);

protected:
	void Run();


private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};


wxDECLARE_EVENT(wxEVT_COMMUN_NOTIFY, wxEvent);

#endif // COMMUNTHREAD_H__
