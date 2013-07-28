#ifndef ONEWINMANAGER_H__
#define ONEWINMANAGER_H__

#include "MissGlobal.h"

#include <wx/string.h>
#include <wx/hashmap.h>

#include <unordered_map>

class wxWindow;
class wxCloseEvent;

class DLL_EXPORT OneWinManager
{
	typedef std::tr1::unordered_map<wxString, wxWindow*, wxStringHash, wxStringEqual> HsWin;

public:
	OneWinManager(wxWindow* pParent);

	template <class T>
	T* CreateWin(const wxString& strWindow)
	{
		T* pRet(NULL);
		HsWin::iterator iFind = m_hsWin.find(strWindow);
		if (iFind != m_hsWin.end())
		{
			pRet = static_cast<T*>(iFind->second);
		}
		else
		{
			pRet = new T(m_pParent);
			m_hsWin.insert(HsWin::value_type(strWindow, pRet));
			pRet->Bind( wxEVT_CLOSE_WINDOW, &OneWinManager::DestroyWin, this );
			pRet->Show();
		}
		return pRet;
	}

    template <class T, class P>
    T* CreateWin(const wxString& strWindow, const P& Param)
    {
        T* pRet(NULL);
        HsWin::iterator iFind = m_hsWin.find(strWindow);
        if (iFind != m_hsWin.end())
        {
            pRet = static_cast<T*>(iFind->second);
        }
        else
        {
            pRet = new T(m_pParent, Param);
            m_hsWin.insert(HsWin::value_type(strWindow, pRet));
            pRet->Bind( wxEVT_CLOSE_WINDOW, &OneWinManager::DestroyWin, this );
            pRet->Show();
        }
        return pRet;
    }
protected:
	void DestroyWin(wxCloseEvent& event);
	class FindSameWindow;

private:
	HsWin     m_hsWin;
	wxWindow* m_pParent;
};


#endif // ONEWINMANAGER_H__