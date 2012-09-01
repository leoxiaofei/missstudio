#ifndef IMPLMISSWIDGETMANAGER_H
#define IMPLMISSWIDGETMANAGER_H

#include "../../MissAPI/interface/IMissWidgetManager.h"

class MissPluginBase;

class ImplMissWidgetManager : public IMissWidgetManager
{
    public:
        ImplMissWidgetManager(MissPluginBase* pPlugMain);
        virtual ~ImplMissWidgetManager();

        void RegWidgetFactory(MissWidgetFactoryBase* pFactory,
            const std::vector<wxString>& vecWidget);

    protected:
    private:
        MissPluginBase* m_pPlugMain;
};

#endif // IMPLMISSWIDGETMANAGER_H
