#ifndef MISSPLUGINTEST_H
#define MISSPLUGINTEST_H

#include "../MissAPI/plugin/MissPluginBase.h"
#include "../MissAPI/plugin/MissHotKeyFuncBase.h"
#include "../MissAPI/plugin/MissWidgetFactoryBase.h"


class MissPluginTest : public MissPluginBase, public MissHotKeyFuncBase, public MissWidgetFactoryBase
{
    public:
        MissPluginTest();
        virtual ~MissPluginTest();

        ///初始化插件
        void LoadPlugin(const std::tr1::shared_ptr<IMissMain>& pParent);

        ///热键方法实现
        void RunFunc(int nFuncIndex);
        void ModifiedHotKey(int nFuncIndex, const wxString& strHotKey);

        ///创建widget实现
        MissWidgetFuncBase* CreateWidgetFunc(unsigned int nIndex);
        void CreateSuccessed(MissWidgetUpdateFunc* pUpdate);

    protected:
    private:
};

#endif // MISSPLUGINTEST_H
