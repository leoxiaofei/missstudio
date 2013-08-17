#ifndef MISSPATHS_h__
#define MISSPATHS_h__

#include <memory>
#include <wx/string.h>

class wxFileName;

class MissPaths
{
    class Impl;

public:
    static MissPaths& Instance()
    {
        static MissPaths theSingleton;
        return theSingleton;
    }

	wxString GetAppPath() const;
    wxString GetDataBasePath() const;
    wxString GetPluginPath() const;
    wxString GetConfigPath() const;
	wxString GetResPath() const;

    void SetConfigDirType(int nType);

	void CheckMakePaths();

protected:
	void CheckMakePath( const wxString& strDir );

private:
    MissPaths();
    ~MissPaths();
    MissPaths(const MissPaths&);
    MissPaths& operator=(const MissPaths&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSPATHS_h__
