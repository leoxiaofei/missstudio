#ifndef MISSWIDGETMANAGER_H
#define MISSWIDGETMANAGER_H

#include "../../MissAPI/interface/IMissWidget.h"

class MissWidgetManager: public IMissWidget
{
    class MissWidgetManagerImpl;
    public:
        MissWidgetManager();
        virtual ~MissWidgetManager();

        MissWidgetUpdateFunc* CreateWidget(MissWidgetFuncBase * pFunc);

    protected:
    private:
        shared_ptr<MissWidgetManagerImpl> m_pImpl;
};

#endif // MISSWIDGETMANAGER_H
