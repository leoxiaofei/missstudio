#include "MissAlgorithm.h"
#include <wx/hashmap.h>


void MissAlgorithm::wxHash( const wxString& strSrc, wxString& strDes )
{
    wxStringHash hash;
    unsigned int hs = hash(strSrc);
    strDes.Printf(wxT("%08X"),hs);
}

