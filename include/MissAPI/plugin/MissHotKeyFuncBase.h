#ifndef MISSHOTKEYFUNCBASE_H
#define MISSHOTKEYFUNCBASE_H

#include <wx/string.h>

struct SHotKeyMajor;

class MissHotKeyFuncBase
{
    public:
        virtual ~MissHotKeyFuncBase() {}

        ///功能名
        ///功能描述
        virtual void GetHotKeyName( int nFuncId, wxString& strFuncName ) = 0;
        virtual void GetHotkeyDesc( int nFuncId, wxString& strFuncDesc) {};
        virtual void RunFunc(int nFuncId) = 0;
        virtual void ModifiedHotKey( const SHotKeyMajor& sNewHotkey ) = 0;

    protected:


    private:
};

#endif // MISSHOTKEYFUNCBASE_H
