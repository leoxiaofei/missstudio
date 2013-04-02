#include "MissHotKeyFunc.h"

#include "MissAPI/interface/IMissMain.h"
#include "MissAPI/interface/IMissStorage.h"
#include "MissAPI/interface/IMissHotKeyMgr.h"
#include "MissTools/MissConfigFile.h"
#include "../UI/MissEvtHandler.h"
#include "../Common/MissGlobal.h"

using std::tr1::shared_ptr;


MissHotKeyFunc::MissHotKeyFunc()
{
}


MissHotKeyFunc::~MissHotKeyFunc()
{
}

void MissHotKeyFunc::RunFunc( int nFuncId )
{
    switch(nFuncId)
    {
    case HKF_AUTOINPUT:
        {
            MissEvtHandler::Instance().OpenAutoInput();
        }
        break;
    default:
        assert(false);
        break;
    }
}

void MissHotKeyFunc::ModifiedHotKey( const SHotKeyMajor& sNewHotkey )
{
    assert(sNewHotkey.nFuncId > HKF_BEGIN && sNewHotkey.nFuncId < HKF_END);
	shared_ptr<IMissStorage> ptStorage = MissGlobal::IMain->QueryIF<IMissStorage>(IF_STORAGE);
    if (ptStorage)
    {
        shared_ptr<MissConfigFile> ptConfig = ptStorage->GetConfigFile(wxT("config.ini"));
        ptConfig->Write(s_strNodePath + s_strFuncNames[sNewHotkey.nFuncId] + wxT("/Enable"), sNewHotkey.bEnable);
        ptConfig->Write(s_strNodePath + s_strFuncNames[sNewHotkey.nFuncId] + wxT("/HotKey"), sNewHotkey.strHotKey);
    }
}

void MissHotKeyFunc::GetHotKeyName( int nFuncId, wxString& strFuncName )
{
    if (nFuncId > HKF_BEGIN && nFuncId < HKF_END)
    {
        strFuncName = s_strFuncNames[nFuncId];
    }
}

void MissHotKeyFunc::GetHotkeyDesc( int nFuncId, wxString& strFuncDesc )
{
    if (nFuncId > HKF_BEGIN && nFuncId < HKF_END)
    {
        strFuncDesc = s_strFuncDescs[nFuncId];
    }
}

void MissHotKeyFunc::InitHotkey( const std::tr1::shared_ptr<MissConfigFile>& pConfig )
{
    ///从文件读取热键数据
    HotKeyMajorSet setHotKeys(HKF_END);
    for (int ix = HKF_BEGIN + 1; ix < HKF_END; ++ix)
    {
        setHotKeys[ix].nFuncId = ix;
        if (pConfig)
        {
            if(!pConfig->Read(s_strNodePath + s_strFuncNames[ix] + wxT("/Enable"), setHotKeys[ix].bEnable))
            {
                setHotKeys[ix].bEnable = false;
            }
            if(!pConfig->Read(s_strNodePath + s_strFuncNames[ix] + wxT("/HotKey"), setHotKeys[ix].strHotKey))
            {
                setHotKeys[ix].strHotKey.Clear();
            }
        }
    }

    ///向框架注册热键
    shared_ptr<IMissHotKeyMgr> ptHotKey = MissGlobal::IMain->QueryIF<IMissHotKeyMgr>(IF_HOTKEY);
    if (ptHotKey)
    {
        ptHotKey->RegHotKeys(setHotKeys, this);
    }
}

const wxString MissHotKeyFunc::s_strFuncNames[] = {
    wxT("自动输入")
};

const wxString MissHotKeyFunc::s_strFuncDescs[] = {
    wxT("自动输入生成的密码到光标处。")
};

const wxString MissHotKeyFunc::s_strNodePath = wxT("热键/");