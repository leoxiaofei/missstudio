#include "MissCoreDb.h"
#include <wx/wxsqlite3.h>

class MissCoreDb::Impl
{
public:
	static const wxString s_SQL[];
	enum E_SQL
	{
		SQL_CREATE_CORECONFIG,
	};
};

const wxString MissCoreDb::Impl::s_SQL[] =
{
	wxT("CREATE TABLE CoreConfig (CC_Key TEXT primary key, CC_Value TEXT);"),
};

MissCoreDb::MissCoreDb( wxSQLite3Database& dbMain )
: MissDbBase(dbMain)
, m_pImpl(new Impl)
{

}


MissCoreDb::~MissCoreDb()
{

}

void MissCoreDb::InitDB( wxSQLite3Database& dbMain )
{
	if(!dbMain.TableExists(wxT("CoreConfig")))
	{
		dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_CREATE_CORECONFIG]);
	}
}


