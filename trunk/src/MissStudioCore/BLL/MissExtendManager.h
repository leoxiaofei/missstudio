#ifndef MISSEXTENDMANAGER_H__
#define MISSEXTENDMANAGER_H__

#include <memory>

class MissExtendManager
{
    class Impl;

public:
    static MissExtendManager& Instance()
    {
        static MissExtendManager theSingleton;
        return theSingleton;
    }

public:
    void LoadPlugin();

private:
    MissExtendManager();
    ~MissExtendManager();
    MissExtendManager(const MissExtendManager&);
    MissExtendManager& operator=(const MissExtendManager&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSEXTENDMANAGER_H__
