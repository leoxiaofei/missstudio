#ifndef MISSNETMESSAGEBASE_H__
#define MISSNETMESSAGEBASE_H__

#include <wx/string.h>

class MissIPAddress;

class MissNetMessageBase
{
public:
	virtual ~MissNetMessageBase() {}

	virtual void Receive(const MissIPAddress& addr, const wxMemoryOutputStream& data) = 0;

protected:


private:
};
#endif // MISSNETMESSAGEBASE_H__
