#include "MissMemoryManager.h"

#include "..\Common\MissFuncFinder.hpp"
#include "MissAPI\plugin\MissSharedMemoryBase.h"

#include <unordered_map>
#include <set>
#include <vector>
#include <wx\hashmap.h>
#include <wx\variant.h>
#include <algorithm>


class MemoryData
{
public:
    wxVariant                        varData;
    std::set<const MissPluginBase*>  setPlugin;
};

typedef std::tr1::unordered_map<wxString, MemoryData, wxStringHash, wxStringEqual> HsMemory;
typedef std::tr1::unordered_map<wxString, std::vector<MissSharedMemoryBase*>, wxStringHash, wxStringEqual> HsCallBack;

class MissMemoryManager::Impl
{
public:
    HsMemory                              hsMemory;
    HsCallBack                            hsCallBack;
    MissFuncFinder<MissSharedMemoryBase>  funcFinder;
};

MissMemoryManager::MissMemoryManager()
: m_pImpl(new Impl)
{
}

MissMemoryManager::~MissMemoryManager()
{
}

bool MissMemoryManager::RegSharedMemory( MissPluginBase* pPluginBase, const wxString& strMemoryName, MissSharedMemoryBase* pFunc )
{
    bool bRet(true);
    m_pImpl->funcFinder.RegPluginFunc(pPluginBase, pFunc);
    m_pImpl->hsCallBack[strMemoryName].push_back(pFunc);
    return bRet;

}

bool MissMemoryManager::UnRegSharedMemory( const wxString& strMemoryName, MissSharedMemoryBase* pFunc )
{
    bool bRet(true);
    m_pImpl->funcFinder.UnRegPluginFunc(pFunc);
    HsCallBack::iterator iFind = m_pImpl->hsCallBack.find(strMemoryName);
    if (iFind != m_pImpl->hsCallBack.end())
    {
        iFind->second.erase(std::remove(iFind->second.begin(), iFind->second.end(), pFunc), iFind->second.end());
        if(iFind->second.empty())
        {
            m_pImpl->hsCallBack.erase(iFind);
        }
        bRet = true;
    }
    return bRet;

}

bool MissMemoryManager::GetVariant( const MissPluginBase* pPlugMain, const wxString& strMemoryName, wxVariant& varData )
{
    bool bRet(false);
    HsMemory::iterator iFind = m_pImpl->hsMemory.find(strMemoryName);
    if (iFind != m_pImpl->hsMemory.end())
    {
        varData = iFind->second.varData;
        iFind->second.setPlugin.insert(pPlugMain);
        bRet = true;
    }
    return bRet;
}

bool MissMemoryManager::SetVariant( const MissPluginBase* pPlugMain, const wxString& strMemoryName, const wxVariant& varData )
{
    bool bRet(false);
    MemoryData& data = m_pImpl->hsMemory[strMemoryName];
    data.varData = varData;
    data.setPlugin.insert(pPlugMain);
    NotifyChanged(strMemoryName, varData);
    return bRet;
}

void MissMemoryManager::NotifyChanged( const wxString& strMemoryName, const wxVariant& varData )
{
    HsCallBack::iterator iFind = m_pImpl->hsCallBack.find(strMemoryName);
    if (iFind != m_pImpl->hsCallBack.end())
    {
        for (std::vector<MissSharedMemoryBase*>::iterator itor = iFind->second.begin();
            itor != iFind->second.end(); ++itor)
        {
            (*itor)->MemoryChanged(varData);
        }
    }
}

bool MissMemoryManager::UnloadPlugin( MissPluginBase* pPluginBase )
{
    for(HsMemory::iterator itor = m_pImpl->hsMemory.begin();
        itor != m_pImpl->hsMemory.end(); )
    {
        itor->second.setPlugin.erase(pPluginBase);
        if (itor->second.setPlugin.empty())
        {
            itor = m_pImpl->hsMemory.erase(itor);
        }
        else
        {
            ++itor;
        }
    }

    std::vector<MissSharedMemoryBase*> vecFunc;
    m_pImpl->funcFinder.QueryFuncByPlugin(pPluginBase, vecFunc);
    m_pImpl->funcFinder.RemovePlugin(pPluginBase);

    for (std::vector<MissSharedMemoryBase*>::size_type ix = 0; ix != vecFunc.size(); ++ix)
    {
        for (HsCallBack::iterator itor = m_pImpl->hsCallBack.begin(); 
            itor != m_pImpl->hsCallBack.end(); ++itor)
        {
            itor->second.erase(std::remove(itor->second.begin(), itor->second.end(), vecFunc[ix]), itor->second.end());
            if(itor->second.empty())
            {
                m_pImpl->hsCallBack.erase(itor);
            }
        }
    }
    return true;
}

