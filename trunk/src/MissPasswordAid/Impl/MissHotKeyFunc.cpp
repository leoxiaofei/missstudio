#include "MissHotKeyFunc.h"

#include "MissAPI/interface/IMissMain.h"
#include "MissAPI/interface/IMissStorage.h"
#include "MissAPI/interface/IMissHotKeyMgr.h"
#include "MissTools/MissConfigFile.h"
#include "../UI/MissEvtHandler.h"

using std::tr1::shared_ptr;


MissHotKeyFunc::MissHotKeyFunc(const std::tr1::shared_ptr<IMissMain>& pMain)
: m_pMain(pMain)
{
}


MissHotKeyFunc::~MissHotKeyFunc(void)
{
}

void MissHotKeyFunc::RunFunc( int nFuncId )
{
    switch(nFuncId)
    {
    case HKF_OPENPANEL:
        {
            MissEvtHandler::Instance().OpenPasswordAid();
        }
        break;
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
    shared_ptr<IMissStorage> ptStorage = m_pMain->QueryIF<IMissStorage>(IF_STORAGE);
    if (ptStorage)
    {
        shared_ptr<MissConfigFile> ptConfig = ptStorage->GetConfigFile(wxT("config.ini"));
        ptConfig->Write(s_strNodePath + s_strFuncNames[sNewHotkey.nFuncId] + wxT("/Enable"), sNewHotkey.bEnable);
        ptConfig->Write(s_strNodePath + s_strFuncNames[sNewHotkey.nFuncId] + wxT("/HotKey"), sNewHotkey.strHotKey);
    }
    //std::tr1::shared_ptr<MissConfig> config = /*m_pMain->*/->GetConfigFile();
    //config->Write();

    //    std::tr1::shared_ptr<IMissConfig> config = GetMain()->GetConfig();
    //    config->Write(wxString::Format(m_pImpl->strFuncNames[nFuncIndex],nFuncIndex), strHotKey);
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
    ///���ļ���ȡ�ȼ�����
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

    ///����ע���ȼ�
    shared_ptr<IMissHotKeyMgr> ptHotKey = m_pMain->QueryIF<IMissHotKeyMgr>(IF_HOTKEY);
    if (ptHotKey)
    {
        ptHotKey->RegHotKeys(setHotKeys, this);
    }
}

const wxString MissHotKeyFunc::s_strFuncNames[] = {
    wxT("�򿪴���"),
    wxT("�Զ�����")
};

const wxString MissHotKeyFunc::s_strFuncDescs[] = {
    wxT("���������ִ��ڣ���������ԭ�ġ�"),
    wxT("�Զ��������ɵ����뵽��괦��")
};

const wxString MissHotKeyFunc::s_strNodePath = wxT("�ȼ�/");