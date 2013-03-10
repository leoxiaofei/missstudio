#ifndef MISSPLUGINBASE_H
#define MISSPLUGINBASE_H

#include <wx/string.h>
#include <memory>

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

    static int APIVersion() {return 1;}

    /** \brief 得到主接口对象
    *
    * \return const std::tr1::shared_ptr<IMissMain>&
    *
    */
    const std::tr1::shared_ptr<IMissMain>& GetMain()
    {
        return m_pMain;
    }

    /** \brief 得到插件基本信息
    *
    * \return bool
    *
    */
    virtual bool GetPlugInfo(SPlugInfo& info) const {return false;}

    /** \brief 得到插件名称
    *
    * \return wxString
    *
    */
    virtual wxString GetPluginName() const {return wxT("Unknow Plugin");}

    /** \brief 得到插件唯一标识符
    *
    * \return wxString
    *
    */
    virtual wxString GetPluginGUID() const = 0;

protected:
    /** \brief 虚基类，需要继承后才可使用。
    *
    */
    MissPluginBase(){}

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
    /** \brief 初始化插件（由主程序调用）
    *
    * \param pParent const std::tr1::shared_ptr<IMissMain>&
    * \return void
    *
    */
    void InitPlugin(const std::tr1::shared_ptr<IMissMain>& pMain)
    {
        m_pMain = pMain;
        LoadPlugin();
    }

    /** \brief 关闭插件（由主程序调用）
    *
    * \return void
    *
    */
    void ClosePlugin()
    {
        UnloadPlugin();
    }

private:
    std::tr1::shared_ptr<IMissMain> m_pMain;
    friend class MissPluginManager;
};

//extern MissPluginBase* Msp;

#endif // MISSPLUGINBASE_H
