#ifndef MISSPATHS_h__
#define MISSPATHS_h__

#include <memory>
#include <wx/string.h>

class MissPaths
{
    class Impl;

public:
    static MissPaths& Instance()
    {
        static MissPaths theSingleton;
        return theSingleton;
    }

    wxString GetDataBaseDir() const;
    wxString GetPluginDir() const;
    wxString GetConfigPath() const;

    void SetConfigDirType(int nType);


private:
    MissPaths();
    ~MissPaths();
    MissPaths(const MissPaths&);
    MissPaths& operator=(const MissPaths&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSPATHS_h__
