#ifndef MISSWIDGETSDAL_H
#define MISSWIDGETSDAL_H


#include <memory>


enum DB_TYPE
{
	DT_CORECONFIG,
	DT_WIDGETS,
	DT_TASKDATA,

};

class MissDbBase;

class MissDAL
{
    class Impl;

public:
    static MissDAL& Instance()
    {
        static MissDAL theSingleton;
        return theSingleton;
    }

	template<class T>
	std::tr1::shared_ptr<T> QueryIF(DB_TYPE eType)
	{
		return std::tr1::dynamic_pointer_cast<T>(GetDbPtr(eType));
	}


	void VacuumDB();

protected:
	std::tr1::shared_ptr<MissDbBase> GetDbPtr(DB_TYPE eType);
	
private:
    MissDAL();
    ~MissDAL();
    MissDAL(const MissDAL&);
    MissDAL& operator=(const MissDAL&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSWIDGETSDAL_H
