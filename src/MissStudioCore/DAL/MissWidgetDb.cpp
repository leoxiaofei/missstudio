#include "MissWidgetDb.h"
#include <wx/wxsqlite3.h>


class MissWidgetDb::Impl
{
public:
	static const wxString s_SQL[];
	enum E_SQL
	{
		SQL_CREATE_WIDGETS,
		SQL_INSERT_WIDGETS,
		SQL_SELECT_WIDGETS,
		SQL_UPDATE_WIDGETS,
		SQL_DELETE_WIDGETS,
		SQL_CREATE_WIDGETPARAS,
		SQL_INSERT_WIDGETPARAS,
		SQL_SELECT_WIDGETPARAS,
		SQL_DELETE_WIDGETPARAS,
	};
};

const wxString MissWidgetDb::Impl::s_SQL[] =
{
	wxT("CREATE TABLE Widgets (W_Id INTEGER primary key NOT NULL, PI_Id INTEGER, W_WType INTEGER,")
	wxT("W_Zone INTEGER, W_Opacity INTEGER, W_Pos TEXT, W_Shadow INTEGER, W_Pin INTEGER, W_ZPos INTEGER);"),

	wxT("INSERT INTO Widgets(PI_Id, W_WType, W_Zone, W_Opacity, W_Pos, W_Shadow, W_Pin, W_ZPos) ")
	wxT("VALUES($PI_Id, $W_WType, $W_Zone, $W_Opacity, $W_Pos, $W_Shadow, $W_Pin, $W_ZPos);"),

	wxT("SELECT * FROM Widgets;"),

	wxT("UPDATE Widgets SET W_Zone = $W_Zone, W_Opacity = $W_Opacity, W_Pos = $W_Pos,")
	wxT("W_Shadow = $W_Shadow, W_Pin = $W_Pin, W_ZPos = $W_ZPos WHERE W_Id = $W_Id;"),

	wxT("DELETE FROM Widgets WHERE W_Id = $W_Id;"),

	wxT("CREATE TABLE WidgetParas (W_Id INTEGER, WP_Key TEXT, WP_Value TEXT );"),

	wxT("INSERT INTO WidgetParas VALUES($W_Id, $WP_Key, $WP_Value);"),

	wxT("SELECT WP_Key, WP_Value FROM WidgetParas WHERE W_Id = $W_Id;"),

	wxT("DELETE FROM WidgetParas WHERE W_Id = $W_Id;"),
};

MissWidgetDb::MissWidgetDb(wxSQLite3Database& dbMain)
: MissDbBase(dbMain)
, m_pImpl(new Impl)
{
}

MissWidgetDb::~MissWidgetDb()
{
}

void MissWidgetDb::InitDB( wxSQLite3Database& dbMain )
{
	if(!dbMain.TableExists(wxT("Widgets")))
	{
		dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_CREATE_WIDGETS]);
		dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_CREATE_WIDGETPARAS]);
	}
}

bool MissWidgetDb::SaveRunWidgets( const std::vector<RunWidgetData>& vecRunWidgets )
{
	bool bRet(false);
	if (!vecRunWidgets.empty())
	{
		wxString strTemp;
		m_dbMain.Begin();
		for (std::vector<RunWidgetData>::const_iterator citor = vecRunWidgets.begin();
			citor != vecRunWidgets.end(); ++citor)
		{
			wxSQLite3Statement statement = m_dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_UPDATE_WIDGETS]);
			statement.Bind(statement.GetParamIndex(wxT("$W_Zone")), (int)citor->sWidgetPara.m_uZone);
			statement.Bind(statement.GetParamIndex(wxT("$W_Opacity")), (int)citor->sWidgetPara.m_uOpacity);
			strTemp.Printf(wxT("%d:%d"), citor->sWidgetPara.m_ptPos.x, citor->sWidgetPara.m_ptPos.y);
			statement.Bind(statement.GetParamIndex(wxT("$W_Pos")), strTemp);
			statement.Bind(statement.GetParamIndex(wxT("$W_Shadow")), citor->sWidgetPara.m_bShadow ? 1 : 0);
			statement.Bind(statement.GetParamIndex(wxT("$W_Pin")), citor->sWidgetPara.m_bPin ? 1 : 0);
			statement.Bind(statement.GetParamIndex(wxT("$W_ZPos")), citor->sWidgetPara.m_nZPos);
			statement.Bind(statement.GetParamIndex(wxT("$W_Id")), (int)citor->sWidgetPara.m_uRunID);
			statement.ExecuteUpdate();

			statement = m_dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_DELETE_WIDGETPARAS]);
			statement.Bind(statement.GetParamIndex(wxT("$W_Id")), (int)citor->sWidgetPara.m_uRunID);
			statement.ExecuteUpdate();

			for (CustomPara::const_iterator citorParam = citor->sWidgetPara.m_vecPara.begin();
				citorParam != citor->sWidgetPara.m_vecPara.end(); ++citorParam)
			{
				statement = m_dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_INSERT_WIDGETPARAS]);
				statement.Bind(statement.GetParamIndex(wxT("$W_Id")), (int)citor->sWidgetPara.m_uRunID);
				statement.Bind(statement.GetParamIndex(wxT("$WP_Key")), citorParam->first);
				statement.Bind(statement.GetParamIndex(wxT("$WP_Value")), citorParam->second);
				statement.ExecuteUpdate();
			}
		}
		m_dbMain.Commit();
	}

	return bRet;
}

