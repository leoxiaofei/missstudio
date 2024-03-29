#include "MissMainEntry.h"
#include "ImplMissHotKeyMgr.h"
#include "ImplMissStorage.h"
#include "ImplMissTimer.h"
#include "ImplMissWidgetMgr.h"
#include "ImplMissSharedMemory.h"
#include "ImplMissClipboard.h"

#include "..\BLL\MissPluginManager.h"
#include "..\UI\MissCoreFrame.h"

#include <map>

typedef IMissUnknown* (MissMainEntry::*FuncCreator)();
typedef std::map<IF_TYPE, FuncCreator> IFCreater;
IFCreater s_InterfaceCreator;

MissMainEntry::MissMainEntry(MissPluginBase* pPlugMain)
: m_pPlugMain ( pPlugMain )
{
    if (s_InterfaceCreator.empty())
    {
        s_InterfaceCreator.insert(IFCreater::value_type(IF_HOTKEY,        &MissMainEntry::CreateInterface<ImplMissHotKeyMgr>));
        s_InterfaceCreator.insert(IFCreater::value_type(IF_STORAGE,       &MissMainEntry::CreateInterface<ImplMissStorage>));
        s_InterfaceCreator.insert(IFCreater::value_type(IF_TIMER,         &MissMainEntry::CreateInterface<ImplMissTimer>));
		s_InterfaceCreator.insert(IFCreater::value_type(IF_SHAREDMEMORY,  &MissMainEntry::CreateInterface<ImplMissSharedMemory>));
        s_InterfaceCreator.insert(IFCreater::value_type(IF_WIDGETMANAGER, &MissMainEntry::CreateInterface<ImplMissWidgetMgr>));
		s_InterfaceCreator.insert(IFCreater::value_type(IF_CLIPBOARD,     &MissMainEntry::CreateInterface<ImplMissClipboard>));
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
    IFCreater::iterator iFind = s_InterfaceCreator.find(eType);
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


