#ifndef IMPLMISSSHAREDMEMORY_H__
#define IMPLMISSSHAREDMEMORY_H__

#include "MissAPI\interface\IMissSharedMemory.h"


class MissPluginBase;

class ImplMissSharedMemory : public IMissSharedMemory
{
    class Impl;
public:
    ImplMissSharedMemory(MissPluginBase* pPlugMain);
    ~ImplMissSharedMemory();

    virtual void RegSharedMemory( const wxString& strMemoryName, MissSharedMemoryBase* pPlugin );
    virtual void UnRegSharedMemory( const wxString& strMemoryName, MissSharedMemoryBase* pPlugin );

    virtual bool GetVariant( const wxString& strMemoryName, wxVariant& varData );
    virtual bool SetVariant( const wxString& strMemoryName, const wxVariant& varData );



private:
    MissPluginBase* m_pPlugMain;
};


#endif // IMPLMISSSHAREDMEMORY_H__
