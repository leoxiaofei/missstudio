#ifndef MISSALGORITHM_H__
#define MISSALGORITHM_H__

#include "MissGlobal.h"
#include <wx/string.h>
#include <vector>

class DLL_EXPORT MissAlgorithm
{
public:
    static void wxHash(const wxString& strSrc, wxString& strDes);
	static void split(const wxString& strSrc, std::vector<wxString>& vecDes, wxString::value_type chSplit = wxT(' '));
};


#endif // MISSALGORITHM_H__
