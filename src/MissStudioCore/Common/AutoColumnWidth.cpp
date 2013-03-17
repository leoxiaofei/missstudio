#include "AutoColumnWidth.h"

#include <wx/headercol.h>
#include <wx/dataview.h>

#include <vector>
using std::vector;

class AutoColumnWidth::Impl
{
public:
    Impl()
    : pView(NULL)
    , nAutoColumn(-1)
    , nMinWidth(-1){}

    vector<wxSettableHeaderColumn*> vecColumn;
    wxDataViewCtrl* pView;
    int nAutoColumn;
    int nMinWidth;
};

AutoColumnWidth::AutoColumnWidth(wxDataViewCtrl* pView)
: wxObject()
, m_pImpl(new Impl)
{
    if (pView)
    {
        SetViewCtrl(pView);
    }
}

AutoColumnWidth::~AutoColumnWidth()
{
    if (m_pImpl->pView)
    {
        m_pImpl->pView->Unbind(wxEVT_SIZE, &AutoColumnWidth::OnViewResize, this);
    }
}

void AutoColumnWidth::SetAutoColumn( int nColumn )
{
    m_pImpl->nAutoColumn = nColumn;
}

AutoColumnWidth& AutoColumnWidth::operator<<( wxSettableHeaderColumn* pColumn )
{
    m_pImpl->vecColumn.push_back(pColumn);
    return *this;
}

void AutoColumnWidth::OnViewResize( wxSizeEvent& event )
{
    event.Skip();
    if(m_pImpl->nAutoColumn != -1 && (int)m_pImpl->vecColumn.size() > m_pImpl->nAutoColumn)
    {
        int nCurWidth = event.GetSize().GetWidth() - 4;
        int nCal(0);
        for(vector<wxSettableHeaderColumn*>::size_type ix = 0;
            ix != m_pImpl->vecColumn.size(); ++ix)
        {
            if(ix != m_pImpl->nAutoColumn)
            {
                nCal += m_pImpl->vecColumn[ix]->GetWidth();
            }
        }
        nCal = nCurWidth - nCal;
        if( nCal < m_pImpl->nMinWidth)
        {
            nCal = m_pImpl->nMinWidth;
        }

        m_pImpl->vecColumn[m_pImpl->nAutoColumn]->SetWidth(nCal);
    }

}

void AutoColumnWidth::SetViewCtrl( wxDataViewCtrl* pView )
{
    m_pImpl->pView = pView;
    pView->Bind(wxEVT_SIZE, &AutoColumnWidth::OnViewResize, this);
}

void AutoColumnWidth::SetMinWidth( int nWidth )
{
    m_pImpl->nMinWidth = nWidth;
}

