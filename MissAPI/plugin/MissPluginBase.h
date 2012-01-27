#ifndef MISSPLUGINBASE_H
#define MISSPLUGINBASE_H

#include <wx/string.h>
#include "../interface/IMissPlugin.h"


class IMissMain;

class MissPluginBase:virtual public IMissPlugin
{
    public:
        virtual ~MissPluginBase(){}
        virtual void LoadPlugin(){}
        virtual void UnloadPlugin(){}
        const SPlugInfo& GetPlugInfo() {return _info;}

        static int APIVersion(){return 1;}

    protected:
        /** \brief 虚基类，需要继承后才可使用。
         *
         *
         */
        MissPluginBase(IMissMain* pParent):m_pParent(pParent){}

        /** \brief 初始化插件信息，请在子类构造函数中调用
         *
         * \param info const SPlugInfo&
         * \return void
         *
         */
        void SetPlugInfo(const SPlugInfo& info){_info = info;}

        /** \brief 得到主接口
         *
         * \return IMissMain*
         *
         */
        IMissMain* GetMain(){return m_pParent;}

    private:
        SPlugInfo _info;
        IMissMain* m_pParent;
};

#endif // MISSPLUGINBASE_H
