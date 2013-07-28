#ifndef MISSCOMMUNICATE_H__
#define MISSCOMMUNICATE_H__

#include <memory>
#include <wx/event.h>

class MissMessageEvent;

class MissCommunicate
{
	class Impl;
public:

	static MissCommunicate& Instance()
	{
		static MissCommunicate theSingleton;
		return theSingleton;
	}

	void Init();

	void GetUserList();

	void NoOperation();
	void Online();
	void Offline();
	void SendMsg();

	wxEvtHandler* GetHandle() const;

	void Exit();

protected:
	void ConnectReady(wxEvent& event);

	void ReceiveData(MissMessageEvent& event);


private:
	MissCommunicate();
	~MissCommunicate();
	MissCommunicate(const MissCommunicate&);
	MissCommunicate& operator=(const MissCommunicate&);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};



#endif // MISSCOMMUNICATE_H__
