#ifndef MISSWIDGETMENU_H__
#define MISSWIDGETMENU_H__

#include <memory>

class ImplMissWidget;
class wxCommandEvent;
class wxMenu;

class MissWidgetMenu
{
    class Impl;
public:
    static MissWidgetMenu& Instance()
    {
        static MissWidgetMenu theSingleton;
        return theSingleton;
    }

	std::tr1::shared_ptr<wxMenu> GetMenu(ImplMissWidget* pWidgets);

protected:
    void BindEvent();
    void UnbindEvent();

    void OnMenuWidgetOption(wxCommandEvent& event);
    void OnMenuWidgetExit(wxCommandEvent& event);

private:
    MissWidgetMenu();
    ~MissWidgetMenu();
    MissWidgetMenu(const MissWidgetMenu&);
    MissWidgetMenu& operator=(const MissWidgetMenu&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSWIDGETMENU_H__
