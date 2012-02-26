#ifndef MISSWIDGETSDAL_H
#define MISSWIDGETSDAL_H


class MissWidgetsDAL
{
    public:
        MissWidgetsDAL();
        virtual ~MissWidgetsDAL();

        bool SaveCurWidgets();
        bool LoadCurWidgets();
    protected:
    private:
};

#endif // MISSWIDGETSDAL_H
