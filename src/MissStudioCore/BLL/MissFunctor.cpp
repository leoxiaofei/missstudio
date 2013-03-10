#include "MissFunctor.h"
#include "MissHotKeyManager.h"

void PluginUnloader::operator()( MissPluginBase* pPluginBase ) const
{
    MissHotKeyManager::Instance().UnloadPlugin(pPluginBase);

}

