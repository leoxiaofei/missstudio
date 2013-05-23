#include "MissAlgorithm.h"
#include <wx/hashmap.h>
#include <algorithm>


void MissAlgorithm::wxHash( const wxString& strSrc, wxString& strDes )
{
    wxStringHash hash;
    unsigned int hs = hash(strSrc);
    strDes.Printf(wxT("%08X"),hs);
}

template<typename T>
class FindSameChar
{
public:
	FindSameChar(T chSplit)
	: m_chSplit(chSplit){}

	bool operator()(T ch) const
	{
		return m_chSplit == ch;
	}
private:
	T m_chSplit;
};

void MissAlgorithm::split( const wxString& strSrc, std::vector<wxString>& vecDes,
						  wxString::value_type chSplit /*= wxT(' ')*/ )
{
	wxString::const_iterator i = strSrc.begin();
	wxString::const_iterator j;
	while (i != strSrc.end())
	{  
		i = std::find_if_not(i, strSrc.end(), FindSameChar<wxString::value_type>(chSplit));  
		j = std::find_if(i, strSrc.end(), FindSameChar<wxString::value_type>(chSplit));  

		// get valid word  
		if (i != j) {
			vecDes.push_back(wxString(i, j));  
			i = j;  
		}  
	}
}

