#ifndef AUTOCOLUMNWIDTH_H__
#define AUTOCOLUMNWIDTH_H__

#include <memory>
#include <wx\object.h>

class wxDataViewCtrl;
class wxSettableHeaderColumn;
class wxSizeEvent;

class AutoColumnWidth : public wxObject
{
    class Impl;

public:
    AutoColumnWidth(wxDataViewCtrl* pView = NULL);
    ~AutoColumnWidth();

    void SetViewCtrl(wxDataViewCtrl* pView);
    void SetAutoColumn(int nColumn);
    void SetMinWidth(int nWidth);

    AutoColumnWidth& operator << (wxSettableHeaderColumn* pColumn);

protected:
    void OnViewResize(wxSizeEvent& event);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // AUTOCOLUMNWIDTH_H__
