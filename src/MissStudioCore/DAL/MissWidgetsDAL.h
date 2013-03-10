#ifndef MISSWIDGETSDAL_H
#define MISSWIDGETSDAL_H


#include <memory>

namespace DTD
{
    struct SWidgetPara;
}

class MissWidgetsDAL
{
    class Impl;

public:
    static MissWidgetsDAL& Instance()
    {
        static MissWidgetsDAL theSingleton;
        return theSingleton;
    }

    bool SaveCurWidgets();
    bool LoadRunWidgets();

    //int NewWidget(const wxString& strPName, int nType);

protected:
    void InitDB();

private:
    MissWidgetsDAL();
    ~MissWidgetsDAL();
    MissWidgetsDAL(const MissWidgetsDAL&);
    MissWidgetsDAL& operator=(const MissWidgetsDAL&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSWIDGETSDAL_H
