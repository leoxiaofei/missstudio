#include "MissMainEntry.h"
#include "ImplMissHotKeyMgr.h"
#include "ImplMissStorage.h"
#include "ImplMissTimer.h"
#include "ImplMissWidgetMgr.h"

#include <map>
#include "..\BLL\MissPluginManager.h"


typedef IMissUnknown* (MissMainEntry::*FuncCreator)(void);
std::map<IF_TYPE, FuncCreator> s_InterfaceCreator;

MissMainEntry::MissMainEntry(MissPluginBase* pPlugMain)
: m_pPlugMain ( pPlugMain )
{
    if (s_InterfaceCreator.empty())
    {
        s_InterfaceCreator.insert(std::make_pair(IF_HOTKEY, &MissMainEntry::CreateHotKey));
        s_InterfaceCreator.insert(std::make_pair(IF_STORAGE, &MissMainEntry::CreateStorage));
        s_InterfaceCreator.insert(std::make_pair(IF_TIMER, &MissMainEntry::CreateTimer));
        s_InterfaceCreator.insert(std::make_pair(IF_WIDGETMANAGER, &MissMainEntry::CreateWidgetMgr));
    }
}


MissMainEntry::~MissMainEntry(void)
{
}

void MissMainEntry::ExitApp()
{

}

std::tr1::shared_ptr<IMissUnknown> MissMainEntry::GetInterfacePtr( IF_TYPE eType )
{
    IMissUnknown* pRet(NULL);
    std::map<IF_TYPE, FuncCreator>::iterator iFind = s_InterfaceCreator.find(eType);
    if (iFind != s_InterfaceCreator.end())
    {
        pRet = (this->*(iFind->second))();
    }
    return std::tr1::shared_ptr<IMissUnknown>(pRet);
}

wxString MissMainEntry::GetPluginPath() const
{
    wxString strPath;
    MissPluginManager::Instance().GetPluginPath(m_pPlugMain, strPath);
    return strPath;
}

IMissUnknown* MissMainEntry::CreateHotKey()
{
    return new ImplMissHotKeyMgr(m_pPlugMain);
}

IMissUnknown* MissMainEntry::CreateStorage()
{
    return new ImplMissStorage(m_pPlugMain);
}

IMissUnknown* MissMainEntry::CreateTimer()
{
    return new ImplMissTimer(m_pPlugMain);
}

IMissUnknown* MissMainEntry::CreateWidgetMgr()
{
    return new ImplMissWidgetMgr(m_pPlugMain);
}



