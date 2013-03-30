#include "MissWidgetFuncMgr.h"
#include <map>
#include "..\Common\MissGlobal.h"
#include "MissAPI\interface\IMissTimer.h"
#include "..\Impl\MissWidgetRefresh.hpp"
#include "..\Impl\MissClockWidgetFunc.h"

using std::map;
using std::pair;
using std::tr1::shared_ptr;

class RunWidgetFunc
{
public:
    RunWidgetFunc(MissWidgetFuncBase* pFunc, MissTimerFuncBase* pRefreash)
    : ptWidgetFunc(pFunc)
    , ptTimerFunc(pRefreash){}

    shared_ptr<MissWidgetFuncBase>   ptWidgetFunc;
    shared_ptr<MissTimerFuncBase>    ptTimerFunc;
};

class MissWidgetFuncMgr::Impl
{
public:
    std::map<unsigned int, RunWidgetFunc> mapRunData;


};

MissWidgetFuncMgr::MissWidgetFuncMgr()
: m_pImpl(new Impl)
{
}

MissWidgetFuncMgr::~MissWidgetFuncMgr()
{
}

void MissWidgetFuncMgr::AddClockWidget( MissClockWidgetFunc* pClockFunc )
{
    MissTimerFuncBase* pRefreash = new MissWidgetRefreash<MissClockWidgetFunc>(pClockFunc);
    m_pImpl->mapRunData.insert( std::map<unsigned int, RunWidgetFunc>::value_type(
        pClockFunc->GetRunID(), RunWidgetFunc(pClockFunc, pRefreash) ));

    if (shared_ptr<IMissTimer> pt = MissGlobal::IMain->QueryIF<IMissTimer>(IF_TIMER))
    {
        pt->RegSecTimer(pRefreash);
    }
}

void MissWidgetFuncMgr::RemoveWidget( unsigned int uRunId )
{
    std::map<unsigned int, RunWidgetFunc>::iterator iFind = m_pImpl->mapRunData.find(uRunId);
    if (iFind != m_pImpl->mapRunData.end())
    {
        if (shared_ptr<IMissTimer> pt = MissGlobal::IMain->QueryIF<IMissTimer>(IF_TIMER))
        {
            pt->UnRegSecTimer(iFind->second.ptTimerFunc.get());
        }
        m_pImpl->mapRunData.erase(iFind);
    }
}
