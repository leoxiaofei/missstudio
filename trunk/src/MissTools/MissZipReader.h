#ifndef MISSZIPREADER_H__
#define MISSZIPREADER_H__

#include "MissGlobal.h"
#include <memory>

class wxImage;
class wxBitmap;
class wxSound;
class wxString;

class DLL_EXPORT MissZipReader
{
	class Impl;
public:
	MissZipReader(const wxString& strZipFile);
	~MissZipReader();

	std::tr1::shared_ptr<wxImage>  LoadImage(const wxString& strFile);
	std::tr1::shared_ptr<wxBitmap> LoadBitmap(const wxString& strFile);
	std::tr1::shared_ptr<wxSound>  LoadSound(const wxString& strFile);

protected:
	void InitReader(const wxString& strZipFile);

private:
	Impl* m_pImpl;
};

#endif // MISSZIPREADER_H__
