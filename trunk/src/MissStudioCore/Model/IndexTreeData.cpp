#include "IndexTreeData.h"
#include <assert.h>


IndexTreeData::IndexTreeData(unsigned int nSize)
: TreeData()
, vecData(nSize)
{
}


IndexTreeData::~IndexTreeData(void)
{
}

int& IndexTreeData::operator[]( unsigned int eType )
{
    assert(eType < vecData.size());
    return vecData[eType];
}

unsigned int IndexTreeData::IndexSize() const
{
    return vecData.size();
}
