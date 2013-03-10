#ifndef MISSWIDGETFUNCBASE_H
#define MISSWIDGETFUNCBASE_H

#include <wx/event.h>
#include <unordered_map>
#include <memory>

class IMissWidget;

typedef std::tr1::unordered_map<wxString, wxString, wxStringHash, wxStringEqual> CustomPara;



class MissWidgetFuncBase : public wxEvtHandler
{
public:
    virtual ~MissWidgetFuncBase() {}

protected:
    const std::tr1::shared_ptr<IMissWidget>& GetWidget() { return m_pWidget; }
    virtual void SetWidgetPara(const CustomPara& para) {};
    virtual void GetWidgetParas(CustomPara& para) {};
    virtual void UpdateUI(const tm* tmNow) {};
    virtual void PreClose() {};

private:
    void InitWidget(const CustomPara& para, const std::tr1::shared_ptr<IMissWidget>& pWidget ) 
    {
        m_pWidget = pWidget;
        SetWidgetPara(para);
    }

private:
    std::tr1::shared_ptr<IMissWidget> m_pWidget;
    friend class MissWidget;
};

#endif // MISSWIDGETFUNCBASE_H
