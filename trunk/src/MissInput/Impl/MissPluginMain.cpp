#include "MissPluginMain.h"

#include <vector>

#include "MissAPI/interface/IMissMain.h"
#include "MissAPI/interface/IMissHotKeyMgr.h"
#include "MissAPI/interface/IMissStorage.h"
#include "MissAPI/interface/IMissClipboard.h"
#include "../UI/MissAutoInputThread.h"
#include "../UI/MissEvtHandler.h"
#include "../Common/MissGlobal.h"

#include "MissHotKeyFunc.h"

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
    m_pImpl->pHotKeyFunc = shared_ptr<MissHotKeyFunc>(new MissHotKeyFunc());
    m_pImpl->pHotKeyFunc->InitHotkey(ptConfig);

	std::tr1::shared_ptr<IMissClipboard> pt = GetMain()->QueryIF<IMissClipboard>(IF_CLIPBOARD);
	pt->RegNotify(&MissEvtHandler::ClipboardChanged, &MissEvtHandler::Instance());
}

void MissPluginMain::UnloadPlugin()
{
}

bool MissPluginMain::GetPlugInfo( SPlugInfo& info ) const
{
    info.strPluginName = wxT("迷失输入助手");
    info.strVersion = wxT("1.0.0");
    info.strSpecification = wxT("方便输入序列号的小工具");
    info.strAuthor = wxT("leoxiaofei");
    info.strEmail = wxT("xxffsoft@163.com");
    info.strWeb = wxT("http://www.leoxiaofei.com");
    return true;
}

wxString MissPluginMain::GetPluginName() const
{
    return wxT("迷失输入助手");
}

wxString MissPluginMain::GetPluginGUID() const
{
    return wxT("4AFFE234-4A38-4d88-80C8-5353C3141583");
}
