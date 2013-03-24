#ifndef MISSRUNNINGMODEL_H__
#define MISSRUNNINGMODEL_H__


#include <wx\dataview.h>
#include <memory>
#include <vector>

class ImplMissWidget;

class MissRunningModel : public wxDataViewVirtualListModel  
{
public:
    MissRunningModel();
    ~MissRunningModel();

    virtual void GetValueByRow( wxVariant &variant, unsigned row, unsigned col ) const;
    virtual bool SetValueByRow( const wxVariant &variant, unsigned row, unsigned col );
    virtual unsigned int GetColumnCount() const;
    virtual wxString GetColumnType( unsigned int col ) const;

protected:

private:
    std::vector<std::tr1::shared_ptr<ImplMissWidget> >& m_vecRunning;
};

#endif // MISSRUNNINGMODEL_H__

