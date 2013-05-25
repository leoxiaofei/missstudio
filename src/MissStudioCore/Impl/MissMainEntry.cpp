#include "MissMainEntry.h"
#include "ImplMissHotKeyMgr.h"
#include "ImplMissStorage.h"
#include "ImplMissTimer.h"
#include "ImplMissWidgetMgr.h"
#include "ImplMissSharedMemory.h"
#include "ImplMissClipboard.h"
#include "ImplMissNetwork.h"

#include "..\BLL\MissPluginManager.h"
#include "..\UI\MissCoreFrame.h"

#include <map>

typedef IMissUnknown* (MissMainEntry::*FuncCreator)(void);
std::map<IF_TYPE, FuncCreator> s_InterfaceCreator;

MissMainEntry::MissMainEntry(MissPluginBase* pPlugMain)
: m_pPlugMain ( pPlugMain )
{
    if (s_InterfaceCreator.empty())
    {
        s_InterfaceCreator.insert(std::make_pair(IF_HOTKEY, &MissMainEntry::CreateInterface<ImplMissHotKeyMgr>));
        s_InterfaceCreator.insert(std::make_pair(IF_STORAGE, &MissMainEntry::CreateInterface<ImplMissStorage>));
        s_InterfaceCreator.insert(std::make_pair(IF_TIMER, &MissMainEntry::CreateInterface<ImplMissTimer>));
		s_InterfaceCreator.insert(std::make_pair(IF_SHAREDMEMORY, &MissMainEntry::CreateInterface<ImplMissSharedMemory>));
        s_InterfaceCreator.insert(std::make_pair(IF_WIDGETMANAGER, &MissMainEntry::CreateInterface<ImplMissWidgetMgr>));
		s_InterfaceCreator.insert(std::make_pair(IF_CLIPBOARD, &MissMainEntry::CreateInterface<ImplMissClipboard>));
		s_InterfaceCreator.insert(std::make_pair(IF_NETWORK, &MissMainEntry::CreateInterface<ImplMissNetwork>));
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

wxFrame* MissMainEntry::GetMainFrame() const
{
    return wxAppFrame;
}

