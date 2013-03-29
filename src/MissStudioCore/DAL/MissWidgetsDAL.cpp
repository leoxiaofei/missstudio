#include "MissWidgetsDAL.h"
#include <wx/wxsqlite3.h>
#include "../Common/MissPaths.h"

class MissWidgetsDAL::Impl
{
public:
    wxSQLite3Database dbMain;

    static const wxString s_SQL[];
    enum E_SQL
    {
        SQL_CREATE_CORECONFIG,
        SQL_CREATE_WIDGETS,
        SQL_INSERT_WIDGETS,
        SQL_SELECT_WIDGETS,
        SQL_UPDATE_WIDGETS,
        SQL_DELETE_WIDGETS,
        SQL_CREATE_WIDGETPARAS,
        SQL_INSERT_WIDGETPARAS,
        SQL_DELETE_WIDGETPARAS,
        SQL_SELECT_LASTID
    };
};

const wxString MissWidgetsDAL::Impl::s_SQL[] =
{
    wxT("CREATE TABLE CoreConfig (CC_Key TEXT primary key, CC_Value TEXT);"),
    
    wxT("CREATE TABLE Widgets (W_ID INTEGER primary key NOT NULL, W_PGuid TEXT, ")
    wxT("W_WType INTEGER, W_Zone INTEGER, W_Opacity INTEGER, W_Pos TEXT);"),

    wxT("INSERT INTO Widgets VALUES(NULL, $W_PGuid, $W_WType, $W_Zone, $W_Opacity, $W_Pos);"),

    wxT("SELECT W_ID, W_PGuid, W_WType, W_Zone, W_Opacity, W_Pos FROM Widgets;"),
    
    wxT("UPDATE Widgets SET W_Zone = $W_Zone, W_Opacity = $W_Opacity, W_Pos = $W_Pos WHERE W_ID = $W_ID;"),
    
    wxT("DELETE FROM Widgets WHERE W_ID = $W_ID;"),

    wxT("CREATE TABLE WidgetParas (W_ID INTEGER, WP_Key TEXT, WP_Value TEXT );"),
    
    wxT("INSERT INTO WidgetParas VALUES($W_ID, $WP_Key, $WP_Value);"),
    
    wxT("DELETE FROM WidgetParas WHERE W_ID = $W_ID;"),

    wxT("SELECT last_insert_rowid();"),
};

MissWidgetsDAL::MissWidgetsDAL()
: m_pImpl(new Impl)
{
    //ctor
    wxString strPath = MissPaths::Instance().GetConfigPath() + wxT("MainDB.db3");
    m_pImpl->dbMain.Open(strPath);

    if(!m_pImpl->dbMain.TableExists(wxT("Widgets")))
    {
        InitDB();
    }
}

MissWidgetsDAL::~MissWidgetsDAL()
{
    //dtor
}

void MissWidgetsDAL::InitDB()
{
    m_pImpl->dbMain.ExecuteUpdate(Impl::s_SQL[Impl::SQL_CREATE_CORECONFIG]);
    m_pImpl->dbMain.ExecuteUpdate(Impl::s_SQL[Impl::SQL_CREATE_WIDGETS]);
    m_pImpl->dbMain.ExecuteUpdate(Impl::s_SQL[Impl::SQL_CREATE_WIDGETPARAS]);
}

bool MissWidgetsDAL::SaveRunWidgets( const std::vector<RunWidgetData>& vecRunWidgets )
{
    bool bRet(false);
    if (!vecRunWidgets.empty())
    {
        wxString strTemp;
        m_pImpl->dbMain.Begin();
        for (std::vector<RunWidgetData>::const_iterator citor = vecRunWidgets.begin();
            citor != vecRunWidgets.end(); ++citor)
        {
            wxSQLite3Statement statement = m_pImpl->dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_UPDATE_WIDGETS]);
            statement.Bind(statement.GetParamIndex(wxT("$W_Zone")), (int)citor->sWidgetPara.m_uZone);
            statement.Bind(statement.GetParamIndex(wxT("$W_Opacity")), (int)citor->sWidgetPara.m_uOpacity);
            
            strTemp.Printf(wxT("%d:%d"), citor->sWidgetPara.m_ptPos.x, citor->sWidgetPara.m_ptPos.y);
            statement.Bind(statement.GetParamIndex(wxT("$W_Pos")), strTemp);
            statement.Bind(statement.GetParamIndex(wxT("$W_ID")), (int)citor->sWidgetPara.m_uRunID);

            statement.ExecuteUpdate();
        }
        m_pImpl->dbMain.Commit();
    }

    return bRet;
}

