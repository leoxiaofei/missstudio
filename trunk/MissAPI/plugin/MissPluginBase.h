#ifndef MISSPLUGINBASE_H
#define MISSPLUGINBASE_H

#include <wx/string.h>
#include <tr1/memory>

struct SPlugInfo
{
    wxString strPluginName;
    wxString strVersion;
    wxString strAuthor;
    wxString strEmail;
    wxString strWeb;
    wxString strSpecification;
};

class IMissMain;

class MissPluginBase
{
    public:
        virtual ~MissPluginBase(){}

        virtual void LoadPlugin(const std::tr1::shared_ptr<IMissMain>& pParent)
        {
            m_pParent = pParent;
        }

        virtual void UnloadPlugin(){}

        const SPlugInfo& GetPlugInfo() const {return m_Info;}
        //const wxString & GetPluginPath() const {return m_PluginPath;}
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

        /** \brief 得到主接口
         *
         * \return const std::tr1::shared_ptr<IMissMain>&
         *
         */
        const std::tr1::shared_ptr<IMissMain>& GetMain(){return m_pParent;}

    private:
        SPlugInfo  m_Info;
        std::tr1::shared_ptr<IMissMain> m_pParent;
        //wxString   m_PluginPath;
};

#endif // MISSPLUGINBASE_H
