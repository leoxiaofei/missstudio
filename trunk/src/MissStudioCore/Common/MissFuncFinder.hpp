#ifndef MISSFUNCFINDER_H__
#define MISSFUNCFINDER_H__

#include <map>
#include <vector>

template <class T>
class MissFuncFinder
{
private:
    std::map<T*, MissPluginBase*> m_mapPluginQuery;

public:
    MissFuncFinder(){};

    ~MissFuncFinder(){};

    typedef std::map<T*, MissPluginBase*> FuncContainer;

    void RegPluginFunc(MissPluginBase* pPlugin, T* pFunc)
    {
        m_mapPluginQuery[pFunc] = pPlugin;
    }

    void UnRegPluginFunc(T* pFunc)
    {
        FuncContainer::iterator iFind = m_mapPluginQuery.find(pFunc);
        if( iFind != m_mapPluginQuery.end() )
        {
            m_mapPluginQuery.erase(iFind);
        }
    }

    MissPluginBase* QueryPluginByFunc(T* pFunc)
    {
        MissPluginBase* pRet(NULL);
        FuncContainer::iterator iFind = m_mapPluginQuery.find(pFunc);
        if( iFind != m_mapPluginQuery.end() )
        {
            pRet = iFind->second;
        }
        return pRet;
    }

    void QueryFuncByPlugin(MissPluginBase* pPlugin, std::vector<T*>& vecFunc)
    {
        for (FuncContainer::iterator itor = m_mapPluginQuery.begin();
            itor != m_mapPluginQuery.end(); ++itor)
        {
            if (itor->second == pPlugin)
            {
                vecFunc.push_back(itor->first);
            }
        }
    }

    void RemovePlugin(MissPluginBase* pPlugin)
    {
        for (FuncContainer::iterator itor = m_mapPluginQuery.begin();
            itor != m_mapPluginQuery.end(); )
        {
            if (itor->second == pPlugin)
            {
                itor = m_mapPluginQuery.erase(itor);
            }
            else
            {
                ++itor;
            }
        }
    }
};



#endif // MISSFUNCFINDER_H__
