#include "MissPluginMain.h"

#include <vector>
#include <tr1/memory>
#include "PasswordAidMain.h"
#include "MissAutoInputThread.h"
#include "../../MissAPI/interface/IMissMain.h"
#include "../../MissAPI/interface/IMissHotKey.h"
#include "../../MissAPI/interface/IMissConfig.h"


MissPluginMain::MissPluginMain(IMissMain* pParent):
MissPluginBase(pParent),
MissHotKeyFuncBase(this)
{
    //ctor
    SPlugInfo info;
    info.strPluginName = wxT("迷失密码助手");
    info.strVersion = wxT("1.0.0");
    info.strSpecification = wxT("用加密后的密码作为网站的密码，以便从容应对各网站密码泄露问题。");
    info.strAuthor = wxT("leoxiaofei");
    info.strEmail = wxT("xxffsoft@163.com");
    info.strWeb = wxT("http://www.leoxiaofei.com");
    SetPlugInfo(info);
}

MissPluginMain::~MissPluginMain()
{
    //dtor
}

void MissPluginMain::LoadPlugin(const wxString& strPath)
{
    MissPluginBase::LoadPlugin(strPath);
    std::vector<SHotKeyData> vecHotKey(2);
    std::tr1::shared_ptr<IMissConfig> config = GetMain()->GetConfig(this);
    //wxString strHotkey;
    vecHotKey[0].strFuncName = wxT("打开密码助手");
    vecHotKey[0].strFuncDesc = wxT("打开密码助手窗口，用来输入原文。");
    if(!config->Read(wxT("热键/打开窗口"),vecHotKey[0].strHotKey))
    {
        vecHotKey[0].strHotKey = wxT("Win+C");
    }

    vecHotKey[1].strFuncName = wxT("自动输入");
    vecHotKey[1].strFuncDesc = wxT("自动输入生成的密码到光标处");
    if(!config->Read(wxT("热键/自动输入"),vecHotKey[1].strHotKey))
    {
        vecHotKey[1].strHotKey = wxT("Win+V");
    }

    GetMain()->GetHotKey()->RegHotKeys(vecHotKey,this);
}

void MissPluginMain::RunFunc(int nFuncIndex)
{
    switch(nFuncIndex)
    {
    case 0:
        {
            PasswordAidDialog dlg(0L);
            dlg.ShowModal();
        }
        break;
    case 1:
        {
            MissAutoInputThread* m_pThread = new MissAutoInputThread();
            if ( m_pThread->Create() != wxTHREAD_NO_ERROR )
            {
                //wxLogError("Can't create the thread!");
                delete m_pThread;
                m_pThread = NULL;
            }
            else
            {
                if (m_pThread->Run() != wxTHREAD_NO_ERROR )
                {
                    //wxLogError("Can't create the thread!");
                    delete m_pThread;
                    m_pThread = NULL;
                }
            }
        }
        break;
    }
}

void MissPluginMain::ModifiedHotKey(int nFuncIndex, const wxString& strHotKey)
{
}
