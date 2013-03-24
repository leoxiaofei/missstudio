#include "MissWidgetManager.h"

#include "MissAPI/plugin/MissWidgetFactoryBase.h"
#include "../Common/MissFuncFinder.hpp"
#include "../Common/IdCreater.hpp"
#include "../Impl/ImplMissWidget.h"
#include "MissPluginManager.h"

#include <wx/frame.h>
#include <iostream>
#include <algorithm>

using std::tr1::shared_ptr;
using std::vector;
using std::map;

class MissWidgetManager::Impl
{
public:
    Impl():icRunWidget(0){}
    vector<shared_ptr<WidgetRelation> >        vecWidgets;
    MissFuncFinder<MissWidgetFactoryBase>      funcFinder;
    vector<shared_ptr<ImplMissWidget> >        vecRunWidgets;
    map<unsigned int, MissWidgetFactoryBase*>  mapWidgetId;
    IdCreater<unsigned int>                    icRunWidget;
};

MissWidgetManager::MissWidgetManager()
: m_pImpl(new Impl)
{
    //ctor
}

MissWidgetManager::~MissWidgetManager()
{
    //dtor
}

bool MissWidgetManager::RegWidgetFactory(MissPluginBase* pPluginBase, 
    const WidgetMajorSet& vecWidgetMajor, MissWidgetFactoryBase* pFunc)
{
    m_pImpl->funcFinder.RegPluginFunc(pPluginBase, pFunc);
    m_pImpl->vecWidgets.push_back(
        shared_ptr<WidgetRelation>(new WidgetRelation(pFunc, vecWidgetMajor)));
    return true;
}

bool MissWidgetManager::UnRegWidgetFactory( MissWidgetFactoryBase* pFunc )
{
    m_pImpl->funcFinder.UnRegPluginFunc(pFunc);
    for (vector<shared_ptr<WidgetRelation> >::iterator itor = m_pImpl->vecWidgets.begin();
        itor != m_pImpl->vecWidgets.end(); ++itor)
    {
        if ((*itor)->pFactory == pFunc)
        {
            m_pImpl->vecWidgets.erase(itor);
            break;
        }
    }
    return true;
}

void MissWidgetManager::CreateWidget( const wxString& strGUID, int nWidgetId, const DTD::SWidgetPara& data )
{
    MissPluginBase* pPlugin;
    if(MissPluginManager::Instance().GetPluginByGuid(strGUID, pPlugin))
    {
        vector<MissWidgetFactoryBase*> vecFactory;
        m_pImpl->funcFinder.QueryFuncByPlugin(pPlugin, vecFactory);
        for (vector<MissWidgetFactoryBase*>::iterator itor = vecFactory.begin();
            itor != vecFactory.end(); ++itor)
        {
            if (CheckWidgetRelation(*itor, nWidgetId))
            {
                GenerateWidget(*itor, nWidgetId, data);
                break;
            }
        }
    }
}

void MissWidgetManager::GenerateWidget( MissWidgetFactoryBase* pBase, int nWidgetId, const DTD::SWidgetPara& data )
{
    MissWidgetFuncBase* pFunc = pBase->CreateWidgetFunc(nWidgetId);
    if (pFunc)
    {
        shared_ptr<ImplMissWidget> p(new ImplMissWidget(pFunc));
        p->SetData(data);
        p->SetRunID(m_pImpl->icRunWidget());
        p->SetWidgetID(nWidgetId);
        m_pImpl->vecRunWidgets.push_back(p);
        m_pImpl->mapWidgetId.insert(std::make_pair(p->GetRunID(), pBase));
        pBase->CreateSuccessed(pFunc);
        p->GetFrame()->Show();
    }
}

MissPluginBase* MissWidgetManager::GetPluginBase( MissWidgetFactoryBase* pBase ) const
{
    return m_pImpl->funcFinder.QueryPluginByFunc(pBase);
}

std::vector<shared_ptr<WidgetRelation> >& MissWidgetManager::GetWidgetData()
{
    return m_pImpl->vecWidgets;
}

std::vector<std::tr1::shared_ptr<ImplMissWidget> >& MissWidgetManager::GetRunningWidget()
{
    return m_pImpl->vecRunWidgets;
}

bool MissWidgetManager::CheckWidgetRelation( MissWidgetFactoryBase* pBase, int nWidgetId )
{
    bool bRet(false);
    for (vector<shared_ptr<WidgetRelation> >::size_type ix = 0; 
        ix != m_pImpl->vecWidgets.size(); ++ix)
    {
        if (m_pImpl->vecWidgets[ix]->pFactory == pBase)
        {
            bRet = std::find_if(m_pImpl->vecWidgets[ix]->vecWidgetMajor.begin(), 
                m_pImpl->vecWidgets[ix]->vecWidgetMajor.end(), FindWidgetMajor(nWidgetId))
                != m_pImpl->vecWidgets[ix]->vecWidgetMajor.end();
            break;
        }
    }
    return bRet;
}

bool MissWidgetManager::GetFactoryByRunId( unsigned int uId, MissWidgetFactoryBase*& pBase )
{
    bool bRet(false);
    map<unsigned int, MissWidgetFactoryBase*>::const_iterator iFind = m_pImpl->mapWidgetId.find(uId);
    if (iFind != m_pImpl->mapWidgetId.end())
    {
        pBase = iFind->second;
        bRet = true;
    }
    return bRet;
}

void MissWidgetManager::GetRunIdByFactory( MissWidgetFactoryBase* pBase, std::vector<unsigned int>& vecRunId )
{
    for (map<unsigned int, MissWidgetFactoryBase*>::const_iterator citor = m_pImpl->mapWidgetId.begin();
        citor != m_pImpl->mapWidgetId.end(); ++citor)
    {
        if (citor->second == pBase)
        {
            vecRunId.push_back(citor->first);
        }
    }
}

bool MissWidgetManager::UnloadPlugin( MissPluginBase* pPluginBase )
{
    std::vector<MissWidgetFactoryBase*> vecFunc;
    m_pImpl->funcFinder.QueryFuncByPlugin(pPluginBase, vecFunc);

    //////////////////////////////////////////////////////////////////////////
    ///关闭运行中的Widget
    std::vector<unsigned int> vecRunId;
    for (std::vector<MissWidgetFactoryBase*>::size_type ix = 0; ix != vecFunc.size(); ++ix)
    {
        GetRunIdByFactory(vecFunc[ix], vecRunId);
    }
    
    for (std::vector<unsigned int>::size_type ix = 0; ix != vecRunId.size(); ++ix)
    {
        for(vector<shared_ptr<ImplMissWidget> >::iterator itor = m_pImpl->vecRunWidgets.begin();
            itor != m_pImpl->vecRunWidgets.end(); ++itor)
        {
            if ((*itor)->GetRunID() == vecRunId[ix])
            {
                m_pImpl->vecRunWidgets.erase(itor);
                break;
            }
        }
        m_pImpl->mapWidgetId.erase(m_pImpl->mapWidgetId.find(vecRunId[ix]));
    }

    //////////////////////////////////////////////////////////////////////////
    ///关闭插件功能
    for (std::vector<MissWidgetFactoryBase*>::size_type ix = 0; ix != vecFunc.size(); ++ix)
    {
        UnRegWidgetFactory(vecFunc[ix]);
    }

    return true;
}

