#ifndef MISSCREATEWIDGETBASE_H
#define MISSCREATEWIDGETBASE_H

class MissWidgetFuncBase;
class MissTimerFuncBase;
typedef MissTimerFuncBase MissWidgetUpdateFunc;

class MissWidgetFactoryBase
{
    public:
        MissWidgetFactoryBase(){};
        virtual ~MissWidgetFactoryBase() {}
        virtual MissWidgetFuncBase* CreateWidgetFunc(unsigned int nIndex) = 0;
        virtual void CreateSuccessed(MissWidgetUpdateFunc* pUpdate) = 0;
    protected:
    private:
};

#endif // MISSCREATEWIDGETBASE_H
