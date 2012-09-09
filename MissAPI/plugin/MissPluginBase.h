#ifndef MISSPLUGINBASE_H
#define MISSPLUGINBASE_H

#include <wx/string.h>
#include <tr1/memory>

class IMissMain;

struct SPlugInfo
{
    wxString strPluginName;
    wxString strVersion;
    wxString strAuthor;
    wxString strEmail;
    wxString strWeb;
    wxString strSpecification;
};

class MissPluginBase
{
    public:
        virtual ~MissPluginBase(){}

        /** \brief 初始化控件由主程序调用
         *
         * \param pParent const std::tr1::shared_ptr<IMissMain>&
         * \return void
         *
         */
        void InitPlugin(const std::tr1::shared_ptr<IMissMain>& pParent)
        {
            m_pParent = pParent;
            LoadPlugin();
        }

        /** \brief 得到主接口对象
         *
         * \return const std::tr1::shared_ptr<IMissMain>&
         *
         */
        const std::tr1::shared_ptr<IMissMain>& GetMain()
        {
            return m_pParent;
        }

        /** \brief 得到插件基本信息
         *
         * \return const SPlugInfo&
         *
         */
        const SPlugInfo& GetPlugInfo() const {return m_Info;}

        static int APIVersion(){return 1;}

    protected:
        /** \brief 虚基类，需要继承后才可使用。
         *
         */
        MissPluginBase(){}

        /** \brief 初始化插件信息，请在子类构造函数中调用
         *
         * \param info const SPlugInfo&
         * \return void
         *
         */
        void SetPlugInfo(const SPlugInfo& info){m_Info = info;}

        /** \brief 初始化插件接口
         *
         * \return virtual void
         *
         */
        virtual void LoadPlugin(){}

        /** \brief 卸载插件接口
         *
         * \return virtual void
         *
         */
        virtual void UnloadPlugin(){}

    private:
        SPlugInfo  m_Info;
        std::tr1::shared_ptr<IMissMain> m_pParent;
        //wxString   m_PluginPath;
};

extern MissPluginBase* Msp;

#endif // MISSPLUGINBASE_H
