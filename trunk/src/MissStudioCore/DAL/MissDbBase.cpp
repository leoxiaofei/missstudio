#include "MissDbBase.h"

#include <wx/wxsqlite3.h>

class MissDbBase::Impl
{
public:
	static const wxString s_SQL[];
	enum E_SQL
	{
		SQL_SELECT_LASTID,
		SQL_CREATE_PLUGININFO,
		SQL_CREATE_PLUGININFO_INDEX,
		SQL_INSERT_PLUGININFO,
		SQL_SELECT_PLUGININFO_ID,
		SQL_SELECT_PLUGININFO_GUID,
	};
};

const wxString MissDbBase::Impl::s_SQL[] =
{
	wxT("SELECT last_insert_rowid();"),
	
	wxT("CREATE TABLE PluginInfo (PI_Id INTEGER primary key NOT NULL, PI_PGuid TEXT);"),

	wxT("CREATE INDEX PluginInfo_Index ON PluginInfo(PI_PGuid);"),

	wxT("INSERT INTO PluginInfo VALUES(NULL, $PI_PGuid);"),

	wxT("SELECT PI_Id FROM PluginInfo WHERE PI_PGuid=$PI_PGuid;"),

	wxT("SELECT PI_PGuid FROM PluginInfo WHERE PI_Id=$PI_Id;"),
};

MissDbBase::MissDbBase( wxSQLite3Database& dbMain )
: m_dbMain(dbMain)
, m_pImpl(new Impl)
{

}

MissDbBase::~MissDbBase()
{

}

void MissDbBase::InitDB( wxSQLite3Database& dbMain )
{
	if(!dbMain.TableExists(wxT("PluginInfo")))
	{
		dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_CREATE_PLUGININFO]);
		dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_CREATE_PLUGININFO_INDEX]);
	}
}

int MissDbBase::GetLastId() const
{
	int nRet(0);
	wxSQLite3ResultSet result = m_dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_SELECT_LASTID]);
	nRet = result.GetInt(0, 0);
	result.Finalize();
	return nRet;
}

bool MissDbBase::GetIdByGuid( const wxString& strGuid, int& nId )
{
	bool bRet(true);
	wxSQLite3Statement statement = m_dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_SELECT_PLUGININFO_ID]);
	statement.Bind(statement.GetParamIndex(wxT("$PI_PGuid")), strGuid);
	wxSQLite3ResultSet result = statement.ExecuteQuery();
	if (result.NextRow())
	{
		nId = result.GetInt(wxT("PI_Id"));
	}
	else
	{
		statement = m_dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_INSERT_PLUGININFO]);
		statement.Bind(statement.GetParamIndex(wxT("$PI_PGuid")), strGuid);
		statement.ExecuteUpdate();
		result = m_dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_SELECT_LASTID]);
		nId = result.GetInt(0, 0);
	}
	result.Finalize();
	return bRet;
}

bool MissDbBase::GetGuidById( const int& nId, wxString& strGuid )
{
	bool bRet(false);
	wxSQLite3Statement statement = m_dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_SELECT_PLUGININFO_GUID]);
	statement.Bind(statement.GetParamIndex(wxT("$PI_Id")), nId);
	wxSQLite3ResultSet result = statement.ExecuteQuery();
	if (result.NextRow())
	{
		strGuid = result.GetString(wxT("PI_PGuid"));
		bRet = true;
	}
	result.Finalize();
	return bRet;
}
