#include "MissTreeData.h"
#include <assert.h>


TreeData::TreeData()
: m_pParent(NULL)
{

}

TreeData::~TreeData()
{
    Dismiss();
    std::vector<TreeData*> vecChilds = GetChilds();
    for (int ix = 0; ix != vecChilds.size(); ++ix)
    {
        delete vecChilds[ix];
    }
//     static int nCount = 0;
//     qDebug()<<++nCount;
}

void TreeData::AppendChild( TreeData* pChild )
{
    assert(this != pChild);
    pChild->SetParent(this);
    AppendChildData(pChild);
}

void TreeData::PrependChild( TreeData* pChild )
{
    assert(this != pChild);
    pChild->SetParent(this);
    PrependChildData(pChild);
}

void TreeData::InsertChildAf( TreeData* pChild, const TreeData* pAfterChild )
{
    pChild->SetParent(this);
    InsertChildDataAf(pChild, pAfterChild);
}

void TreeData::InsertChildBf( TreeData* pChild, const TreeData* pBeforeChild )
{
    pChild->SetParent(this);
    InsertChildDataBf(pChild, pBeforeChild);
}

void TreeData::RemoveChild( TreeData* pChild )
{
    pChild->Dismiss();
}

void TreeData::ModifyParent( TreeData* pParent )
{
    assert(this != pParent);
    SetParent(pParent);
    if (pParent)
    {
        pParent->AppendChildData(this);
    }
}

TreeData* TreeData::GetParent() const
{
    return m_pParent;
}


const std::vector<TreeData*>& TreeData::GetChilds() const
{
    return m_vecChilds;
}


void TreeData::Dismiss()
{
    if (m_pParent)
    {
        m_pParent->RemoveChildData(this);
        m_pParent = NULL;
    }
}

void TreeData::AppendChildData( TreeData* pChild )
{
    RemoveChildData( pChild );
    m_vecChilds.push_back(pChild);
}

void TreeData::PrependChildData( TreeData* pChild )
{
    RemoveChildData( pChild );
    m_vecChilds.insert(m_vecChilds.begin(), pChild);
}

void TreeData::RemoveChildData( TreeData* pChild )
{
    std::vector<TreeData*>::iterator iFind = std::find(m_vecChilds.begin(), m_vecChilds.end(), pChild);
    if(iFind != m_vecChilds.end())
    {
        m_vecChilds.erase(iFind);
    }
}

void TreeData::InsertChildDataAf( TreeData* pChild, const TreeData* pAfterChild )
{
    RemoveChildData( pChild );
    std::vector<TreeData*>::iterator iFind = std::find(m_vecChilds.begin(), m_vecChilds.end(), pAfterChild);
    if (iFind != m_vecChilds.end())
    {
        ++iFind;
    }
    m_vecChilds.insert(iFind, pChild);
}

void TreeData::InsertChildDataBf( TreeData* pChild, const TreeData* pBeforeChild )
{
    RemoveChildData( pChild );
    std::vector<TreeData*>::iterator iFind = std::find(m_vecChilds.begin(), m_vecChilds.end(), pBeforeChild);
    m_vecChilds.insert(iFind, pChild);
}



void TreeData::SetParent( TreeData* pParent )
{
    if (m_pParent != pParent)
    {
        Dismiss();
        m_pParent = pParent;
    }
}

// void TreeData::SetName( const QString& strName )
// {
//     m_strName = strName;
// }

bool TreeData::FindChild( const TreeData* pChild )
{
    std::vector<TreeData*>::iterator iFind = std::find(m_vecChilds.begin(), m_vecChilds.end(), pChild);
    return (iFind != m_vecChilds.end());
}

// void TreeData::SetData( const QString& strData )
// {
//     m_strData = strData;
// }

TreeData* TreeData::GetChildBySn( int nSN )
{
    //Q_ASSERT(nSN < m_vecChilds.size() && nSN > -1);
    TreeData* pRet(NULL);
    if ((std::vector<TreeData*>::size_type)nSN < m_vecChilds.size() )
    {
        pRet = m_vecChilds[nSN];
    }
    return pRet;
}

int TreeData::GetSnInParent() const
{
    int nRet(0);
    if (m_pParent)
    {
        const std::vector<TreeData*>& vecBrother = m_pParent->GetChilds();
        std::vector<TreeData*>::const_iterator iFind = std::find(vecBrother.begin(), vecBrother.end(), this);
        if (iFind != vecBrother.end())
        {
            nRet = iFind - vecBrother.begin();
        }
    }
    return nRet;
}