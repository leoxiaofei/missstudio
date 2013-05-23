#include "MissTaskDb.h"
#include <wx/wxsqlite3.h>
#include "../../../include/MissAPI/datatype/TaskDef.h"

class MissTaskDb::Impl
{
public:
	static const wxString s_SQL[];
	enum E_SQL
	{
		SQL_CREATE_TASKDATA,
		SQL_INSERT_TASKDATA,
		SQL_UPDATE_TASKDATA,
		SQL_DELETE_TASKDATA,
	};
};

const wxString MissTaskDb::Impl::s_SQL[] =
{
	wxT("CREATE TABLE TaskData (TD_Id INTEGER PRIMARY KEY NOT NULL, TD_DateType INTEGER, TD_TaskDate TEXT,")
	wxT("TD_TimeType INTEGER, TD_TaskTime TEXT, PI_Id INTEGER, TD_TaskContent TEXT, TD_Enable INTEGER);"),

	wxT("INSERT INTO TaskData(TD_DateType, TD_TaskDate, TD_TimeType, TD_TaskTime, PI_Id, TD_TaskContent, TD_Enable) ")
	wxT("VALUES($TD_DateType, $TD_TaskDate, $TD_TimeType, $TD_TaskTime, $PI_Id, $TD_TaskContent, $TD_Enable);"),

	wxT("UPDATE TaskData SET TD_DateType = $TD_DateType, TD_TaskDate = $TD_TaskDate, TD_TimeType = $TD_TimeType,")
	wxT("TD_TaskTime = $TD_TaskTime, TD_TaskContent = $TD_TaskContent, TD_Enable = $TD_Enable WHERE TD_Id = $TD_Id ")
	wxT("AND PI_Id = $PI_Id;"),

	wxT("DELETE FROM TaskData WHERE TD_Id = $TD_Id AND PI_Id = $PI_Id;"),

	wxT("SELECT * FROM TaskData WHERE TD_Id = $TD_Id;"),
};

MissTaskDb::MissTaskDb( wxSQLite3Database& dbMain )
: MissDbBase(dbMain)
, m_pImpl(new Impl)
{

}

MissTaskDb::~MissTaskDb()
{

}

void MissTaskDb::InitDB( wxSQLite3Database& dbMain )
{
	if(!dbMain.TableExists(wxT("TaskData")))
	{
		dbMain.ExecuteQuery(Impl::s_SQL[Impl::SQL_CREATE_TASKDATA]);
	}
}

int MissTaskDb::InsertTaskData( const wxString& strGuid, const Miss::TaskDef &data )
{
	int nPiId;
	GetIdByGuid(strGuid, nPiId);
	wxSQLite3Statement statement;
	statement = m_dbMain.PrepareStatement(Impl::s_SQL[Impl::SQL_INSERT_TASKDATA]);
	statement.Bind(statement.GetParamIndex(wxT("$TD_DateType")), data.ptDate->GetType());
// 	statement.Bind(statement.GetParamIndex(wxT("$TD_TaskDate")), );
// 	statement.Bind(statement.GetParamIndex(wxT("$TD_TimeType")), );
// 	statement.Bind(statement.GetParamIndex(wxT("$TD_TaskTime")), );
	statement.Bind(statement.GetParamIndex(wxT("$PI_Id")), nPiId);
	statement.Bind(statement.GetParamIndex(wxT("$TD_TaskContent")), data.strData);
	statement.Bind(statement.GetParamIndex(wxT("$TD_Enable")), data.bEnable ? 1 : 0);
	statement.ExecuteUpdate();

	return GetLastId();
}

void MissTaskDb::UpdateTaskData( const wxString& strGuid, const Miss::TaskDef &data )
{

}

void MissTaskDb::DeleteTaskData( const wxString& strGuid, int nID )
{

}

void MissTaskDb::SelectTaskData( const wxString& strGuid, std::vector<std::tr1::shared_ptr<Miss::TaskDef> >& vecData )
{

}

