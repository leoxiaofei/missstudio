#ifndef MISSHOTKEYFUNCBASE_H
#define MISSHOTKEYFUNCBASE_H

#include "../interface/IMissPlugin.h"

class MissHotKeyFuncBase: virtual public IMissPlugin
{
    public:
        virtual ~MissHotKeyFuncBase() {}

        virtual void RunFunc(int nFuncIndex) = 0;
        virtual void ModifyHotKey(int nFuncIndex, const wxString& strHotKey) = 0;

    protected:

    private:
};

#endif // MISSHOTKEYFUNCBASE_H