bool MissWidgetsDAL::LoadRunWidgets( std::vector<RunWidgetData>& vecRunWidgets )
{
    bool bRet(false);
    wxSQLite3ResultSet result = m_pImpl->dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_SELECT_WIDGETS]);
    RunWidgetData data;
    wxString strPos;
    long lTemp;
    if(result.IsOk())
    {
        while (result.NextRow())
        {
            data.strGuid                 = result.GetString(wxT("W_PGuid"));
            data.nWidgetId               = result.GetInt(wxT("W_WType"));
            data.sWidgetPara.m_uRunID    = result.GetInt(wxT("W_ID"));
            data.sWidgetPara.m_uZone     = result.GetInt(wxT("W_Zone"));
            data.sWidgetPara.m_uOpacity  = result.GetInt(wxT("W_Opacity"));
            strPos                       = result.GetString(wxT("W_Pos"), wxT("0:0"));
            if(strPos.BeforeFirst(wxT(':')).ToLong(&lTemp))
            {
                data.sWidgetPara.m_ptPos.x = lTemp;
            }
            if(strPos.AfterFirst(wxT(':')).ToLong(&lTemp))
            {
                data.sWidgetPara.m_ptPos.y = lTemp;
            }
            vecRunWidgets.push_back(data);
        }
        result.Finalize();
        bRet = true;
    }
    return bRet;
}

bool MissWidgetsDAL::NewRunWidget( const wxString& strGuid, int nWidgetId, DTD::SWidgetPara& sWidgetPara )
{
    wxString strTemp;
    wxSQLite3Statement statement;
    statement = m_pImpl->dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_INSERT_WIDGETS]);
    statement.Bind(statement.GetParamIndex(wxT("$W_PGuid")), strGuid);
    statement.Bind(statement.GetParamIndex(wxT("$W_WType")), nWidgetId);
    statement.Bind(statement.GetParamIndex(wxT("$W_Zone")), (int)sWidgetPara.m_uZone);
    statement.Bind(statement.GetParamIndex(wxT("$W_Opacity")), (int)sWidgetPara.m_uOpacity);
    strTemp.Printf(wxT("%d:%d"), sWidgetPara.m_ptPos.x, sWidgetPara.m_ptPos.y);
    statement.Bind(statement.GetParamIndex(wxT("$W_Pos")), strTemp);
    statement.ExecuteUpdate();

    sWidgetPara.m_uRunID = GetLastId();
    return true;
}

bool MissWidgetsDAL::DelRunWidget( unsigned int uRunId )
{
    wxSQLite3Statement statement = m_pImpl->dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_DELETE_WIDGETS]);
    statement.Bind(statement.GetParamIndex(wxT("$W_ID")), (int)uRunId);
    statement.ExecuteUpdate();

    return true;
}

int MissWidgetsDAL::GetLastId()
{
    int nRet(0);
    wxSQLite3ResultSet result = m_pImpl->dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_SELECT_LASTID]);
    if (result.IsOk())
    {
        nRet = result.GetInt(0, 0);
    }
    return nRet;
}

// int MissWidgetsDAL::NewWidget(const wxString& strPName, int nType)
// {
//     /*
//     wxSQLite3Statement query = m_pImpl->dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_INSERT_WIDGETS]);
//     query.Bind(1,data.nDateType);
//     query.Bind(2,data.strTaskDate);
//     query.Bind(3,data.nRemindType);
//     query.Bind(4,data.nTimeType);
//     query.Bind(5,data.strTaskTime);
//     query.Bind(6,data.nEvery);
//     query.Bind(7,data.nTaskType);
//     query.Bind(8,data.strPlugInGUID);
//     query.Bind(9,data.strTaskContent);
//     query.Bind(10,nID);
// 
//     query.ExecuteUpdate();
//     */
//     return 0;
// }
