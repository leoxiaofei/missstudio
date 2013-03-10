#include "ImplMissWidgetMgr.h"

#include "../BLL/MissWidgetManager.h"
#include "../BLL/MissPluginManager.h"

ImplMissWidgetMgr::ImplMissWidgetMgr(MissPluginBase* pPlugMain)
: m_pPlugMain(pPlugMain)
{
    //ctor
}

ImplMissWidgetMgr::~ImplMissWidgetMgr()
{
    //dtor
}

bool ImplMissWidgetMgr::RegWidgetFactory( MissWidgetFactoryBase* pFactory, const WidgetMajorSet& vecWidget )
{
    return MissWidgetManager::Instance().RegWidgetFactory(m_pPlugMain, vecWidget, pFactory);
}
