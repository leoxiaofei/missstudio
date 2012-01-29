#ifndef MISSCONFIGFILE_H
#define MISSCONFIGFILE_H

#include <wx/string.h>
#include <tr1/memory>
#include "../MissAPI/interface/IMissConfig.h"

class MissConfigFile:public IMissConfig
{
    class MissConfigFileImpl;

    public:
        MissConfigFile(const wxString& strFileName);
        virtual ~MissConfigFile();

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
        std::tr1::shared_ptr<MissConfigFileImpl> m_pImpl;
};

#endif // MISSCONFIGFILE_H
