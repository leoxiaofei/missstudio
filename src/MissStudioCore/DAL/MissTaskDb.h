#ifndef MISSTASKDB_H__
#define MISSTASKDB_H__

#include "MissDbBase.h"

#include "wx/hashmap.h"

#include <vector>
#include <unordered_map>


namespace Miss
{
	class TaskDef;
}

typedef std::tr1::unordered_map<wxString, std::vector<std::tr1::shared_ptr<Miss::TaskDef> >,
	wxStringHash, wxStringEqual> PluginTaskData;

class MissTaskDb : public MissDbBase
{
	class Impl;
public:
	MissTaskDb(wxSQLite3Database& dbMain);
	~MissTaskDb();

	static void InitDB(wxSQLite3Database& dbMain);

	int  InsertTaskData(const wxString& strGuid, const Miss::TaskDef &data);
	void UpdateTaskData(const wxString& strGuid, const Miss::TaskDef &data);
	void DeleteTaskData(const wxString& strGuid, int nID);
	void SelectTaskData(const wxString& strGuid, std::vector<std::tr1::shared_ptr<Miss::TaskDef> >& vecData);

	void QusetTurnOnRemind(const wxString &strDate, PluginTaskData &vecData);
	void QusetTurnOffRemind(const wxString &strDate, PluginTaskData &vecData);
	void QusetNextRemind(const wxString &strDate, const wxString &strTime, PluginTaskData &vecData);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSTASKDB_H__
