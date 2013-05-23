#ifndef MISSNETMESSAGEBASE_H__
#define MISSNETMESSAGEBASE_H__

#include <wx/string.h>

class MissIPAddress;

class MissNetMessageBase
{
public:
	virtual ~MissNetMessageBase() {}

	void Receive(const MissIPAddress& addr, );

protected:


private:
};
#endif // MISSNETMESSAGEBASE_H__
