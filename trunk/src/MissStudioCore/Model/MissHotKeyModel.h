#ifndef MISSHOTKEYMODEL_H__
#define MISSHOTKEYMODEL_H__

#include <wx\dataview.h>
#include <memory>

class IndexTreeData;

class MissHotKeyModel : public wxDataViewModel
{
public:
    MissHotKeyModel(void);
    ~MissHotKeyModel(void);

    virtual unsigned int GetColumnCount() const;
    virtual wxString GetColumnType( unsigned int col ) const;
    virtual void GetValue( wxVariant &variant, const wxDataViewItem &item, unsigned int col ) const;
    virtual bool SetValue( const wxVariant &variant, const wxDataViewItem &item, unsigned int col );
    virtual wxDataViewItem GetParent( const wxDataViewItem &item ) const;
    virtual bool IsContainer( const wxDataViewItem &item ) const;
    virtual unsigned int GetChildren( const wxDataViewItem &item, wxDataViewItemArray &children ) const;
    
    enum NodeType{NT_RELATION_INDEX, NT_HOTKEY_ID};

    void LoadData();
    bool GetIndexData(const wxDataViewItem &item, unsigned int& uRelationIndex, unsigned int& uHotkeyId) const;

private:
    std::tr1::shared_ptr<IndexTreeData> m_root;
};

#endif // MISSHOTKEYMODEL_H__
