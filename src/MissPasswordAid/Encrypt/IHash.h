#ifndef IHASH_H
#define IHASH_H


class IHash
{
    public:
        IHash() {}
        virtual ~IHash() {}

        /** \brief �����ϣֵ
         *
         * \param szDataSrc const char* ����������
         * \param nLenSrc short         ���������ݵĳ���
         * \param szDataDes char*       ���������
         * \param nLenDes short&        �������ĳ��ȣ�in:szDataDes���������ȣ�out:ʵ�ʼ��������ȣ�
         * \return virtual bool         �Ƿ����ɹ�
         *
         */
        virtual bool ProcessMessage(const char* szDataSrc, short nLenSrc, char* szDataDes, short &nLenDes) = 0;

    protected:

    private:
};

#endif // IHASH_H
