#ifndef MISSCORECONFIG_H__
#define MISSCORECONFIG_H__

class MissCoreConfig
{
public:
    static MissCoreConfig& Instance()
    {
        static MissCoreConfig theSingleton;
        return theSingleton;
    }

    void Init();

    //PCD_TYPE GetPcdType() const;

protected:


private:
    MissCoreConfig();
    ~MissCoreConfig();
    MissCoreConfig(const MissCoreConfig&);
    MissCoreConfig& operator=(const MissCoreConfig&);

};


#endif // MISSCORECONFIG_H__
