#include "MissPaths.h"
#include <wx/stdpaths.h>
#include "MissTools/MissAlgorithm.h"
#include "ConfigId.h"

class MissPaths::Impl
{
public:
    Impl():nDirType(DTD::PCD_GLOBAL){}
    int nDirType;
    wxStandardPaths spDir;
};

MissPaths::MissPaths()
: m_pImpl(new Impl)
{
}

MissPaths::~MissPaths()
{
}

void MissPaths::SetConfigDirType( int nType )
{
    if (nType >= DTD::PCD_GLOBAL && nType <= DTD::PCD_SYSTEMUSER)
    {
        m_pImpl->nDirType = nType;
    }
}

wxString MissPaths::GetDataBasePath() const
{
    return m_pImpl->spDir.GetDataDir() + wxT("\\..\\Config\\");
}

wxString MissPaths::GetPluginPath() const
{
    return m_pImpl->spDir.GetDataDir() + wxT("\\..\\Plugin\\");
}

wxString MissPaths::GetConfigPath() const
{
    wxString strRet = GetDataBasePath();
    switch (m_pImpl->nDirType)
    {
    case DTD::PCD_GLOBAL:
        {
            strRet += wxT("Public\\");
        }
        break;
    case DTD::PCD_SYSTEMUSER:
        {
            static wxString strUserTag;
            if (strUserTag.IsEmpty())
            {
                wxString strSrc, strDes;
                strSrc = m_pImpl->spDir.GetUserConfigDir().MakeUpper();
                MissAlgorithm::wxHash(strSrc, strDes);
                strUserTag = wxT("Users\\") + strDes;
                MissAlgorithm::wxHash(strSrc + wxT("MissStudio"), strDes);
                strUserTag += (wxT("-") + strDes + wxT("\\"));
            }
            strRet += strUserTag;
        }
        break;
    default:
        assert(false);
        break;
    }
    return strRet;
}

wxString MissPaths::GetAppPath() const
{
	return m_pImpl->spDir.GetDataDir() + wxT("\\");
}
