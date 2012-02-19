#include "MissWidgetManager.h"

#include "../Widget/MissWidget.h"
#include "../../MissAPI/plugin/MissWidgetFactoryBase.h"

#include <iostream>

class MissWidgetManager::MissWidgetManagerImpl
{
public:
    std::vector<shared_ptr<MissWidget> > m_vecRunWidgets;
    std::vector<shared_ptr<SWidget> > m_vecWidgets;

};

MissWidgetManager::MissWidgetManager():
m_pImpl(new MissWidgetManagerImpl)
{
    //ctor
}

MissWidgetManager::~MissWidgetManager()
{
    //dtor
}
/*
MissWidgetUpdateFunc* MissWidgetManager::CreateWidget(MissWidgetFuncBase * pFunc)
{
    shared_ptr<MissWidget> p(new MissWidget(pFunc,0));
    m_pImpl->m_vecWidgets.push_back(p);

    //RegSecTimer(a.get());
    p->Show();
    return (MissWidgetUpdateFunc*)(MissTimerFuncBase*)p.get();
    //MissWidget a(0);
    //return new MissWidget(0);
}
*/
void MissWidgetManager::RegPluginWidget(MissWidgetFactoryBase* pFactory, const std::vector<wxString>& vecWidget)
{
    std::cout<<"RegPluginWidget:"<<vecWidget.size()<<std::endl;
    m_pImpl->m_vecWidgets.push_back(shared_ptr<SWidget>(new SWidget(pFactory, vecWidget)));
    //widget->CreateWidgetFunc();
}

std::vector<shared_ptr<SWidget> >& MissWidgetManager::GetWidgetData()
{
    return m_pImpl->m_vecWidgets;
}

void MissWidgetManager::CreateWidget(unsigned int nPlugin, unsigned int nWidget)
{
    if(nPlugin < m_pImpl->m_vecWidgets.size() &&
       nWidget < m_pImpl->m_vecWidgets[nPlugin]->vecWidgetName.size())
    {
        MissWidgetFuncBase* pFunc = m_pImpl->m_vecWidgets[nPlugin]
            ->pFactory->CreateWidgetFunc(nWidget);
        shared_ptr<MissWidget> p(new MissWidget(pFunc,0));
        p->Show();
        m_pImpl->m_vecWidgets[nPlugin]->pFactory->CreateSuccessed((MissWidgetUpdateFunc*)(MissTimerFuncBase*)p.get());
        m_pImpl->m_vecRunWidgets.push_back(p);
    }
}
