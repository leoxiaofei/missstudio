#ifndef MISSWIDGETFUNC_H
#define MISSWIDGETFUNC_H

#include "../../MissAPI/plugin/MissWidgetFuncBase.h"

class MissSkin;

class MissClockWidget : public MissWidgetFuncBase
{
    public:
        MissClockWidget();
        virtual ~MissClockWidget();

        void LoadSkin();

    ///接口实现
    public:
        virtual void InitWidget(const WidgetParas& para, wxFrame* pWidget);
        virtual void GetWidgetParas(WidgetParas& para);
        virtual void UpdateUI(wxDC &dc, const tm* tmNow);
        virtual wxSize GetSize();

    protected:
    private:
        shared_ptr<MissSkin> m_pSkin;
};

#endif // MISSWIDGETFUNC_H
