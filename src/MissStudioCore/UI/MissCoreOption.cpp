#include "MissCoreOption.h"
#include "..\BLL\MissResManager.h"
#include "..\..\MissTools\MissZipReader.h"


class MissCoreOption::Impl
{
public:

};

MissCoreOption::MissCoreOption( wxWindow* parent )
: CoreOptionBase( parent )
, m_pImpl(new Impl)
{
	InitUI();
}

void MissCoreOption::InitUI()
{
	wxSize bookOptionImageSize(48, 48);
	wxImageList* bookOptionImages = new wxImageList( bookOptionImageSize.GetWidth(), bookOptionImageSize.GetHeight() );
	bookOption->AssignImageList( bookOptionImages );
	int bookOptionIndex = 0;

	std::tr1::shared_ptr<MissZipReader> ptRes = MissResManager::Instance().GetMainRes();
	std::tr1::shared_ptr<wxImage> ptImg = ptRes->LoadImage("Bitmap\\exec.png");
	if ( ptImg )
	{
		bookOptionImages->Add( ptImg->Scale( bookOptionImageSize.GetWidth(), bookOptionImageSize.GetHeight() ) );
		bookOption->SetPageImage( bookOptionIndex, bookOptionIndex );
		bookOptionIndex++;
	}

	 ptImg = ptRes->LoadImage("Bitmap\\kontact_todo.png");
	if ( ptImg )
	{
		bookOptionImages->Add( ptImg->Scale( bookOptionImageSize.GetWidth(), bookOptionImageSize.GetHeight() ) );
		bookOption->SetPageImage( bookOptionIndex, bookOptionIndex );
		bookOptionIndex++;
	}


}
