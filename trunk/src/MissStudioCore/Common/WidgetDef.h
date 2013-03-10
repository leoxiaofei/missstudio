#ifndef MISSDATATYPEDEF_H
#define MISSDATATYPEDEF_H

//#include <tr1/unordered_map>
#include <unordered_map>
#include <wx/string.h>
#include <wx/gdicmn.h>

typedef std::tr1::unordered_map<wxString, wxString, wxStringHash, wxStringEqual> CustomPara;

namespace DTD
{
    struct SWidgetPara
    {
        SWidgetPara()
            : m_nZone(100)
            , m_nOpacity(255)
            , m_ptPos(0,0)
        {}
        int         m_nZone;
        int         m_nOpacity;
        wxPoint     m_ptPos;
        CustomPara  m_vecPata;
    };

}

#endif // MISSDATATYPEDEF_H
