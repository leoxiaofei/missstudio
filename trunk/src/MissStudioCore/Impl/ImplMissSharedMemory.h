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

    virtual void RegSharedMemory( MissSharedMemoryBase* pPlugin );
    virtual void UnRegSharedMemory( MissSharedMemoryBase* pPlugin );

    virtual bool operator = ( const wxVariant& varData ) ;
    virtual bool operator ()( wxVariant& varData );
    //     virtual bool GetSharedMemory( wxVariant& strMemory ) const;
//     virtual bool SetSharedMemory( const wxVariant& strMemory );

private:
    MissPluginBase* m_pPlugMain;
};


#endif // IMPLMISSSHAREDMEMORY_H__
