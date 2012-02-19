#ifndef IMISSWIDGET_H
#define IMISSWIDGET_H

//class MissWidgetFuncBase;
//class MissTimerFuncBase;
//typedef MissTimerFuncBase MissWidgetUpdateFunc;
class MissWidgetFactoryBase;

class IMissWidget
{
    public:
        virtual ~IMissWidget() {}
        //virtual MissWidgetUpdateFunc* CreateWidget(MissWidgetFuncBase * pFunc) = 0;
        virtual void RegPluginWidget(MissWidgetFactoryBase* pFactory, const std::vector<wxString>& vecWidget) = 0;
    protected:
    private:
};

#endif // IMISSWIDGET_H
