#include "MissResManager.h"
#include "MissTools/MissZipReader.h"
#include "wx/string.h"
#include "../Common/MissPaths.h"

using std::tr1::shared_ptr;

class MissResManager::Impl
{
public:
	shared_ptr<MissZipReader> ptMainRes;

};

MissResManager::MissResManager()
: m_pImpl(new Impl)
{
	wxString strPath = MissPaths::Instance().GetAppPath() + wxT("Resource.bin");
	m_pImpl->ptMainRes = shared_ptr<MissZipReader>(new MissZipReader(strPath));
}

MissResManager::~MissResManager()
{

}

std::tr1::shared_ptr<MissZipReader> MissResManager::GetMainRes() const
{
	return m_pImpl->ptMainRes;
}

