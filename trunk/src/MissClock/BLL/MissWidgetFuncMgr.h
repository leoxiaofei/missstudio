#ifndef MISSWIDGETFUNCMGR_H__
#define MISSWIDGETFUNCMGR_H__

#include <memory>

class MissClockWidgetFunc;

class MissWidgetFuncMgr
{
    class Impl;
public:
    static MissWidgetFuncMgr& Instance()
    {
        static MissWidgetFuncMgr theSingleton;
        return theSingleton;
    }

    void AddClockWidget(MissClockWidgetFunc* pClockFunc);

    void RemoveWidget(unsigned int uRunId);

private:
    MissWidgetFuncMgr();
    ~MissWidgetFuncMgr();
    MissWidgetFuncMgr(const MissWidgetFuncMgr&);
    MissWidgetFuncMgr& operator=(const MissWidgetFuncMgr&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};



#endif // MISSWIDGETFUNCMGR_H__
