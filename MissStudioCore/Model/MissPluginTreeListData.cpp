#include "MissPluginTreeListData.h"

MissPluginTreeListData::MissPluginTreeListData(
    unsigned int nPluginIndex, unsigned int nFuncIndex)
    : m_nPluginIndex(nPluginIndex)
    , m_nFuncIndex(nFuncIndex)
{
    //ctor
}

MissPluginTreeListData::~MissPluginTreeListData()
{
    //dtor
}

unsigned int MissPluginTreeListData::GetPluginIndex()
{
    return m_nPluginIndex;
}

unsigned int MissPluginTreeListData::GetFuncIndex()
{
    return m_nFuncIndex;
}
