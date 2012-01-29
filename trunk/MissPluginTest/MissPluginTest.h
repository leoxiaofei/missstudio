#ifndef MISSPLUGINTEST_H
#define MISSPLUGINTEST_H

#include "../MissAPI/plugin/MissPluginBase.h"
#include "../MissAPI/plugin/MissHotKeyFuncBase.h"

class MissPluginTest : public MissPluginBase, public MissHotKeyFuncBase
{
    public:
        MissPluginTest(IMissMain* pParent);
        virtual ~MissPluginTest();

        ///初始化插件
        void LoadPlugin();

        ///热键方法实现
        void RunFunc(int nFuncIndex);
        void ModifiedHotKey(int nFuncIndex, const wxString& strHotKey);

    protected:
    private:
};

#endif // MISSPLUGINTEST_H
