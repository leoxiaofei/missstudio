#ifndef MISSWIDGETFUNCMGR_H__
#define MISSWIDGETFUNCMGR_H__

#include <memory>

class MissWidgetFuncBase;
class MissTimerFuncBase;

class MissWidgetFuncMgr
{
    class Impl;
public:
    static MissWidgetFuncMgr& Instance()
    {
        static MissWidgetFuncMgr theSingleton;
        return theSingleton;
    }

    void SaveFunc(const std::tr1::shared_ptr<MissWidgetFuncBase>& pFunc,
        const std::tr1::shared_ptr<MissTimerFuncBase>& pRefreash);

private:
    MissWidgetFuncMgr();
    ~MissWidgetFuncMgr();
    MissWidgetFuncMgr(const MissWidgetFuncMgr&);
    MissWidgetFuncMgr& operator=(const MissWidgetFuncMgr&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};



#endif // MISSWIDGETFUNCMGR_H__
