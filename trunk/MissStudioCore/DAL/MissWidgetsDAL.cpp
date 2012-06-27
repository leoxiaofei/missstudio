#include "MissWidgetsDAL.h"
#include <wx/wxsqlite3.h>

class MissWidgetsDAL::MissWidgetsDALImpl
{
public:
    wxSQLite3Database dbMain;

    static const wxString s_SQL[];
    enum E_SQL
    {
        SQL_CTEATE_CORECONFIG
    };
};

const wxString MissWidgetsDAL::MissWidgetsDALImpl::s_SQL[] =
{
    wxT("CREATE TABLE CoreConfig (CC_Key TEXT primary key, CC_Value TEXT);")
};

MissWidgetsDAL::MissWidgetsDAL()
: m_pImpl(new MissWidgetsDALImpl)
{
    //ctor
    m_pImpl->dbMain.Open(wxT("MainDB.db3"));

    if(!m_pImpl->dbMain.TableExists(wxT("CoreConfig")))
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
    m_pImpl->dbMain.ExecuteUpdate(MissWidgetsDALImpl::s_SQL[MissWidgetsDALImpl::SQL_CTEATE_CORECONFIG]);
}
