#ifndef MISSPLUGINTEST_H
#define MISSPLUGINTEST_H

#include "../../MissAPI/plugin/MissPluginBase.h"
#include "../../MissAPI/plugin/MissHotKeyFuncBase.h"
#include "../../MissAPI/plugin/MissWidgetFactoryBase.h"

class MissClockPlugin : public MissPluginBase, public MissHotKeyFuncBase, public MissWidgetFactoryBase
{
    public:
        MissClockPlugin();
        virtual ~MissClockPlugin();

        ///热键方法实现
        void RunFunc(int nFuncIndex);
        void ModifiedHotKey(int nFuncIndex, const wxString& strHotKey);

        ///创建widget实现
        MissWidgetFuncBase* CreateWidgetFunc(unsigned int nIndex);
        void CreateSuccessed(MissWidgetUpdateFunc* pUpdate);

    protected:
        ///初始化插件
        void LoadPlugin();

    private:
};

#endif // MISSPLUGINTEST_H
