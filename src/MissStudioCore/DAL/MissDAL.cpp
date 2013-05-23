#include "MissDAL.h"
#include "../Common/MissPaths.h"
#include "MissWidgetDb.h"

#include <wx/wxsqlite3.h>
#include <map>
#include "MissTaskDb.h"
#include "MissCoreDb.h"

typedef MissDbBase* (*FuncCreator)(wxSQLite3Database& dbMain);

template <class T>
MissDbBase* CreateDB(wxSQLite3Database& dbMain)
{
	return new T(dbMain);
};

class MissDAL::Impl
{
public:
    wxSQLite3Database dbMain;
	std::map<DB_TYPE, FuncCreator> mapCreator;
};


MissDAL::MissDAL()
: m_pImpl(new Impl)
{
    wxString strPath = MissPaths::Instance().GetConfigPath() + wxT("MainDB.db3");
	wxSQLite3Database& dbMain = m_pImpl->dbMain;
    dbMain.Open(strPath);

	m_pImpl->mapCreator.insert(std::make_pair(DT_CORECONFIG, &CreateDB<MissCoreDb>));
	m_pImpl->mapCreator.insert(std::make_pair(DT_WIDGETS,    &CreateDB<MissWidgetDb>));
	m_pImpl->mapCreator.insert(std::make_pair(DT_TASKDATA,   &CreateDB<MissTaskDb>));

	dbMain.Begin();
	MissDbBase::InitDB(dbMain);
	MissCoreDb::InitDB(dbMain);
	MissWidgetDb::InitDB(dbMain);
	MissTaskDb::InitDB(dbMain);
	dbMain.Commit();
}

MissDAL::~MissDAL()
{
    //dtor
}

std::tr1::shared_ptr<MissDbBase> MissDAL::GetDbPtr( DB_TYPE eType )
{
	MissDbBase* pRet(NULL);
	std::map<DB_TYPE, FuncCreator>::iterator iFind = m_pImpl->mapCreator.find(eType);
	if (iFind != m_pImpl->mapCreator.end())
	{
		pRet = (*(iFind->second))(m_pImpl->dbMain);
	}
	return std::tr1::shared_ptr<MissDbBase>(pRet);
}

void MissDAL::VacuumDB()
{
	m_pImpl->dbMain.ExecuteUpdate("VACUUM;");
}

