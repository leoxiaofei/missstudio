#ifndef MISSPLUGINTREELISTDATA_H
#define MISSPLUGINTREELISTDATA_H

#include <wx/treectrl.h>


class MissPluginTreeListData : public wxTreeItemData
{
public:
    MissPluginTreeListData(unsigned int nPluginIndex, unsigned int nFuncIndex);
    virtual ~MissPluginTreeListData();
    unsigned int GetPluginIndex();
    unsigned int GetFuncIndex();
protected:
private:
    unsigned int m_nPluginIndex;
    unsigned int m_nFuncIndex;
};

#endif // MISSPLUGINTREELISTDATA_H
