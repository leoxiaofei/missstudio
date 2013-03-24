#ifndef MISSWIDGETMANAGER_H
#define MISSWIDGETMANAGER_H

#include "MissAPI\interface\IMissWidgetMgr.h"
#include <memory>

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

    //MissWidgetUpdateFunc* CreateWidget(MissWidgetFuncBase * pFunc);
    MissPluginBase* GetPluginBase(MissWidgetFactoryBase* pBase) const;

    void CreateWidget(const wxString& strGUID, int nWidgetId, const DTD::SWidgetPara& data);
    void GenerateWidget(MissWidgetFactoryBase* pBase, int nWidgetId, const DTD::SWidgetPara& data);

    std::vector<std::tr1::shared_ptr<WidgetRelation> >& GetWidgetData();
    std::vector<std::tr1::shared_ptr<ImplMissWidget> >& GetRunningWidget();

    bool RegWidgetFactory(MissPluginBase* pPluginBase, const WidgetMajorSet& vecWidgetMajor, MissWidgetFactoryBase* pFunc);
    bool UnRegWidgetFactory(MissWidgetFactoryBase* pFunc);

    bool GetFactoryByRunId(unsigned int uId, MissWidgetFactoryBase*& pBase);
    void GetRunIdByFactory(MissWidgetFactoryBase* pBase, std::vector<unsigned int>& vecRunId);

protected:
    bool CheckWidgetRelation(MissWidgetFactoryBase* pBase, int nWidgetId);

private:
    MissWidgetManager();
    ~MissWidgetManager();
    MissWidgetManager(const MissWidgetManager&);
    MissWidgetManager& operator=(const MissWidgetManager&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSWIDGETMANAGER_H
