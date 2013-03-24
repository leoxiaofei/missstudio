#include "MissFunctor.h"
#include "MissHotKeyManager.h"
#include "MissTimerManager.h"
#include "MissWidgetManager.h"

void PluginUnloader::operator()( MissPluginBase* pPluginBase ) const
{
    MissHotKeyManager::Instance().UnloadPlugin(pPluginBase);
    MissTimerManager::Instance().UnloadPlugin(pPluginBase);
    MissWidgetManager::Instance().UnloadPlugin(pPluginBase);
}

