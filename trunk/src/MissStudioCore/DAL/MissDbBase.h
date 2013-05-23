#ifndef MISSDBBASE_H__
#define MISSDBBASE_H__

#include <wx/string.h>
#include <memory>

class wxSQLite3Database;

class MissDbBase
{
	class Impl;
public:
	MissDbBase(wxSQLite3Database& dbMain);
	virtual ~MissDbBase();

	static void InitDB(wxSQLite3Database& dbMain);

protected:
	int  GetLastId() const;

	bool  GetIdByGuid(const wxString& strGuid, int& nId);
	bool  GetGuidById(const int& nId, wxString& strGuid);

	wxSQLite3Database& m_dbMain;

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSDBBASE_H__
