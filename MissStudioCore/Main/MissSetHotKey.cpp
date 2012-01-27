#include "MissSetHotKey.h"

MissSetHotKey::MissSetHotKey(const wxString& strHotKey, wxWindow* parent )
:
SetHotKeyBase( parent )
{
    m_kedtHotKey->SetValue(strHotKey);
}

void MissSetHotKey::GetHotKeyString(wxString& strHotKey)
{
    strHotKey = m_kedtHotKey->GetValue();
}
