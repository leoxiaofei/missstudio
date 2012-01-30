#ifndef MISSWIDGETMANAGER_H
#define MISSWIDGETMANAGER_H


class MissWidgetManager
{
    public:
        MissWidgetManager();
        virtual ~MissWidgetManager();

        std::tr1::shared_ptr<wxFrame> CreateWidget();
    protected:
    private:
};

#endif // MISSWIDGETMANAGER_H
