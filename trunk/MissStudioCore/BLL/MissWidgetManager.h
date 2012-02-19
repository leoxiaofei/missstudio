#ifndef MISSWIDGETMANAGER_H
#define MISSWIDGETMANAGER_H

#include "../../MissAPI/interface/IMissWidget.h"

struct SWidget
{
    SWidget(MissWidgetFactoryBase* widget,const std::vector<wxString>& vecWidget):
        pFactory(widget),
        vecWidgetName(vecWidget){}
    MissWidgetFactoryBase* pFactory;
    std::vector<wxString> vecWidgetName;
};

class MissWidgetManager: public IMissWidget
{
    class MissWidgetManagerImpl;
    public:
        MissWidgetManager();
        virtual ~MissWidgetManager();

        //MissWidgetUpdateFunc* CreateWidget(MissWidgetFuncBase * pFunc);
        void CreateWidget(unsigned int nPlugin, unsigned int nWidget);

        std::vector<shared_ptr<SWidget> >& GetWidgetData();

    ///接口实现
        void RegPluginWidget(MissWidgetFactoryBase* pFactory, const std::vector<wxString>& vecWidget);

    protected:
    private:
        shared_ptr<MissWidgetManagerImpl> m_pImpl;
};

#endif // MISSWIDGETMANAGER_H
