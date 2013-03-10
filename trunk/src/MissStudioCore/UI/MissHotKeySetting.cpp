#include "MissHotKeySetting.h"
#include "../Widget/wxKeyMonitorTextCtrl.h"

MissHotKeySetting::MissHotKeySetting(const wxString& strHotKey, wxWindow* parent )
: HotKeySettingBase( parent )
{
    BindEvent();
    kedtHotKey->SetValue(strHotKey);
}

MissHotKeySetting::~MissHotKeySetting()
{
    UnbindEvent();
}

void MissHotKeySetting::BindEvent()
{
    btnClear->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &MissHotKeySetting::OnBtnClearClick, this );
}

void MissHotKeySetting::UnbindEvent()
{
    btnClear->Unbind( wxEVT_COMMAND_BUTTON_CLICKED, &MissHotKeySetting::OnBtnClearClick, this );
}

void MissHotKeySetting::OnBtnClearClick( wxCommandEvent& event )
{
    // TODO: 清空
    kedtHotKey->Clear();
}

void MissHotKeySetting::GetHotKeyString( wxString& strHotKey )
{
    strHotKey = kedtHotKey->GetValue();
}

