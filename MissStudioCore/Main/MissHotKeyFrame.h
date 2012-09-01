#ifndef __MissHotKeyFrame__
#define __MissHotKeyFrame__

/**
@file
Subclass of MissHotKeyFrameBase, which is generated by wxFormBuilder.
*/

#include "../Generated/GUIFrame.h"

//// end generated include

/** Implementing MissHotKeyFrameBase */
class MissHotKeyFrame : public MissHotKeyFrameBase
{
    class MissHotKeyFrameImpl;
public:
    /** Constructor */
    MissHotKeyFrame( wxWindow* parent);

    virtual void OnHotKeyTreeItemActivated( wxTreeEvent& event );
    //// end generated class members
protected:
    void InitUI();

private:
    shared_ptr<MissHotKeyFrameImpl> m_pImpl;
};

#endif // __MissHotKeyFrame__