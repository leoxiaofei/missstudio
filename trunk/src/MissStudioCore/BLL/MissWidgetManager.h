#ifndef MISSWIDGETMANAGER_H
#define MISSWIDGETMANAGER_H

#include "MissAPI\interface\IMissWidgetMgr.h"
#include <memory>
#include <wx\event.h>

namespace DTD
{
    struct SWidgetPara;
}

class MissWidgetFactoryBase;
class MissPluginBase;
class ImplMissWidget;

struct WidgetRelation
{
    WidgetRelation(MissWidgetFactoryBase* widget, const WidgetMajorSet& vecWidget)
    : pFactory(widget)
    , vecWidgetMajor(vecWidget){}

    MissWidgetFactoryBase* pFactory;
    WidgetMajorSet vecWidgetMajor;
};

class MissWidgetManager
{
    class Impl;
public:
    static MissWidgetManager& Instance()
    {
        static MissWidgetManager theSingleton;
        return theSingleton;
    }

    bool UnloadPlugin(MissPluginBase* pPluginBase);

    MissPluginBase* GetPluginBase(MissWidgetFactoryBase* pBase) const;

    void CreateWidget(MissWidgetFactoryBase* pBase, int nWidgetId);
    void DelRunWidget(unsigned int uRunId);

    std::vector<std::tr1::shared_ptr<WidgetRelation> >& GetWidgetData();
    std::vector<std::tr1::shared_ptr<ImplMissWidget> >& GetRunningWidget();

    bool RegWidgetFactory(MissPluginBase* pPluginBase, const WidgetMajorSet& vecWidgetMajor, MissWidgetFactoryBase* pFunc);
    bool UnRegWidgetFactory(MissWidgetFactoryBase* pFunc);

    bool GetFactoryByRunId(unsigned int uId, MissWidgetFactoryBase*& pBase);
    void GetRunIdByFactory(MissWidgetFactoryBase* pBase, std::vector<unsigned int>& vecRunId);

    void LoadRunWidget();
    void SaveRunWidget();

    wxEvtHandler* GetHandle() const;

protected:
    bool CheckWidgetRelation(MissWidgetFactoryBase* pBase, int nWidgetId);
    void GenerateWidget(const wxString& strGUID, int nWidgetId, const DTD::SWidgetPara& data);
    void GenerateWidget(MissWidgetFactoryBase* pBase, int nWidgetId, const DTD::SWidgetPara& data);
    void CloseRunWidget(unsigned int uRunId);

    void SendRunWidgetChanged();

private:
    MissWidgetManager();
    ~MissWidgetManager();
    MissWidgetManager(const MissWidgetManager&);
    MissWidgetManager& operator=(const MissWidgetManager&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_RUNNINGWIDGET_CHANGED, -1)
END_DECLARE_EVENT_TYPES()

#endif // MISSWIDGETMANAGER_H
