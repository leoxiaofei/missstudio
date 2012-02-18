#ifndef IMISSWIDGET_H
#define IMISSWIDGET_H

class MissWidgetFuncBase;
class MissTimerFuncBase;
typedef MissTimerFuncBase MissWidgetUpdateFunc;

class IMissWidget
{
    public:
        virtual ~IMissWidget() {}
        virtual MissWidgetUpdateFunc* CreateWidget(MissWidgetFuncBase * pFunc) = 0;

    protected:
    private:
};

#endif // IMISSWIDGET_H
