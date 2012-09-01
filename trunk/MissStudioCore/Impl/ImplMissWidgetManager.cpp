#include "ImplMissWidgetManager.h"

#include "../BLL/MissWidgetManager.h"
#include "../BLL/MissPluginManager.h"

ImplMissWidgetManager::ImplMissWidgetManager(MissPluginBase* pPlugMain)
: m_pPlugMain(pPlugMain)
{
    //ctor
}

ImplMissWidgetManager::~ImplMissWidgetManager()
{
    //dtor
}

void ImplMissWidgetManager::RegWidgetFactory(MissWidgetFactoryBase* pFactory,
    const std::vector<wxString>& vecWidget)
{
    MissPluginManager::Instance().RegPluginInterface(m_pPlugMain, pFactory);
    MissPluginManager::Instance().GetWidgetManager().
        RegWidgetFactory(pFactory, vecWidget);
}
