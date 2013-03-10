#ifndef MISSFUNCTOR_H__
#define MISSFUNCTOR_H__

class MissPluginBase;

class PluginUnloader
{
public:
    void operator() (MissPluginBase* pPluginBase) const;

};


#endif // MissFunctor_h__
