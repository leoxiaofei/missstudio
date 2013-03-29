#ifndef MISSWIDGETSDAL_H
#define MISSWIDGETSDAL_H


#include <memory>
#include "..\Common\WidgetDef.h"

struct RunWidgetData
{
    wxString         strGuid;
    int              nWidgetId;
    DTD::SWidgetPara sWidgetPara;
};

class MissWidgetsDAL
{
    class Impl;

public:
    static MissWidgetsDAL& Instance()
    {
        static MissWidgetsDAL theSingleton;
        return theSingleton;
    }

    bool SaveRunWidgets(const std::vector<RunWidgetData>& vecRunWidgets);
    bool LoadRunWidgets(std::vector<RunWidgetData>& vecRunWidgets);

    bool NewRunWidget(const wxString& strGuid, int nWidgetId, DTD::SWidgetPara& sWidgetPara);
    bool DelRunWidget(unsigned int uRunId);

protected:
    void InitDB();
    int  GetLastId();

private:
    MissWidgetsDAL();
    ~MissWidgetsDAL();
    MissWidgetsDAL(const MissWidgetsDAL&);
    MissWidgetsDAL& operator=(const MissWidgetsDAL&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSWIDGETSDAL_H
