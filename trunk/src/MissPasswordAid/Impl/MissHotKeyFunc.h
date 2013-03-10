#ifndef MISSHOTKEYFUNC_H__
#define MISSHOTKEYFUNC_H__

#include "MissAPI\plugin\MissHotKeyFuncBase.h"

#include <memory>
class IMissMain;
class MissConfigFile;

class MissHotKeyFunc : public MissHotKeyFuncBase
{
public:
    MissHotKeyFunc(const std::tr1::shared_ptr<IMissMain>& pMain);
    ~MissHotKeyFunc(void);

    void InitHotkey(const std::tr1::shared_ptr<MissConfigFile>& pConfig);

    virtual void GetHotKeyName( int nFuncId, wxString& strFuncName );
    virtual void GetHotkeyDesc( int nFuncId, wxString& strFuncDesc );

    virtual void RunFunc( int nFuncId );
    virtual void ModifiedHotKey( const SHotKeyMajor& sNewHotkey );

    enum FuncType{HKF_BEGIN = -1, HKF_OPENPANEL, HKF_AUTOINPUT, HKF_END};
    static const wxString s_strFuncNames[];
    static const wxString s_strFuncDescs[];
    static const wxString s_strNodePath;

protected:

private:
    std::tr1::shared_ptr<IMissMain> m_pMain;
};

#endif // MISSHOTKEYFUNC_H__

