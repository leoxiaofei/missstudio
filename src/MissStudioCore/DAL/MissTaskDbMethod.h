#ifndef MISSTASKDBMETHOD_H__
#define MISSTASKDBMETHOD_H__

class DbMethodBase
{
public:
	virtual bool ReadDb(Miss::TaskDef &data, wxSQLite3ResultSet& result) const = 0;
	virtual bool WriteDb(const Miss::TaskDef &data, wxSQLite3Statement& statement) const = 0;
};

class DbMethodFactory
{
	class Impl;
public:
	DbMethodFactory();
	~DbMethodFactory();

	std::tr1::shared_ptr<DbMethodBase> GetDateMethod(int nType) const;
	std::tr1::shared_ptr<DbMethodBase> GetTimeMethod(int nType) const;

protected:
	void Init();

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

class DateUsualMethod : public DbMethodBase
{
public:
	virtual bool ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const;
	virtual bool WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const;

};

class DateDailyMethod : public DbMethodBase
{
public:
	virtual bool ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const;
	virtual bool WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const;

};

class DateWeeklyMethod : public DbMethodBase
{
public:
	virtual bool ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const;
	virtual bool WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const;

};

class DateMonthlyMethod : public DbMethodBase
{
public:
	virtual bool ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const;
	virtual bool WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const;

};

class DateYearlyMethod : public DbMethodBase
{
public:
	virtual bool ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const;
	virtual bool WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const;

};

class TimeUsualMethod : public DbMethodBase
{
public:
	virtual bool ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const;
	virtual bool WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const;

};

class TimeLaunchMethod : public DbMethodBase
{
public:
	virtual bool ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const;
	virtual bool WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const;

};

class TimeShutMethod : public DbMethodBase
{
public:
	virtual bool ReadDb( Miss::TaskDef &data, wxSQLite3ResultSet& result ) const;
	virtual bool WriteDb( const Miss::TaskDef &data, wxSQLite3Statement& statement ) const;

};

#endif // MISSTASKDBMETHOD_H__
