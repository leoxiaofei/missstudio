#ifndef MISSWIDGETDB_H__
#define MISSWIDGETDB_H__


#include "MissDbBase.h"
#include <vector>

#include "..\Common\WidgetDef.h"

struct RunWidgetData
{
	wxString         strGuid;
	int              nWidgetId;
	DTD::SWidgetPara sWidgetPara;
};

class MissWidgetDb : public MissDbBase
{
	class Impl;
public:
	MissWidgetDb(wxSQLite3Database& dbMain);
	~MissWidgetDb();

	static void InitDB(wxSQLite3Database& dbMain);

	bool SaveRunWidgets(const std::vector<RunWidgetData>& vecRunWidgets);
	bool LoadRunWidgets(std::vector<RunWidgetData>& vecRunWidgets);

	bool NewRunWidget(const wxString& strGuid, int nWidgetId, DTD::SWidgetPara& sWidgetPara);
	bool DelRunWidget(unsigned int uRunId);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};





#endif // MISSWIDGETDB_H__