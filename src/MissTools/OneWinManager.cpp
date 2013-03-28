#include "OneWinManager.h"

#include <wx/window.h>
#include <wx/event.h>
#include <algorithm>

class OneWinManager::FindSameWindow
{
public:
	FindSameWindow(wxObject* pObject):m_pObject(pObject){};
	bool operator ()(const std::pair<wxString, wxWindow*>& win) const
	{
		return win.second == m_pObject;
	}
private:
	wxObject* m_pObject;
};

OneWinManager::OneWinManager( wxWindow* pParent )
: m_pParent(pParent)
{

}

void OneWinManager::DestroyWin( wxCloseEvent& event )
{
	HsWin::iterator iFind = std::find_if(m_hsWin.begin(), m_hsWin.end(), 
		FindSameWindow(event.GetEventObject()));
	if (iFind != m_hsWin.end())
	{
		iFind->second->Unbind(wxEVT_CLOSE_WINDOW, &OneWinManager::DestroyWin, this);
		iFind->second->Destroy();
		m_hsWin.erase(iFind);
	}
}