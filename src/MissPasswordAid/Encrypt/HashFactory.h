#ifndef HASHFACTORY_H
#define HASHFACTORY_H

class IHash;

/** \brief ɢ���㷨����
 */
class HashFactory
{
    public:
        enum HashType {MD5,SHA1};

        /** \brief ����ɢ������ ����ɢ���㷨
         *
         * \param eType HashType ɢ������ ��Ŀǰֻ֧��SHA1��
         * \return IHash*        ���ش����õ�ɢ�ж�����Ҫ�������٣�
         *
         */
        static IHash* CreateHash(HashType eType);

    protected:
    private:
};

#endif // HASHFACTORY_H
