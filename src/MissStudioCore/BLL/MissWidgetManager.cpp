#include "MissWidgetManager.h"

#include "../Widget/MissWidget.h"
#include "MissAPI/plugin/MissWidgetFactoryBase.h"
#include "MissFuncFinder.h"

#include <iostream>
#include "MissPluginManager.h"

using std::tr1::shared_ptr;
using std::vector;

class MissWidgetManager::Impl
{
public:
    vector<shared_ptr<MissWidget> >        vecRunWidgets;
    vector<shared_ptr<WidgetRelation> >    vecWidgets;
    MissFuncFinder<MissWidgetFactoryBase>  funcFinder;

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

std::vector<shared_ptr<WidgetRelation> >& MissWidgetManager::GetWidgetData()
{
    return m_pImpl->vecWidgets;
}

//void MissWidgetManager::CreateWidget(unsigned int nPlugin, unsigned int nWidget, const DTD::SWidgetPara& data)
//{
//     if(nPlugin < m_pImpl->vecWidgets.size() &&
//             nWidget < m_pImpl->vecWidgets[nPlugin]->vecWidgetName.size())
//     {
//         MissWidgetFuncBase* pFunc = m_pImpl->m_vecWidgets[nPlugin]
//                                     ->pFactory->CreateWidgetFunc(nWidget);
//         shared_ptr<MissWidget> p(new MissWidget(pFunc,0));
//         p->SetData(data);
//         m_pImpl->m_vecRunWidgets.push_back(p);
//         m_pImpl->m_vecWidgets[nPlugin]->pFactory->CreateSuccessed((MissTimerFuncBase*)p.get());
//         p->Show();
//     }
//}

void MissWidgetManager::CreateWidget( unsigned int nPluginIndex, int nWidgetId, const DTD::SWidgetPara& data )
{

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
            GenerateWidget(*itor, nWidgetId, data);
        }
    }
    //Zm_pImpl->funcFinder.QueryFuncByPlugin()
}

void MissWidgetManager::GenerateWidget( MissWidgetFactoryBase* pBase, int nWidgetId, const DTD::SWidgetPara& data )
{
    MissWidgetFuncBase* pFunc = pBase->CreateWidgetFunc(nWidgetId);
    if (pFunc)
    {
        shared_ptr<MissWidget> p(new MissWidget(pFunc, 0));
        p->SetData(data);
        m_pImpl->vecRunWidgets.push_back(p);
        pBase->CreateSuccessed(pFunc);
        p->Show();
    }
}
