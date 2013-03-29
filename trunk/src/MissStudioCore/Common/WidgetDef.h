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
            : m_uRunID(0)
            , m_uZone(100)
            , m_uOpacity(255)
            , m_ptPos(0,0)
        {}
        unsigned int m_uRunID;
        unsigned int m_uZone;
        unsigned int m_uOpacity;
        wxPoint      m_ptPos;
        CustomPara   m_vecPata;
    };

}

#endif // MISSDATATYPEDEF_H
