#include "MissHotKeyModel.h"

#include "IndexTreeData.h"
#include "MissAPI\plugin\MissHotKeyFuncBase.h"
#include "..\BLL\MissHotKeyManager.h"

#include <vector>
#include <wx\dataview.h>
#include "..\..\..\include\MissAPI\plugin\MissPluginBase.h"


MissHotKeyModel::MissHotKeyModel(void)
: wxDataViewModel()
{
    LoadData();
}


MissHotKeyModel::~MissHotKeyModel(void)
{
}

unsigned int MissHotKeyModel::GetColumnCount() const
{
    return 4;
}

wxString MissHotKeyModel::GetColumnType( unsigned int col ) const
{
    wxString strRet;
    switch (col)
    {
    case 3:
        strRet = wxT("bool");
        break;
    default:
        strRet = wxT("string");
        break;
    }
    return strRet;
}

void MissHotKeyModel::GetValue( wxVariant &variant, const wxDataViewItem &item, unsigned int col ) const
{
    if (item.IsOk())
    {
        IndexTreeData& data = (*static_cast<IndexTreeData*>(item.GetID()));
        std::vector<HotKeyRelation>& vecRelation = MissHotKeyManager::Instance().GetHotKeyRelation();
        int nSize = data.IndexSize();
        if (nSize > 1)
        {
            const SHotKeyMajor& hotKeyMajor = vecRelation[data[NT_RELATION_INDEX]].mapIdToMajor[data[NT_HOTKEY_ID]];
            switch (col)
            {
            case 0:
                {
                    wxString strName;
                    vecRelation[data[NT_RELATION_INDEX]].pHotKeyFunc->GetHotKeyName(hotKeyMajor.nFuncId, strName);
                    variant = strName;
                }
                break;
            case 1:
                {
                    wxString strDesc;
                    vecRelation[data[NT_RELATION_INDEX]].pHotKeyFunc->GetHotkeyDesc(hotKeyMajor.nFuncId, strDesc);
                    variant = strDesc;
                }
                break;
            case 2:
                variant = hotKeyMajor.strHotKey;
                break;
            case 3:
                variant = hotKeyMajor.bEnable /*? wxT("已启用") : wxT("未启用")*/;
                break;
            default:
                break;
            }
        }
        else
        {
            if (col == 0)
            {
                MissPluginBase* pBase = MissHotKeyManager::Instance().
                    GetPluginBase(vecRelation[data[NT_RELATION_INDEX]].pHotKeyFunc);
                variant = pBase->GetPluginName();
            }
            else if(col == 3)
            {
                variant = false;
            }
        }
        
    }
}

bool MissHotKeyModel::SetValue( const wxVariant &variant, const wxDataViewItem &item, unsigned int col )
{
    bool bRet(false);
    if (item.IsOk())
    {
        IndexTreeData& data = (*static_cast<IndexTreeData*>(item.GetID()));
        if (data.IndexSize() > 1 )
        {
            std::vector<HotKeyRelation>& vecRelation = MissHotKeyManager::Instance().GetHotKeyRelation();
            SHotKeyMajor hotKeyMajor = vecRelation[data[NT_RELATION_INDEX]].mapIdToMajor[data[NT_HOTKEY_ID]];
            switch (col)
            {
            case 2:
                hotKeyMajor.strHotKey = variant.GetString();
                bRet = MissHotKeyManager::Instance().ModifyHotKey(data[NT_RELATION_INDEX],data[NT_HOTKEY_ID], hotKeyMajor);
                break;
            case 3:
                hotKeyMajor.bEnable = variant.GetBool();
                bRet = MissHotKeyManager::Instance().ModifyHotKey(data[NT_RELATION_INDEX],data[NT_HOTKEY_ID], hotKeyMajor);
                break;
            default:
                break;
            }
        }
    }
    return bRet;
}

wxDataViewItem MissHotKeyModel::GetParent( const wxDataViewItem &item ) const
{
    if (!item.IsOk())
    {
        return item;
    }
    return wxDataViewItem((void*)static_cast<IndexTreeData*>(item.GetID())->GetParent());
}

bool MissHotKeyModel::IsContainer( const wxDataViewItem &item ) const
{
    bool bRet(false);
    if (!item.IsOk())
    {
        ///根节点
        bRet = m_root && !(m_root->GetChilds().empty());
    }
    else
    {
        ///子节点
        bRet = !static_cast<IndexTreeData*>(item.GetID())->GetChilds().empty();
    }
    return bRet;
}

unsigned int MissHotKeyModel::GetChildren( const wxDataViewItem &item, wxDataViewItemArray &children ) const
{
    const std::vector<TreeData*>& vecChild = item.IsOk() 
        ? static_cast<IndexTreeData*>(item.GetID())->GetChilds() 
        : m_root->GetChilds();

    for (std::vector<TreeData*>::size_type ix = 0; ix != vecChild.size(); ++ix)
    {
        children.push_back(wxDataViewItem((void*)vecChild[ix]));
    }

    return vecChild.size();
}

void MissHotKeyModel::LoadData()
{
    std::vector<HotKeyRelation>& vecRelation = MissHotKeyManager::Instance().GetHotKeyRelation();
    m_root = std::tr1::shared_ptr<IndexTreeData>(new IndexTreeData);
    IndexTreeData* pRelation(NULL);
    IndexTreeData* pHotkeyID(NULL);
    for (int ix = 0; ix != vecRelation.size(); ++ix)
    {
        pRelation = new IndexTreeData;
        (*pRelation)[NT_RELATION_INDEX] = ix;
        for (std::map<unsigned int, SHotKeyMajor>::const_iterator citor = vecRelation[ix].mapIdToMajor.begin();
            citor != vecRelation[ix].mapIdToMajor.end(); ++citor)
        {
            pHotkeyID = new IndexTreeData;
            (*pHotkeyID)[NT_RELATION_INDEX] = ix;
            (*pHotkeyID)[NT_HOTKEY_ID] = citor->first;
            pRelation->AppendChild(pHotkeyID);
        }
        m_root->AppendChild(pRelation);
    }
}

bool MissHotKeyModel::GetIndexData( const wxDataViewItem &item, unsigned int& uRelationIndex, unsigned int& uHotkeyId ) const
{
    bool bRet(false);
    if (item.IsOk())
    {
        IndexTreeData& data = (*static_cast<IndexTreeData*>(item.GetID()));
        if (data.IndexSize() > 1)
        {
            uRelationIndex = data[NT_RELATION_INDEX];
            uHotkeyId      = data[NT_HOTKEY_ID];
            bRet = true;
        }
    }
    return bRet;
}
