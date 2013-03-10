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

    /** \brief �õ����ӿڶ���
    *
    * \return const std::tr1::shared_ptr<IMissMain>&
    *
    */
    const std::tr1::shared_ptr<IMissMain>& GetMain()
    {
        return m_pMain;
    }

    /** \brief �õ����������Ϣ
    *
    * \return bool
    *
    */
    virtual bool GetPlugInfo(SPlugInfo& info) const {return false;}

    /** \brief �õ��������
    *
    * \return wxString
    *
    */
    virtual wxString GetPluginName() const {return wxT("Unknow Plugin");}

    /** \brief �õ����Ψһ��ʶ��
    *
    * \return wxString
    *
    */
    virtual wxString GetPluginGUID() const = 0;

protected:
    /** \brief ����࣬��Ҫ�̳к�ſ�ʹ�á�
    *
    */
    MissPluginBase(){}

    /** \brief ��ʼ������ӿ�
    *
    * \return virtual void
    *
    */
    virtual void LoadPlugin(){}

    /** \brief ж�ز���ӿ�
    *
    * \return virtual void
    *
    */
    virtual void UnloadPlugin(){}

private:
    /** \brief ��ʼ�����������������ã�
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

    /** \brief �رղ��������������ã�
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
