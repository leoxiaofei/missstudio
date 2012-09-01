#ifndef MISSWIDGETMANAGER_H
#define MISSWIDGETMANAGER_H

struct SWidgetPara;
class MissWidgetFactoryBase;

struct SPluginWidgetData
{
    SPluginWidgetData(MissWidgetFactoryBase* widget,
                      const std::vector<wxString>& vecWidget)
    : pFactory(widget)
    , vecWidgetName(vecWidget){}

    MissWidgetFactoryBase* pFactory;
    std::vector<wxString> vecWidgetName;
};

class MissWidgetManager
{
    class MissWidgetManagerImpl;
    public:
        MissWidgetManager();
        virtual ~MissWidgetManager();

        //MissWidgetUpdateFunc* CreateWidget(MissWidgetFuncBase * pFunc);
        void CreateWidget(unsigned int nPlugin, unsigned int nWidget, const SWidgetPara& data);

        std::vector<shared_ptr<SPluginWidgetData> >& GetWidgetData();

        void RegWidgetFactory(MissWidgetFactoryBase* pFactory, const std::vector<wxString>& vecWidget);

    protected:
    private:
        shared_ptr<MissWidgetManagerImpl> m_pImpl;
};

#endif // MISSWIDGETMANAGER_H
