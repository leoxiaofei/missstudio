#ifndef MISSPLUGINTEST_H
#define MISSPLUGINTEST_H

#include "../MissAPI/plugin/MissPluginBase.h"
#include "../MissAPI/plugin/MissHotKeyFuncBase.h"

class MissPluginTest : public MissPluginBase, public MissHotKeyFuncBase
{
    public:
        MissPluginTest(IMissMain* pParent);
        virtual ~MissPluginTest();

        void RunFunc(int nFuncIndex);
        void ModifyHotKey(int nFuncIndex, const wxString& strHotKey);
        void LoadPlugin();
    protected:
    private:
};

#endif // MISSPLUGINTEST_H
