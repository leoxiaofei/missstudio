#ifndef MISSWIDGETSDAL_H
#define MISSWIDGETSDAL_H

class MissWidgetsDAL
{
    class MissWidgetsDALImpl;
public:
    MissWidgetsDAL();
    virtual ~MissWidgetsDAL();

    bool SaveCurWidgets();
    bool LoadCurWidgets();

protected:
    void InitDB();

private:
    std::tr1::shared_ptr<MissWidgetsDALImpl> m_pImpl;
};

#endif // MISSWIDGETSDAL_H
