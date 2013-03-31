#ifndef MISSSHAREDMEMORYBASE_H__
#define MISSSHAREDMEMORYBASE_H__

class MissSharedMemoryBase
{
public:
    virtual ~MissSharedMemoryBase(){};
    virtual void MemoryChanged(const wxVariant& vMemory) = 0;

private:

};


#endif // MISSSHAREDMEMORYBASE_H__
