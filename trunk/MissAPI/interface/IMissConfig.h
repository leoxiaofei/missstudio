#ifndef IMISSCONFIG_H
#define IMISSCONFIG_H


class IMissConfig
{
    public:
        virtual ~IMissConfig() {}
        virtual bool Write(const wxString& key, const wxString& value) = 0;
        virtual bool Write(const wxString& key, long value) = 0;
        virtual bool Write(const wxString& key, double value) = 0;
        virtual bool Write(const wxString& key, bool value) = 0;

        virtual bool Read(const wxString& key, wxString& value) const = 0;
        virtual bool Read(const wxString& key, long& value) const = 0;
        virtual bool Read(const wxString& key, double& value) const = 0;
        virtual bool Read(const wxString& key, bool& value) const = 0;

    protected:
    private:
};

#endif // IMISSCONFIG_H
