#ifndef MISSDATATYPEDEF_H
#define MISSDATATYPEDEF_H

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
            , m_bShadow(false)
            , m_bPin(false)
            , m_nZPos(1)
        {}
        unsigned int m_uRunID;
        unsigned int m_uZone;
        unsigned int m_uOpacity;
        wxPoint      m_ptPos;
        bool         m_bShadow;
        bool         m_bPin;
        int          m_nZPos;
        CustomPara   m_vecPara;
    };

}

#endif // MISSDATATYPEDEF_H
