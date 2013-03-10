#include "IndexTreeData.h"
#include <assert.h>


IndexTreeData::IndexTreeData(void)
: TreeData()
{
}


IndexTreeData::~IndexTreeData(void)
{
}

int& IndexTreeData::operator[]( unsigned int eType )
{
    assert(eType < 1000);
    if (eType >= vecData.size())
    {
        vecData.resize(eType + 1);
    }
    return vecData[eType];
}

unsigned int IndexTreeData::IndexSize() const
{
    return vecData.size();
}
