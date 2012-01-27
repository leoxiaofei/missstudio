#ifndef IMISSPLUGIN_H
#define IMISSPLUGIN_H

struct SPlugInfo
{
    wxString strPluginName;
    wxString strVersion;
    wxString strAuthor;
    wxString strEmail;
    wxString strWeb;
    wxString strSpecification;
};

class IMissPlugin
{
    public:
        virtual ~IMissPlugin() {}
        virtual const SPlugInfo& GetPlugInfo() = 0;
    protected:
    private:
};

#endif // IMISSPLUGIN_H
