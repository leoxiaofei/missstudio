#include "MissPluginMain.h"

#include <vector>

#include "MissAPI/interface/IMissMain.h"
#include "MissAPI/interface/IMissHotKeyMgr.h"
#include "MissAPI/interface/IMissStorage.h"
#include "../UI/MissAutoInputThread.h"
#include "MissHotKeyFunc.h"
#include "../Common/MissGlobal.h"

using std::tr1::shared_ptr;

class MissPluginMain::Impl
{
public:
    shared_ptr<MissHotKeyFunc> pHotKeyFunc;
};

MissPluginMain::MissPluginMain()
: MissPluginBase()
, m_pImpl(new Impl)
{
    //ctor
}

MissPluginMain::~MissPluginMain()
{
    //dtor
}

void MissPluginMain::LoadPlugin()
{
    MissGlobal::IMain = GetMain();
    shared_ptr<MissConfigFile> ptConfig;
    if (shared_ptr<IMissStorage> ptData = GetMain()->QueryIF<IMissStorage>(IF_STORAGE))
    {
        ptConfig = ptData->GetConfigFile(wxT("config.ini"));
    }
    ///加载热键功能
    m_pImpl->pHotKeyFunc = shared_ptr<MissHotKeyFunc>(new MissHotKeyFunc(GetMain()));
    m_pImpl->pHotKeyFunc->InitHotkey(ptConfig);
}

void MissPluginMain::UnloadPlugin()
{
}

bool MissPluginMain::GetPlugInfo( SPlugInfo& info ) const
{
    info.strPluginName = wxT("迷失密码助手");
    info.strVersion = wxT("1.0.0");
    info.strSpecification = wxT("用加密后的密码作为网站的密码，以便从容应对各网站密码泄露问题。");
    info.strAuthor = wxT("leoxiaofei");
    info.strEmail = wxT("xxffsoft@163.com");
    info.strWeb = wxT("http://www.leoxiaofei.com");
    return true;
}

wxString MissPluginMain::GetPluginName() const
{
    return wxT("迷失密码助手");
}

wxString MissPluginMain::GetPluginGUID() const
{
    return wxT("76C98BE0-4C3D-459A-9626-A6B2929EB367");
}
