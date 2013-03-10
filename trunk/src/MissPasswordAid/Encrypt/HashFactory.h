#ifndef HASHFACTORY_H
#define HASHFACTORY_H

class IHash;

/** \brief 散列算法工厂
 */
class HashFactory
{
    public:
        enum HashType {MD5,SHA1};

        /** \brief 根据散列类型 创建散列算法
         *
         * \param eType HashType 散列类型 （目前只支持SHA1）
         * \return IHash*        返回创建好的散列对象（需要自行销毁）
         *
         */
        static IHash* CreateHash(HashType eType);

    protected:
    private:
};

#endif // HASHFACTORY_H
