#include "ImplMissTimer.h"
#include "..\BLL\MissTimerManager.h"
#include "MissAPI\plugin\MissTimerFuncBase.h"

ImplMissTimer::ImplMissTimer( MissPluginBase* pPlugMain )
: m_pPlugMain(pPlugMain)
{

}

ImplMissTimer::~ImplMissTimer()
{

}

void ImplMissTimer::RegSecTimer( MissTimerFuncBase* pPlugin )
{
    MissTimerManager::Instance().RegTimer(m_pPlugMain, MTT_SEC, pPlugin);
}

void ImplMissTimer::RegMinTimer( MissTimerFuncBase* pPlugin )
{
    MissTimerManager::Instance().RegTimer(m_pPlugMain, MTT_MIN, pPlugin);
}

void ImplMissTimer::UnRegSecTimer( MissTimerFuncBase* pPlugin )
{
    MissTimerManager::Instance().UnRegTimer(MTT_SEC, pPlugin);
}

void ImplMissTimer::UnRegMinTimer( MissTimerFuncBase* pPlugin )
{
    MissTimerManager::Instance().UnRegTimer(MTT_MIN, pPlugin);
}


