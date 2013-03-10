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
        ///��ʼ�����
        virtual void LoadPlugin();

        ///ж�ز��
        virtual void UnloadPlugin();

        ///�����ϸ��Ϣ
        virtual bool GetPlugInfo( SPlugInfo& info ) const;

        ///�������
        virtual wxString GetPluginName() const;

        ///���GUID
        virtual wxString GetPluginGUID() const;

    private:
        std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSPLUGINMAIN_H
