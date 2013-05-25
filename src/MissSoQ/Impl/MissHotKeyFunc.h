#ifndef MISSHOTKEYFUNC_H__
#define MISSHOTKEYFUNC_H__

#include "MissAPI\plugin\MissHotKeyFuncBase.h"

#include <memory>

class MissConfigFile;

class MissHotKeyFunc : public MissHotKeyFuncBase
{
public:
    MissHotKeyFunc();
    ~MissHotKeyFunc();

    void InitHotkey(const std::tr1::shared_ptr<MissConfigFile>& pConfig);

    virtual void GetHotKeyName( int nFuncId, wxString& strFuncName );
    virtual void GetHotkeyDesc( int nFuncId, wxString& strFuncDesc );

    virtual void RunFunc( int nFuncId );
    virtual void ModifiedHotKey( const SHotKeyMajor& sNewHotkey );

    enum FuncType{HKF_BEGIN = -1, HKF_SENDMSG, HKF_END};

protected:
	static const wxString s_strFuncNames[];
	static const wxString s_strFuncDescs[];
	static const wxString s_strNodePath;

private:
};

#endif // MISSHOTKEYFUNC_H__

