#include "MissWidgetsDAL.h"
#include <wx/wxsqlite3.h>

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

    wxT("CREATE TABLE Widgets (W_ID INTEGER primary key NOT NULL, W_PName TEXT, "
        "W_WType INTEGER, W_Zone INTEGER, W_Opacity INTEGER, W_Pos INTEGER);"),
    wxT("INSERT INTO Widgets VALUES(NULL, $W_PName, $W_WType, $W_Zone, $W_Opacity, $W_Pos);"),
    wxT("UPDATE Widgets SET W_Zone = $W_Zone, W_Opacity = $W_Opacity, W_Pos = $W_Pos WHERE W_ID = $W_ID);"),
    wxT("DELETE FROM Widgets WHERE W_ID = $W_ID;")

    wxT("CREATE TABLE WidgetParas (W_ID INTEGER, WP_Key TEXT, WP_Value TEXT );"),
    wxT("INSERT INTO WidgetParas VALUES($W_ID, $WP_Key, $WP_Value);"),
    wxT("DELETE FROM WidgetParas WHERE W_ID = $W_ID;")



    wxT("last_insert_rowid();"),
};

MissWidgetsDAL::MissWidgetsDAL()
: m_pImpl(new Impl)
{
    //ctor
    m_pImpl->dbMain.Open(wxT("MainDB.db3"));

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

int MissWidgetsDAL::NewWidget(const wxString& strPName, int nType)
{
    /*
    wxSQLite3Statement query = m_pImpl->dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_INSERT_WIDGETS]);
    query.Bind(1,data.nDateType);
    query.Bind(2,data.strTaskDate);
    query.Bind(3,data.nRemindType);
    query.Bind(4,data.nTimeType);
    query.Bind(5,data.strTaskTime);
    query.Bind(6,data.nEvery);
    query.Bind(7,data.nTaskType);
    query.Bind(8,data.strPlugInGUID);
    query.Bind(9,data.strTaskContent);
    query.Bind(10,nID);

    query.ExecuteUpdate();
    */
    return 0;
}