bool MissWidgetDb::LoadRunWidgets( std::vector<RunWidgetData>& vecRunWidgets )
{
	bool bRet(true);
	wxSQLite3Statement statement;
	wxSQLite3ResultSet resParam;
	RunWidgetData data;
	wxString strPos;
	long lTemp;
	int nPiId;
	wxSQLite3ResultSet result = m_dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_SELECT_WIDGETS]);
	while (result.NextRow())
	{
		nPiId = result.GetInt(wxT("PI_Id"));
		GetGuidById(nPiId, data.strGuid);

		data.nWidgetId               = result.GetInt(wxT("W_WType"));
		data.sWidgetPara.m_uRunID    = result.GetInt(wxT("W_Id"));
		data.sWidgetPara.m_uZone     = result.GetInt(wxT("W_Zone"));
		data.sWidgetPara.m_uOpacity  = result.GetInt(wxT("W_Opacity"));
		data.sWidgetPara.m_bShadow   = result.GetBool(wxT("W_Shadow"));
		data.sWidgetPara.m_bPin      = result.GetBool(wxT("W_Pin"));
		data.sWidgetPara.m_nZPos     = result.GetInt(wxT("W_ZPos"));
		strPos                       = result.GetString(wxT("W_Pos"), wxT("0:0"));
		if(strPos.BeforeFirst(wxT(':')).ToLong(&lTemp))
		{
			data.sWidgetPara.m_ptPos.x = lTemp;
		}
		if(strPos.AfterFirst(wxT(':')).ToLong(&lTemp))
		{
			data.sWidgetPara.m_ptPos.y = lTemp;
		}

		statement = m_dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_SELECT_WIDGETPARAS]);
		statement.Bind(statement.GetParamIndex(wxT("$W_Id")), (int)data.sWidgetPara.m_uRunID);
		resParam = statement.ExecuteQuery();
		while (resParam.NextRow())
		{
			data.sWidgetPara.m_vecPara.insert(CustomPara::value_type(
				resParam.GetString(wxT("WP_Key")), resParam.GetString(wxT("WP_Value"))));
		}
		resParam.Finalize();
		vecRunWidgets.push_back(data);
	}
	result.Finalize();
	return bRet;
}

bool MissWidgetDb::NewRunWidget( const wxString& strGuid, int nWidgetId, DTD::SWidgetPara& sWidgetPara )
{
	wxString strTemp;
	int nPiId;
	GetIdByGuid(strGuid, nPiId);
	wxSQLite3Statement statement;
	statement = m_dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_INSERT_WIDGETS]);
	statement.Bind(statement.GetParamIndex(wxT("$PI_Id")), nPiId);
	statement.Bind(statement.GetParamIndex(wxT("$W_WType")), nWidgetId);
	statement.Bind(statement.GetParamIndex(wxT("$W_Zone")), (int)sWidgetPara.m_uZone);
	statement.Bind(statement.GetParamIndex(wxT("$W_Opacity")), (int)sWidgetPara.m_uOpacity);
	strTemp.Printf(wxT("%d:%d"), sWidgetPara.m_ptPos.x, sWidgetPara.m_ptPos.y);
	statement.Bind(statement.GetParamIndex(wxT("$W_Pos")), strTemp);
	statement.Bind(statement.GetParamIndex(wxT("$W_Shadow")), sWidgetPara.m_bShadow ? 1 : 0);
	statement.Bind(statement.GetParamIndex(wxT("$W_Pin")), sWidgetPara.m_bPin ? 1 : 0);
	statement.Bind(statement.GetParamIndex(wxT("$W_ZPos")), sWidgetPara.m_nZPos);
	statement.ExecuteUpdate();

	sWidgetPara.m_uRunID = GetLastId();
	return true;
}

bool MissWidgetDb::DelRunWidget( unsigned int uRunId )
{
	wxSQLite3Statement statement = m_dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_DELETE_WIDGETS]);
	statement.Bind(statement.GetParamIndex(wxT("$W_Id")), (int)uRunId);
	statement.ExecuteUpdate();

	return true;
}


