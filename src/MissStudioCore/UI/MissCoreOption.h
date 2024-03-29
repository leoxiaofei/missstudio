﻿#ifndef __MissCoreOption__
#define __MissCoreOption__

/**
@file
Subclass of CoreOptionBase, which is generated by wxFormBuilder.
*/

#include "../Generated/GUIFrame.h"
#include <memory>

//// end generated include

/** Implementing CoreOptionBase */
class MissCoreOption : public CoreOptionBase
{
	class Impl;
	public:
		/** Constructor */
		MissCoreOption( wxWindow* parent );
	//// end generated class members
	
protected:
	void InitUI();

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // __MissCoreOption__
