#include "MissZipReader.h"

#include <wx/string.h>
#include <wx/filesys.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/sound.h>
#include <wx/fs_arc.h>

#include <list>
#include <utility>
#include <memory>
#include <algorithm>


template <class T>
class FindLRUName
{
public:
	FindLRUName(const wxString& strFileName)
	: strName(strFileName){}

	bool operator ()(const std::pair<wxString, 
		std::tr1::shared_ptr<T> >& data) const
	{
		return data.first == strName;
	}

private:
	const wxString& strName;
};

template <class T>
class ContainerLRU
{
public:
	ContainerLRU(int nCount = 30)
	{
		SetCount(nCount);
	}

	~ContainerLRU()
	{

	}

	void SetCount(int nCount)
	{
		m_nCount = nCount;
	}

	std::tr1::shared_ptr<T> GetData(const wxString& strName)
	{
		std::tr1::shared_ptr<T> pRet;
		ListData::iterator iFind = 
			std::find_if(m_listData.begin(), m_listData.end(), FindLRUName<T>(strName));
		if (iFind != m_listData.end())
		{
			pRet = iFind->second;
			m_listData.splice(m_listData.end(), m_listData, iFind, iFind);
		}

		return pRet;
	}

	void AddData(const wxString& strName, const std::tr1::shared_ptr<T>& data)
	{
		m_listData.push_back(std::make_pair(strName, data));
		while (m_listData.size() > (size_t)m_nCount)
		{
			m_listData.pop_front();
		}
	}

private:
	typedef std::list<std::pair<wxString, std::tr1::shared_ptr<T> > >  ListData;

	int        m_nCount;
	ListData   m_listData;
};

class MissZipReader::Impl
{
public:
	wxString     strZipFile;
	wxFileSystem fsZip;

	ContainerLRU<wxImage>  lruImage;
	ContainerLRU<wxBitmap> lruBitmap;
	ContainerLRU<wxSound>  lruSound;
};

MissZipReader::MissZipReader( const wxString& strZipFile)
: m_pImpl(new Impl)
{
	InitReader(strZipFile);
}

MissZipReader::~MissZipReader()
{
	delete m_pImpl;
}

void MissZipReader::InitReader( const wxString& strZipFile )
{
	m_pImpl->strZipFile = wxFileSystem::FileNameToURL(strZipFile);
}

std::tr1::shared_ptr<wxImage> MissZipReader::LoadImage( const wxString& strFile )
{
	std::tr1::shared_ptr<wxImage> pt = m_pImpl->lruImage.GetData(strFile);
	if (!pt)
	{
		wxFSFile* file = m_pImpl->fsZip.OpenFile(m_pImpl->strZipFile + wxT("#zip:") + strFile);
		if (file)
		{
			pt = std::tr1::shared_ptr<wxImage>(new wxImage(*file->GetStream(), wxBITMAP_TYPE_PNG));
			if (pt->IsOk())
			{
				m_pImpl->lruImage.AddData(strFile, pt);
			}
			delete file;
		}
	}
	return pt;
}

std::tr1::shared_ptr<wxBitmap> MissZipReader::LoadBitmap( const wxString& strFile )
{
	std::tr1::shared_ptr<wxBitmap> pt = m_pImpl->lruBitmap.GetData(strFile);
	if (!pt)
	{
		wxFSFile* file = m_pImpl->fsZip.OpenFile(m_pImpl->strZipFile + wxT("#zip:") + strFile);
		if (file)
		{
			wxImage image(*file->GetStream(), wxBITMAP_TYPE_ANY);
			if (image.IsOk())
			{
				pt = std::tr1::shared_ptr<wxBitmap>(new wxBitmap(image));
				m_pImpl->lruBitmap.AddData(strFile, pt);
			}
			delete file;
		}
	}
	return pt;
}	

std::tr1::shared_ptr<wxSound> MissZipReader::LoadSound( const wxString& strFile )
{
	std::tr1::shared_ptr<wxSound> pt = m_pImpl->lruSound.GetData(strFile);
	if (!pt)
	{
		wxFSFile* file = m_pImpl->fsZip.OpenFile(m_pImpl->strZipFile + wxT("#zip:") + strFile);
		if (file)
		{
			wxInputStream * pStream = file->GetStream();
			int nSize = pStream->GetSize();
			unsigned char* ch = new unsigned char[nSize];
			pStream->Read((void*)ch, nSize);
			pt = std::tr1::shared_ptr<wxSound>(new wxSound(nSize, ch));
			if (pt->IsOk())
			{
				m_pImpl->lruSound.AddData(strFile, pt);
			}
			delete[] ch;
			delete   file;
		}
	}
	return pt;
}

