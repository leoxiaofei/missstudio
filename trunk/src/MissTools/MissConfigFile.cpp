#include "MissConfigFile.h"
#include <wx/fileconf.h>
#include <wx/wfstream.h>

using std::tr1::shared_ptr;

class MissConfigFile::Impl
{
public:
    Impl(const wxString& strFileName):
        m_ConfigName(strFileName),
        m_bWrite(false)
    {};

public:
    wxString m_ConfigName;                      ///配置文件名
    shared_ptr<wxFileInputStream> m_pIStream;   ///文件流
    shared_ptr<wxFileConfig> m_pConfigFile;     ///配置文件读写器
    bool     m_bWrite;
};

MissConfigFile::MissConfigFile(const wxString& strFileName):
m_pImpl(new Impl(strFileName))
{
    //ctor
    if(!wxFile::Exists(m_pImpl->m_ConfigName))
    {
        wxFile file;
        file.Create(m_pImpl->m_ConfigName);
        file.Close();
    }
    m_pImpl->m_pIStream = shared_ptr<wxFileInputStream>(new wxFileInputStream(m_pImpl->m_ConfigName));
    m_pImpl->m_pConfigFile = shared_ptr<wxFileConfig>(new wxFileConfig(*m_pImpl->m_pIStream));
}

MissConfigFile::~MissConfigFile()
{
    //dtor
    if(m_pImpl->m_bWrite)
    {
        SaveConfig();
    }
}

void MissConfigFile::SaveConfig()
{
    wxFileOutputStream oStream(m_pImpl->m_ConfigName);
    m_pImpl->m_pConfigFile->Save(oStream);
}

bool MissConfigFile::Write(const wxString& key, const wxString& value)
{
    m_pImpl->m_bWrite = true;
    return m_pImpl->m_pConfigFile->Write(key, value);
}

bool MissConfigFile::Write(const wxString& key, long value)
{
    m_pImpl->m_bWrite = true;
    return m_pImpl->m_pConfigFile->Write(key, value);
}

bool MissConfigFile::Write(const wxString& key, double value)
{
    m_pImpl->m_bWrite = true;
    return m_pImpl->m_pConfigFile->Write(key, value);
}

bool MissConfigFile::Write(const wxString& key, bool value)
{
    m_pImpl->m_bWrite = true;
    return m_pImpl->m_pConfigFile->Write(key, value);
}

bool MissConfigFile::Read(const wxString& key, wxString& value) const
{
    return m_pImpl->m_pConfigFile->Read(key, &value);
}

bool MissConfigFile::Read(const wxString& key, long& value) const
{
    return m_pImpl->m_pConfigFile->Read(key, &value);
}

bool MissConfigFile::Read(const wxString& key, double& value) const
{
    return m_pImpl->m_pConfigFile->Read(key, &value);
}

bool MissConfigFile::Read(const wxString& key, bool& value) const
{
    return m_pImpl->m_pConfigFile->Read(key, &value);
}
