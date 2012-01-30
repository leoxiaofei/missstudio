#ifndef MISSHOTKEYFUNCBASE_H
#define MISSHOTKEYFUNCBASE_H

#include "../interface/IMissPlugin.h"

class MissHotKeyFuncBase: public IMissPlugin
{
    public:
        MissHotKeyFuncBase(MissPluginBase* pPlugin):IMissPlugin(pPlugin){};
        virtual ~MissHotKeyFuncBase() {}

        virtual void RunFunc(int nFuncIndex) = 0;
        virtual void ModifiedHotKey(int nFuncIndex, const wxString& strHotKey) = 0;

    protected:


    private:
};

#endif // MISSHOTKEYFUNCBASE_H
