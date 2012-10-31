#ifndef MISSWIDGETSDAL_H
#define MISSWIDGETSDAL_H

namespace DTD
{
    struct SWidgetPara;
}

class MissWidgetsDAL
{
    class Impl;
public:
    MissWidgetsDAL();
    virtual ~MissWidgetsDAL();

    bool SaveCurWidgets();
    bool LoadRunWidgets();

    int NewWidget(const wxString& strPName, int nType);

protected:
    void InitDB();

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSWIDGETSDAL_H
