#ifndef MISSRESMANAGER_H__
#define MISSRESMANAGER_H__

#include <memory>
class MissZipReader;

class MissResManager
{
	class Impl;
public:
	static MissResManager& Instance()
	{
		static MissResManager theSingleton;
		return theSingleton;
	}

	std::tr1::shared_ptr<MissZipReader> GetMainRes() const;

protected:

private:
	MissResManager();
	~MissResManager();
	MissResManager(const MissResManager&);
	MissResManager& operator=(const MissResManager&);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // MISSRESMANAGER_H__
