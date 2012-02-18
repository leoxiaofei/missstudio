#include "MissWidgetManager.h"

#include "../Widget/MissWidget.h"

class MissWidgetManager::MissWidgetManagerImpl
{
public:
    std::vector<shared_ptr<MissWidget> > m_vecWidgets;
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

