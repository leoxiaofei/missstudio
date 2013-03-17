#ifndef MISSINSTALLEDMODEL_H__
#define MISSINSTALLEDMODEL_H__

#include <wx\dataview.h>
#include <memory>
#include "IndexTreeData.h"

class MissInstalledModel : public wxDataViewModel
{
public:
    MissInstalledModel();
    ~MissInstalledModel();

    virtual unsigned int GetColumnCount() const;
    virtual wxString GetColumnType( unsigned int col ) const;
    virtual void GetValue( wxVariant &variant, const wxDataViewItem &item, unsigned int col ) const;
    virtual bool SetValue( const wxVariant &variant, const wxDataViewItem &item, unsigned int col );
    virtual wxDataViewItem GetParent( const wxDataViewItem &item ) const;
    virtual bool IsContainer( const wxDataViewItem &item ) const;
    virtual unsigned int GetChildren( const wxDataViewItem &item, wxDataViewItemArray &children ) const;


    enum NodeType{NT_ROOT, NT_PLUGIN, NT_PLUGIN_WIDGET};
    enum NodeData{ND_RELATION_INDEX, ND_WIDGET_INDEX};

protected:
    void LoadData();

private:
    std::tr1::shared_ptr<IndexTreeData> m_root;

};


#endif // MISSINSTALLEDMODEL_H__
