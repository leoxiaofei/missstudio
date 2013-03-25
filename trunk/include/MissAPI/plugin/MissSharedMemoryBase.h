#ifndef MISSSHAREDMEMORYBASE_H__
#define MISSSHAREDMEMORYBASE_H__

class MissSharedMemoryBase
{
public:
    virtual ~MissSharedMemoryBase(){};
    virtual MemoryChanged(const wxString& strMemory) = 0;

private:

};


#endif // MISSSHAREDMEMORYBASE_H__
