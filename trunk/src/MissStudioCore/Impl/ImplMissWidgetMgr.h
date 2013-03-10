#ifndef IMPLMISSWIDGETMANAGER_H
#define IMPLMISSWIDGETMANAGER_H

#include "MissAPI/interface/IMissWidgetMgr.h"

class MissPluginBase;

class ImplMissWidgetMgr : public IMissWidgetMgr
{
    public:
        ImplMissWidgetMgr(MissPluginBase* pPlugMain);
        virtual ~ImplMissWidgetMgr();

        virtual bool RegWidgetFactory( MissWidgetFactoryBase* pFactory, 
            const WidgetMajorSet& vecWidget );

    protected:
    private:
        MissPluginBase* m_pPlugMain;
};

#endif // IMPLMISSWIDGETMANAGER_H
