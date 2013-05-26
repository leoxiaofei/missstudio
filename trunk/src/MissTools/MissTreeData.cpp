#include "MissTreeData.h"
#include <assert.h>
#include <algorithm>

class TreeData::Impl
{
public:
	std::vector<TreeData*>   vecChilds;
	TreeData*                pParent;
};

TreeData::TreeData()
: m_pImpl(new Impl)
{
	m_pImpl->pParent = NULL;
}

TreeData::~TreeData()
{
    Dismiss();
    std::vector<TreeData*> vecChilds = GetChilds();
    for (int ix = 0; ix != vecChilds.size(); ++ix)
    {
        delete vecChilds[ix];
    }
	delete m_pImpl;
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
    return m_pImpl->pParent;
}


const std::vector<TreeData*>& TreeData::GetChilds() const
{
    return m_pImpl->vecChilds;
}


void TreeData::Dismiss()
{
    if (m_pImpl->pParent)
    {
        m_pImpl->pParent->RemoveChildData(this);
        m_pImpl->pParent = NULL;
    }
}

void TreeData::AppendChildData( TreeData* pChild )
{
    RemoveChildData( pChild );
    m_pImpl->vecChilds.push_back(pChild);
}

void TreeData::PrependChildData( TreeData* pChild )
{
    RemoveChildData( pChild );
    m_pImpl->vecChilds.insert(m_pImpl->vecChilds.begin(), pChild);
}

void TreeData::RemoveChildData( TreeData* pChild )
{
    std::vector<TreeData*>::iterator iFind = std::find(m_pImpl->vecChilds.begin(), m_pImpl->vecChilds.end(), pChild);
    if(iFind != m_pImpl->vecChilds.end())
    {
        m_pImpl->vecChilds.erase(iFind);
    }
}

void TreeData::InsertChildDataAf( TreeData* pChild, const TreeData* pAfterChild )
{
    RemoveChildData( pChild );
    std::vector<TreeData*>::iterator iFind = std::find(m_pImpl->vecChilds.begin(), m_pImpl->vecChilds.end(), pAfterChild);
    if (iFind != m_pImpl->vecChilds.end())
    {
        ++iFind;
    }
    m_pImpl->vecChilds.insert(iFind, pChild);
}

void TreeData::InsertChildDataBf( TreeData* pChild, const TreeData* pBeforeChild )
{
    RemoveChildData( pChild );
    std::vector<TreeData*>::iterator iFind = std::find(m_pImpl->vecChilds.begin(), m_pImpl->vecChilds.end(), pBeforeChild);
    m_pImpl->vecChilds.insert(iFind, pChild);
}



void TreeData::SetParent( TreeData* pParent )
{
    if (m_pImpl->pParent != pParent)
    {
        Dismiss();
        m_pImpl->pParent = pParent;
    }
}

// void TreeData::SetName( const QString& strName )
// {
//     m_pImpl->strName = strName;
// }

bool TreeData::FindChild( const TreeData* pChild )
{
    std::vector<TreeData*>::iterator iFind = std::find(m_pImpl->vecChilds.begin(), m_pImpl->vecChilds.end(), pChild);
    return (iFind != m_pImpl->vecChilds.end());
}

// void TreeData::SetData( const QString& strData )
// {
//     m_pImpl->strData = strData;
// }

TreeData* TreeData::GetChildBySn( int nSN )
{
    //Q_ASSERT(nSN < m_pImpl->vecChilds.size() && nSN > -1);
    TreeData* pRet(NULL);
    if ((std::vector<TreeData*>::size_type)nSN < m_pImpl->vecChilds.size() )
    {
        pRet = m_pImpl->vecChilds[nSN];
    }
    return pRet;
}

int TreeData::GetSnInParent() const
{
    int nRet(0);
    if (m_pImpl->pParent)
    {
        const std::vector<TreeData*>& vecBrother = m_pImpl->pParent->GetChilds();
        std::vector<TreeData*>::const_iterator iFind = std::find(vecBrother.begin(), vecBrother.end(), this);
        if (iFind != vecBrother.end())
        {
            nRet = iFind - vecBrother.begin();
        }
    }
    return nRet;
}