#ifndef __MISSDESKTOPTOOLS__
#define __MISSDESKTOPTOOLS__


#include "..\Generated\GUIFrame.h"

#include <memory>

class wxDataViewEvent;

class MissDesktopTools : public DesktopToolsBase
{
    class Impl;
	public:
		MissDesktopTools( wxWindow* parent );
	    ~MissDesktopTools();

protected:
    void InitUi();
    void BindEvent();

    void DClickInstalledItem(wxDataViewEvent& event);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // __MISSDESKTOPTOOLS__
