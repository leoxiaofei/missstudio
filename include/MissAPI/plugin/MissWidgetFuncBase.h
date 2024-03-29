#ifndef MISSWIDGETFUNCBASE_H
#define MISSWIDGETFUNCBASE_H

#include <unordered_map>
#include <memory>
#include <wx/string.h>
#include <wx/hashmap.h>

class IMissWidget;

typedef std::tr1::unordered_map<wxString, wxString, wxStringHash, wxStringEqual> CustomPara;

class MissWidgetFuncBase
{
public:
    virtual ~MissWidgetFuncBase() {}

	virtual void UpdateUI() = 0;

protected:
    IMissWidget* GetWidget() const { return m_pWidget; }
    virtual void SetWidgetPara(const CustomPara& para) {};
    virtual void GetWidgetPara(CustomPara& para) const {};
    virtual void PreClose() {};

private:
    void InitWidget(const CustomPara& para, IMissWidget* pWidget ) 
    {
        m_pWidget = pWidget;
        SetWidgetPara(para);
    }

private:
    IMissWidget* m_pWidget;
    friend class ImplMissWidget;
};

#endif // MISSWIDGETFUNCBASE_H
