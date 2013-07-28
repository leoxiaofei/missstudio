#ifndef MISSCOMDEF_H__
#define MISSCOMDEF_H__

#include <wx\string.h>

class HostInfo
{
public:
	wxString       strUserName;
	wxString       strHostName;
	wxString       strAddr;
	unsigned short uPortNo;
};


class UserInfo
{
public:
	HostInfo       hostInfo;

};
#endif // MISSCOMDEF_H__
