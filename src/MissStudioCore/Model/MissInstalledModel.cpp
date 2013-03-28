#include "MissInstalledModel.h"

#include "MissAPI\plugin\MissPluginBase.h"
#include "MissAPI\plugin\MissWidgetFactoryBase.h"
#include "..\BLL\MissWidgetManager.h"

using std::vector;
using std::tr1::shared_ptr;

MissInstalledModel::MissInstalledModel()
{
    LoadData();
}

MissInstalledModel::~MissInstalledModel()
{

}

unsigned int MissInstalledModel::GetColumnCount() const
{
    return 1;
}

wxString MissInstalledModel::GetColumnType( unsigned int col ) const
{
//     wxString strRet;
//     switch (col)
//     {
//     default:
//         strRet = wxT("string");
//         break;
//     }
    return wxT("string");
}

void MissInstalledModel::GetValue( wxVariant &variant, const wxDataViewItem &item, unsigned int col ) const
{
    if (item.IsOk())
    {
        IndexTreeData& data = (*static_cast<IndexTreeData*>(item.GetID()));
        vector<shared_ptr<WidgetRelation> >& vecRelation = MissWidgetManager::Instance().GetWidgetData();
        int nSize = data.IndexSize();
        switch (nSize)
        {
        case NT_PLUGIN:
            if (col == 0)
            {
                MissPluginBase* pBase = MissWidgetManager::Instance().
                    GetPluginBase(vecRelation[data[ND_RELATION_INDEX]]->pFactory);
                variant = pBase->GetPluginName();
            }
            break;
        case NT_PLUGIN_WIDGET:
            {
                const SWidgetMajor& widgetMajor = vecRelation[data[ND_RELATION_INDEX]]->vecWidgetMajor[data[ND_WIDGET_INDEX]];
                switch (col)
                {
                case 0:
                    {
                        wxString strName;
                        vecRelation[data[ND_RELATION_INDEX]]->pFactory->GetWidgetName(widgetMajor.nWidgetId, strName);
                        variant = strName;
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        default:
            break;
        }
    }
}

bool MissInstalledModel::SetValue( const wxVariant &variant, const wxDataViewItem &item, unsigned int col )
{
    return false;
}

wxDataViewItem MissInstalledModel::GetParent( const wxDataViewItem &item ) const
{
    if (!item.IsOk())
    {
        return item;
    }
    return wxDataViewItem((void*)static_cast<IndexTreeData*>(item.GetID())->GetParent());
}

bool MissInstalledModel::IsContainer( const wxDataViewItem &item ) const
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

unsigned int MissInstalledModel::GetChildren( const wxDataViewItem &item, wxDataViewItemArray &children ) const
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

void MissInstalledModel::LoadData()
{
    vector<shared_ptr<WidgetRelation> >& vecRelation = MissWidgetManager::Instance().GetWidgetData();
    m_root = std::tr1::shared_ptr<IndexTreeData>(new IndexTreeData(NT_ROOT));
    IndexTreeData* pRelation(NULL);
    IndexTreeData* pHotkeyID(NULL);
    for (vector<shared_ptr<WidgetRelation> >::size_type ixRelation = 0; 
        ixRelation != vecRelation.size(); ++ixRelation)
    {
        pRelation = new IndexTreeData(NT_PLUGIN);
        (*pRelation)[ND_RELATION_INDEX] = ixRelation;
        for (WidgetMajorSet::size_type ixWidgetMajor = 0;
            ixWidgetMajor != vecRelation[ixRelation]->vecWidgetMajor.size(); ++ixWidgetMajor)
        {
            pHotkeyID = new IndexTreeData(NT_PLUGIN_WIDGET);
            (*pHotkeyID)[ND_RELATION_INDEX] = ixRelation;
            (*pHotkeyID)[ND_WIDGET_INDEX] = ixWidgetMajor;
            pRelation->AppendChild(pHotkeyID);
        }
        m_root->AppendChild(pRelation);
    }
}

bool MissInstalledModel::GetDataByItem( const wxDataViewItem &item, MissWidgetFactoryBase*& pBase, int& nWigetId ) const
{
    bool bRet(false);
    if (item.IsOk())
    {
        IndexTreeData* pTreeData = static_cast<IndexTreeData*>(item.GetID());
        if (pTreeData->IndexSize() == NT_PLUGIN_WIDGET)
        {
            vector<shared_ptr<WidgetRelation> >& vecRelation = MissWidgetManager::Instance().GetWidgetData();
            pBase    = vecRelation[(*pTreeData)[ND_RELATION_INDEX]]->pFactory;
            nWigetId = vecRelation[(*pTreeData)[ND_RELATION_INDEX]]->vecWidgetMajor[(*pTreeData)[ND_WIDGET_INDEX]].nWidgetId;
            bRet = true;
        }

    }
    return bRet;
}

