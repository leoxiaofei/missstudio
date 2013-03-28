#include "MissTimerManager.h"
#include "MissAPI\plugin\MissTimerFuncBase.h"
#include "..\Common\MissFuncFinder.hpp"
#include <time.h>
#include <vector>
#include <algorithm>


class MissTimerManager::Impl
{
public:
    MissFuncFinder<MissTimerFuncBase>       funcFinder;

    std::vector<MissTimerFuncBase*>         vecSecUp;
    std::vector<MissTimerFuncBase*>         vecMinUp;
};


MissTimerManager::MissTimerManager()
: m_pImpl(new Impl)
{
}

MissTimerManager::~MissTimerManager()
{
}

bool MissTimerManager::RegTimer( MissPluginBase* pPluginBase, int nType, MissTimerFuncBase* pFunc )
{
    m_pImpl->funcFinder.RegPluginFunc(pPluginBase, pFunc);
    switch (nType)
    {
    case MTT_SEC:
        {
            std::vector<MissTimerFuncBase*>::iterator itor =
                std::find(m_pImpl->vecSecUp.begin(), m_pImpl->vecSecUp.end(), pFunc);
            if(itor == m_pImpl->vecSecUp.end())
            {
                m_pImpl->vecSecUp.push_back(pFunc);
            }
        }
        break;
    case MTT_MIN:
        {
            std::vector<MissTimerFuncBase*>::iterator itor =
                std::find(m_pImpl->vecMinUp.begin(), m_pImpl->vecMinUp.end(), pFunc);
            if(itor == m_pImpl->vecMinUp.end())
            {
                m_pImpl->vecMinUp.push_back(pFunc);
            }
        }
        break;
    default:
        break;
    }
    return true;
}

bool MissTimerManager::UnRegTimer( int nType, MissTimerFuncBase* pFunc )
{
    switch (nType)
    {
    case MTT_SEC:
        {
            std::vector<MissTimerFuncBase*>::iterator itor =
                std::find(m_pImpl->vecSecUp.begin(), m_pImpl->vecSecUp.end(), pFunc);
            if(itor != m_pImpl->vecSecUp.end())
            {
                m_pImpl->vecSecUp.erase(itor);
            }
        }
        break;
    case MTT_MIN:
        {
            std::vector<MissTimerFuncBase*>::iterator itor =
                std::find(m_pImpl->vecMinUp.begin(), m_pImpl->vecMinUp.end(), pFunc);
            if(itor != m_pImpl->vecMinUp.end())
            {
                m_pImpl->vecMinUp.erase(itor);
            }
        }
        break;
    default:
        break;
    }
    if (!FindTimerFunc(pFunc))
    {
        m_pImpl->funcFinder.UnRegPluginFunc(pFunc);
    }
    return true;
}

void MissTimerManager::TimeUp()
{
    static time_t  ttNow;
    static tm      *tmNow;
    ttNow = time(NULL);
    tmNow = localtime(&ttNow);
    static int s_savemin = tmNow->tm_min;

    ///秒钟定时器
    for(std::vector<MissTimerFuncBase*>::iterator itor = m_pImpl->vecSecUp.begin();
        itor != m_pImpl->vecSecUp.end(); ++itor)
    {
        (*itor)->TimeUp(tmNow);
    }

    ///分钟定时器
    if (s_savemin != tmNow->tm_min)
    {
        s_savemin = tmNow->tm_min;
        for(std::vector<MissTimerFuncBase*>::iterator itor = m_pImpl->vecMinUp.begin();
            itor != m_pImpl->vecMinUp.end(); ++itor)
        {
            (*itor)->TimeUp(tmNow);
        }
    }
}

bool MissTimerManager::FindTimerFunc( MissTimerFuncBase* pFunc ) const
{
    bool bRet(false);
    do 
    {
        std::vector<MissTimerFuncBase*>::iterator itor =
            std::find(m_pImpl->vecSecUp.begin(), m_pImpl->vecSecUp.end(), pFunc);
        if(itor != m_pImpl->vecSecUp.end())
        {
            bRet = true;
            break;
        }

        itor = std::find(m_pImpl->vecMinUp.begin(), m_pImpl->vecMinUp.end(), pFunc);
        if(itor != m_pImpl->vecMinUp.end())
        {
            bRet = true;
            break;
        }

    } while (0);

    return bRet;
}

bool MissTimerManager::UnloadPlugin( MissPluginBase* pPluginBase )
{
    std::vector<MissTimerFuncBase*> vecFunc;
    m_pImpl->funcFinder.QueryFuncByPlugin(pPluginBase, vecFunc);
    for (std::vector<MissTimerFuncBase*>::size_type ix = 0; ix != vecFunc.size(); ++ix)
    {
        UnRegTimer(MTT_SEC, vecFunc[ix]);
        UnRegTimer(MTT_MIN, vecFunc[ix]);
    }
    return true;
}
