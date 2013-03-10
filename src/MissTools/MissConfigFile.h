#ifndef MISSCONFIGFILE_H__
#define MISSCONFIGFILE_H__

#include <wx/string.h>
#include <memory>
#include "MissGlobal.h"

class DLL_EXPORT MissConfigFile
{
    class Impl;

    public:
        MissConfigFile(const wxString& strFileName);
        ~MissConfigFile();

        bool Write(const wxString& key, const wxString& value);
        bool Write(const wxString& key, long value);
        bool Write(const wxString& key, double value);
        bool Write(const wxString& key, bool value);

        bool Read(const wxString& key, wxString& value) const;
        bool Read(const wxString& key, long& value) const;
        bool Read(const wxString& key, double& value) const;
        bool Read(const wxString& key, bool& value) const;

    protected:
        void SaveConfig();

    private:
        std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSCONFIGFILE_H__
