#include "ImplMissMain.h"

#include "../Main/MissStudioCoreMain.h"
#include "../../MissTools/MissConfigFile.h"
#include "../../MissAPI/plugin/MissPluginBase.h"
#include "../BLL/MissPluginManager.h"
#include "ImplMissTaskIcon.h"
#include "ImplMissHotKey.h"
#include "ImplMissWidgetManager.h"

#include <wx/wxsqlite3.h>

ImplMissMain::ImplMissMain(MissStudioCoreFrame* pCore, MissPluginBase* pPlugMain)
: m_pCore(pCore)
, m_pPlugMain(pPlugMain)
{
    //ctor
}

ImplMissMain::~ImplMissMain()
{
    //dtor
}

void ImplMissMain::ExitApp()
{
}

void ImplMissMain::RegSecTimer(MissTimerFuncBase* pPlugin)
{
    m_pCore->RegSecTimer(pPlugin);
}

void ImplMissMain::RegMinTimer(MissTimerFuncBase* pPlugin)
{
    m_pCore->RegMinTimer(pPlugin);
}

std::tr1::shared_ptr<IMissTaskIcon> ImplMissMain::GetTaskIcon()
{
    std::tr1::shared_ptr<IMissTaskIcon> Icon(
        new ImplMissTaskIcon(m_pCore->GetTaskIcon(), m_pPlugMain));
    return Icon;
}

std::tr1::shared_ptr<IMissHotKey> ImplMissMain::GetHotKey()
{
    std::tr1::shared_ptr<IMissHotKey> hotkey(new ImplMissHotKey(m_pPlugMain));
    return hotkey;
}

std::tr1::shared_ptr<IMissWidgetManager> ImplMissMain::GetWidgetManager()
{
    std::tr1::shared_ptr<IMissWidgetManager> manager(
        new ImplMissWidgetManager(m_pPlugMain));
    return manager;
}

std::tr1::shared_ptr<IMissConfig> ImplMissMain::GetConfig()
{
    std::tr1::shared_ptr<IMissConfig> conf(new MissConfigFile(wxT("config\\")
                        + m_pPlugMain->GetPlugInfo().strPluginName +wxT(".ini")));
    return conf;
}

std::tr1::shared_ptr<wxSQLite3Database> ImplMissMain::GetDataBase()
{
    std::tr1::shared_ptr<wxSQLite3Database> db(new wxSQLite3Database);
    db->Open(wxT("database\\") + m_pPlugMain->GetPlugInfo().strPluginName + wxT(".db3"));
    return db;
}

wxString ImplMissMain::GetPluginPath()
{
    wxString strPath;
    MissPluginManager::Instance().FindPluginPath(m_pPlugMain, strPath);
    return strPath;
}
