#ifndef MISSCORECONFIGDB_H__
#define MISSCORECONFIGDB_H__

#include "MissDbBase.h"


class MissCoreDb : public MissDbBase
{
	class Impl;
public:
	MissCoreDb(wxSQLite3Database& dbMain);
	~MissCoreDb();

	static void InitDB(wxSQLite3Database& dbMain);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // MISSCORECONFIGDB_H__
