#ifndef IMISSPLUGIN_H
#define IMISSPLUGIN_H

class MissPluginBase;

class IMissPlugin
{
    public:
        virtual ~IMissPlugin() {}
        const MissPluginBase* GetPlugin(){return m_pPlugin;}

    protected:
        IMissPlugin(MissPluginBase* pParent):m_pPlugin(pParent){}

    private:
        MissPluginBase* m_pPlugin;
};

#endif // IMISSPLUGIN_H
