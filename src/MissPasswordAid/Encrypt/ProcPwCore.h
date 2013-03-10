#ifndef PROCPWCORE_H
#define PROCPWCORE_H

class ProcPwCore
{
    public:

        enum PWTYPE
        {
            PW_HAS1_STANDARD,
            PW_HAS1_NUMERIC
        };

        ProcPwCore(unsigned char uLen = 8, short nEdition = 1, PWTYPE eType = PW_HAS1_STANDARD);
        virtual ~ProcPwCore();

        /** \brief �����������ĳ���
         *
         * \param uLen unsigned char �������ĳ���
         * \return void
         *
         */
        void SetOutLen(unsigned char uLen);

        /** \brief �����������İ汾
         *
         * \param nEdition int �������İ汾
         * \return void
         *
         */
        void SetEdition(short nEdition);

        /** \brief ��ʼ��������
         *
         * \param szDataSrc const char*  ����Դ
         * \param nLenSrc short          ����Դ����
         * \param szDataDes char*        ���������
         * \param nLenDes short          �������������
         * \return bool                  �Ƿ���ɹ�
         *
         */
        bool StartProc(const char* szDataSrc, short nLenSrc, char* szDataDes, short nLenDes);

    protected:
        /** \brief ��һ���ֽ�תΪʮ�������ַ�����2���ֽڣ�
         *
         * \param cSrc char       ��ת�ַ�
         * \param szDes[2] char   ����ַ���
         * \return bool           �Ƿ���ɹ���δ����
         *
         */
        bool CharToHex(char cSrc,char szDes[2]);

        /** \brief ʮ���ƣ�0~16����Ϊ16�����ַ�(0~f)
         *
         * \param nSrc int    ��תʮ������(0~16)
         * \return char       ���16������(0~f)
         *
         */
        char GetCharByHexInt(int nSrc);

        /** \brief ��ʼ��������
         *
         * \return int ���ػ���������
         *
         */
        int InitConfuse();

        /** \brief �ַ���������
         *
         * \param cSrc char    �������ַ�
         * \return char        �����������ַ�
         *
         */
        static char ConfuseLower(unsigned char cSrc);
        static char ConfuseUpper(unsigned char cSrc);
        static char ConfuseNumericFront(unsigned char cSrc);
        static char ConfuseNumeric(unsigned char cSrc);
        static char ConfuseAdditional(unsigned char cSrc);

    private:
        unsigned char   m_uLen;       /**< �������ĳ��� */
        short           m_nEdition;   /**< ����汾 */
        PWTYPE          m_eType;      /**< �������� */

        static const char s_szAdditional[];
        typedef char (*ConfuseFun)(unsigned char);
        ConfuseFun m_szConfuse[4];
};

#endif // PROCPWCORE_H
