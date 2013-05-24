#include "MissExtendManager.h"

#include <assert.h>
#include <wx/dynlib.h>
#include "../Common/MissPaths.h"
#include "wx/image.h"
#include "wx/filesys.h"
#include "wx/fs_arc.h"


class MissExtendManager::Impl
{
public:
    wxDynamicLibrary dllResource;
};

MissExtendManager::MissExtendManager()
: m_pImpl(new Impl)
{
    //ctor
}

MissExtendManager::~MissExtendManager()
{
    //dtor
}

void MissExtendManager::LoadPlugin()
{
// 	wxString strPath = MissPaths::Instance().GetAppPath() + wxT("MissResource.dll");
//     if(m_pImpl->dllResource.Load(strPath))
// 	{
// 		typedef void (* PFN_InitXrc)();
// 		PFN_InitXrc pAPIFun = (PFN_InitXrc)(m_pImpl->dllResource.GetSymbol(wxT("InitXrc")));
// 		pAPIFun();
// 	}

	wxInitAllImageHandlers();
	wxFileSystem::AddHandler(new wxArchiveFSHandler);

}




