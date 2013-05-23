#include "MissTaskDbMethod.h"
#include "MissAPI\datatype\TaskDef.h"

typedef std::map<int, std::tr1::shared_ptr<DbMethodBase> > MethodContainer;

class DbMethodFactory::Impl
{
public:
	 MethodContainer mapDateMethod;
	 MethodContainer mapTimeMethod;
};

DbMethodFactory::DbMethodFactory()
: m_pImpl(new Impl)
{
	Init();
}

DbMethodFactory::~DbMethodFactory()
{

}

void DbMethodFactory::Init()
{
	MethodContainer& mapDateMethod = m_pImpl->mapDateMethod;
	MethodContainer& mapTimeMethod = m_pImpl->mapTimeMethod;

	mapDateMethod[DateUsual::TYPE] = std::tr1::shared_ptr<DbMethodBase>(new DateUsualMethod);
	mapDateMethod[DateDaily::TYPE] = std::tr1::shared_ptr<DbMethodBase>(new DateDailyMethod);
	mapDateMethod[DateWeekly::TYPE] = std::tr1::shared_ptr<DbMethodBase>(new DateWeeklyMethod);
	mapDateMethod[DateMonthly::TYPE] = std::tr1::shared_ptr<DbMethodBase>(new DateMonthlyMethod);
	mapDateMethod[DateYearly::TYPE] = std::tr1::shared_ptr<DbMethodBase>(new DateYearlyMethod);

	mapTimeMethod[TimeUsual::TYPE] = std::tr1::shared_ptr<DbMethodBase>(new TimeUsualMethod);
	mapTimeMethod[TimeLaunch::TYPE] = std::tr1::shared_ptr<DbMethodBase>(new TimeLaunchMethod);
	mapTimeMethod[TimeShut::TYPE] = std::tr1::shared_ptr<DbMethodBase>(new TimeShutMethod);
}

std::tr1::shared_ptr<DbMethodBase> DbMethodFactory::GetDateMethod( int nType ) const
{
	std::tr1::shared_ptr<DbMethodBase> ptRet;
	MethodContainer::const_iterator ciFind = m_pImpl->mapDateMethod.find(nType);
	if (ciFind != m_pImpl->mapDateMethod.end())
	{
		ptRet = ciFind->second;
	}
	return ptRet;
}

std::tr1::shared_ptr<DbMethodBase> DbMethodFactory::GetTimeMethod( int nType ) const
{
	std::tr1::shared_ptr<DbMethodBase> ptRet;
	MethodContainer::const_iterator ciFind = m_pImpl->mapTimeMethod.find(nType);
	if (ciFind != m_pImpl->mapTimeMethod.end())
	{
		ptRet = ciFind->second;
	}
	return ptRet;
}

bool DateUsualMethod::ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const
{
	DateUsual* p = new DateUsual;
	wxDateTime time;
	time.ParseISODate(result.GetString(wxT("TD_TaskDate")));
	p->year = time.GetYear();
	p->month = time.GetMonth();
	p->day = time.GetDay();
	data.ptDate = std::tr1::shared_ptr<DateBase>(p);
}

bool DateUsualMethod::WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const
{
	DateUsual* p = static_cast<DateUsual>(data.ptDate.get());
	statement.Bind(statement.GetParamIndex(wxT("$TD_DateType")), DateUsual::TYPE);
	wxString strTemp;
	strTemp.Printf(wxT("%04d-%02d-%02d"), p->year, p->month, p->day);
	statement.Bind(statement.GetParamIndex(wxT("$TD_TaskDate")), strTemp);
}

bool DateDailyMethod::ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const
{
	DateDaily* p = new DateDaily;
	wxString strDate = result.GetString(wxT("TD_TaskDate"));
	p->
	wxDateTime time;
	time.ParseISODate();
	p->year = time.GetYear();
	p->month = time.GetMonth();
	p->day = time.GetDay();
	data.ptDate = std::tr1::shared_ptr<DateBase>(p);
}

bool DateDailyMethod::WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool DateWeeklyMethod::ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool DateWeeklyMethod::WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool DateMonthlyMethod::ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool DateMonthlyMethod::WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool DateYearlyMethod::ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool DateYearlyMethod::WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool TimeUsualMethod::ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool TimeUsualMethod::WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool TimeLaunchMethod::ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool TimeLaunchMethod::WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool TimeShutMethod::ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const
{
	throw std::exception("The method or operation is not implemented.");
}

bool TimeShutMethod::WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const
{
	throw std::exception("The method or operation is not implemented.");
}
