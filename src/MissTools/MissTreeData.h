#ifndef DEF_TREEDATA_H__
#define DEF_TREEDATA_H__

#include "MissGlobal.h"
#include <vector>


class DLL_EXPORT TreeData
{
	class Impl;
public:
    TreeData();
    virtual ~TreeData();

    void                AppendChild(TreeData* pChild);
    void                PrependChild(TreeData* pChild);
    void                RemoveChild(TreeData* pChild);
    void                InsertChildAf(TreeData* pChild, const TreeData* pAfterChild);
    void                InsertChildBf(TreeData* pChild, const TreeData* pBeforeChild);
    void                ModifyParent(TreeData* pParent);
    TreeData*           GetParent() const;
    const std::vector<TreeData*>& GetChilds() const;

    enum { Type, UserType = 19880324 };
    virtual int GetType() const {return Type; }

    bool                FindChild(const TreeData* pChild);
    TreeData*           GetChildBySn(int nSN);
    int                 GetSnInParent() const;

protected:
    void                Dismiss();
    void                AppendChildData(TreeData* pChild);
    void                PrependChildData(TreeData* pChild);
    void                RemoveChildData(TreeData* pChild);
    void                InsertChildDataBf(TreeData* pChild, const TreeData* pBeforeChild);
    void                InsertChildDataAf(TreeData* pChild, const TreeData* pAfterChild);
    void                SetParent(TreeData* pParent);

private:
	Impl*    m_pImpl;
};



template <class T> inline T treedata_cast(TreeData *item)
{
    return int(static_cast<T>(0)->Type) == int(TreeData::Type)
        || (item && int(static_cast<T>(0)->Type) == item->GetType()) ? static_cast<T>(item) : 0;
}


template <class T> inline T treedata_cast(const TreeData *item)
{
    return int(static_cast<T>(0)->Type) == int(TreeData::Type)
        || (item && int(static_cast<T>(0)->Type) == item->GetType()) ? static_cast<T>(item) : 0;
}


#endif // DEF_TREEDATA_H__
