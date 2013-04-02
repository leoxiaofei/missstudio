#ifndef MISSPLUGINMAIN_H
#define MISSPLUGINMAIN_H

#include "MissAPI/plugin/MissPluginBase.h"
#include <memory>

class MissPluginMain : public MissPluginBase
{
    class Impl;
    public:
        MissPluginMain();
        virtual ~MissPluginMain();

    protected:
        ///初始化插件
        virtual void LoadPlugin();

        ///卸载插件
        virtual void UnloadPlugin();

        ///插件详细信息
        virtual bool GetPlugInfo( SPlugInfo& info ) const;

        ///插件名称
        virtual wxString GetPluginName() const;

        ///插件GUID
        virtual wxString GetPluginGUID() const;

    private:
        std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSPLUGINMAIN_H
