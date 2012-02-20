#ifndef MISSPLUGINMAIN_H
#define MISSPLUGINMAIN_H

#include "../../MissAPI/plugin/MissPluginBase.h"
#include "../../MissAPI/plugin/MissHotKeyFuncBase.h"

class MissPluginMain : public MissPluginBase, public MissHotKeyFuncBase
{
    public:
        MissPluginMain(IMissMain* pParent);
        virtual ~MissPluginMain();

        ///初始化插件
        virtual void LoadPlugin(const wxString& strPath);

        ///热键方法实现
        void RunFunc(int nFuncIndex);
        void ModifiedHotKey(int nFuncIndex, const wxString& strHotKey);

    protected:
    private:
};

#endif // MISSPLUGINMAIN_H
