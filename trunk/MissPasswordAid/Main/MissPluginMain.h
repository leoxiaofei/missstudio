#ifndef MISSPLUGINMAIN_H
#define MISSPLUGINMAIN_H

#include "../../MissAPI/plugin/MissPluginBase.h"
#include "../../MissAPI/plugin/MissHotKeyFuncBase.h"
#include <tr1/memory>

class MissPluginMain : public MissPluginBase, public MissHotKeyFuncBase
{
    class MissPluginMainImpl;
    public:
        MissPluginMain();
        virtual ~MissPluginMain();

        ///初始化插件
        virtual void LoadPlugin(const std::tr1::shared_ptr<IMissMain>& pParent);

        ///热键方法实现
        void RunFunc(int nFuncIndex);
        void ModifiedHotKey(int nFuncIndex, const wxString& strHotKey);

    protected:
    private:
        std::tr1::shared_ptr<MissPluginMainImpl> m_pImpl;
};

#endif // MISSPLUGINMAIN_H
