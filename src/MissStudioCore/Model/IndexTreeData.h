#ifndef _INDEXTREEDATA_H__
#define _INDEXTREEDATA_H__

#include "MissTools\MissTreeData.h"


class IndexTreeData : public TreeData
{
public:
    IndexTreeData(void);
    virtual ~IndexTreeData(void);

    int& operator [] (unsigned int eType);
    unsigned int IndexSize() const;

private:
    std::vector<int> vecData;
};

#endif // _INDEXTREEDATA_H__
