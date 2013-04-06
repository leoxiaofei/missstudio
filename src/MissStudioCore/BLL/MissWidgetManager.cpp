#include "MissWidgetManager.h"

#include "MissAPI/plugin/MissWidgetFactoryBase.h"
#include "../Common/MissFuncFinder.hpp"
#include "../Impl/ImplMissWidget.h"
#include "MissPluginManager.h"

#include <wx/frame.h>
#include <iostream>
#include <algorithm>
#include "../DAL/MissWidgetsDAL.h"
#include "MissAPI/plugin/MissPluginBase.h"
#include "../Common/WidgetEvent.h"

using std::tr1::shared_ptr;
using std::vector;
using std::map;


class FindImplMissWidget
{
public:
    FindImplMissWidget(unsigned int uRunId)
    : m_uRunId(uRunId)
    {}

    bool operator()(const shared_ptr<ImplMissWidget>& ptWidget) const
    {
        return ptWidget->GetRunID() == m_uRunId;
    }

private:
    unsigned int m_uRunId;
};

class MissWidgetManager::Impl
{
public:
    Impl(){}
    vector<shared_ptr<WidgetRelation> >        vecWidgets;
    MissFuncFinder<MissWidgetFactoryBase>      funcFinder;
    vector<shared_ptr<ImplMissWidget> >        vecRunWidgets;
    map<unsigned int, MissWidgetFactoryBase*>  mapWidgetId;
    wxEvtHandler                               hHandler;
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

void MissWidgetManager::GenerateWidget( const wxString& strGUID, int nWidgetId, const DTD::SWidgetPara& data )
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
        p->SetWidgetID(nWidgetId);
        m_pImpl->vecRunWidgets.push_back(p);
        m_pImpl->mapWidgetId.insert(std::make_pair(p->GetRunID(), pBase));
        pBase->CreateSuccessed(pFunc);
        p->GetFrame()->Show();
        p->UpdateUI();
        SendRunWidgetChanged();
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
        CloseRunWidget(vecRunId[ix]);
    }

    //////////////////////////////////////////////////////////////////////////
    ///关闭插件功能
    for (std::vector<MissWidgetFactoryBase*>::size_type ix = 0; ix != vecFunc.size(); ++ix)
    {
        UnRegWidgetFactory(vecFunc[ix]);
    }

    return true;
}

void MissWidgetManager::LoadRunWidget()
{
    std::vector<RunWidgetData> vecRunDatas;
    MissWidgetsDAL::Instance().LoadRunWidgets(vecRunDatas);
    for (std::vector<RunWidgetData>::const_iterator citor = vecRunDatas.begin();
        citor != vecRunDatas.end(); ++citor)
    {
        GenerateWidget(citor->strGuid, citor->nWidgetId, citor->sWidgetPara);
    }
}

void MissWidgetManager::SaveRunWidget()
{
    std::vector<RunWidgetData> vecRunDatas(m_pImpl->vecRunWidgets.size());
    for (vector<shared_ptr<ImplMissWidget> >::size_type ix = 0;
        ix != m_pImpl->vecRunWidgets.size(); ++ix)
    {
        MissWidgetFactoryBase* pBase(NULL);
        if(GetFactoryByRunId(m_pImpl->vecRunWidgets[ix]->GetRunID(), pBase))
        {
            vecRunDatas[ix].strGuid = GetPluginBase(pBase)->GetPluginGUID();
            vecRunDatas[ix].nWidgetId = m_pImpl->vecRunWidgets[ix]->GetWidgetID();
            m_pImpl->vecRunWidgets[ix]->GetData(vecRunDatas[ix].sWidgetPara);
        }
    }
    MissWidgetsDAL::Instance().SaveRunWidgets(vecRunDatas);
}

void MissWidgetManager::CreateWidget( MissWidgetFactoryBase* pBase, int nWidgetId )
{
    MissPluginBase* pPlugin = GetPluginBase(pBase);
    if (pPlugin)
    {
        DTD::SWidgetPara data;
        MissWidgetsDAL::Instance().NewRunWidget(pPlugin->GetPluginGUID(), nWidgetId, data);
        GenerateWidget(pBase, nWidgetId, data);
    }
}

void MissWidgetManager::DelRunWidget( unsigned int uRunId )
{
    CloseRunWidget(uRunId);
    MissWidgetsDAL::Instance().DelRunWidget(uRunId);
}

void MissWidgetManager::CloseRunWidget( unsigned int uRunId )
{
    vector<shared_ptr<ImplMissWidget> >::iterator iFind = 
        std::find_if(m_pImpl->vecRunWidgets.begin(), m_pImpl->vecRunWidgets.end(), 
        FindImplMissWidget(uRunId));
    (*iFind)->PreClose();
    m_pImpl->vecRunWidgets.erase(iFind);
    m_pImpl->mapWidgetId.erase(m_pImpl->mapWidgetId.find(uRunId));

    SendRunWidgetChanged();
}

wxEvtHandler* MissWidgetManager::GetHandle() const
{
    return &m_pImpl->hHandler;
}

void MissWidgetManager::SendRunWidgetChanged()
{
    ///发送一个数据改变消息
    wxCommandEvent send(wxEVT_RUNNINGWIDGET_CHANGED);
    m_pImpl->hHandler.AddPendingEvent(send);
}

