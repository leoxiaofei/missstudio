#ifndef MISSHOTKEYFUNC_H__
#define MISSHOTKEYFUNC_H__

#include "MissAPI\plugin\MissHotKeyFuncBase.h"

#include <wx/event.h>

#include <memory>

class MissConfigFile;

class MissHotKeyFunc : public MissHotKeyFuncBase
{
	class Impl;
public:
    MissHotKeyFunc();
    ~MissHotKeyFunc();

    void InitHotkey(const std::tr1::shared_ptr<MissConfigFile>& pConfig);

    virtual void GetHotKeyName( int nFuncId, wxString& strFuncName );
    virtual void GetHotkeyDesc( int nFuncId, wxString& strFuncDesc );

    virtual void RunFunc( int nFuncId );
    virtual void ModifiedHotKey( const SHotKeyMajor& sNewHotkey );

    enum FuncType{HKF_BEGIN = -1, HKF_SENDMSG, HKF_END};

	wxEvtHandler* GetHandle() const;

protected:
	void SendEvent(int nType);

protected:
	static const wxString s_strFuncNames[];
	static const wxString s_strFuncDescs[];
	static const wxString s_strNodePath;

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

wxDECLARE_EVENT(wxEVT_HOTKEYFUNC, wxCommandEvent);

#endif // MISSHOTKEYFUNC_H__

