#ifndef PROCPWCORE_H
#define PROCPWCORE_H


class ProcPwCore
{
    public:
        ProcPwCore(short nLen = 8, short nEdition = 1);
        virtual ~ProcPwCore();

        /** \brief 设置输出密码的长度
         *
         * \param nLen int 输出密码的长度
         * \return void
         *
         */
        void SetOutLen(short nLen);

        /** \brief 设置输出密码的版本
         *
         * \param nEdition int 输出密码的版本
         * \return void
         *
         */
        void SetEdition(short nEdition);

        /** \brief 开始处理密码
         *
         * \param szDataSrc const char*  数据源
         * \param nLenSrc short          数据源长度
         * \param szDataDes char*        输出缓冲区
         * \param nLenDes short          输出缓冲区长度
         * \return bool                  是否处理成功
         *
         */
        bool StartProc(const char* szDataSrc, short nLenSrc, char* szDataDes, short nLenDes);

    protected:
        /** \brief 将一个字节转为十六进制字符串（2个字节）
         *
         * \param cSrc char       待转字符
         * \param szDes[2] char   输出字符串
         * \return bool           是否处理成功（未处理）
         *
         */
        bool CharToHex(char cSrc,char szDes[2]);

        /** \brief 十进制（0~16）变为16进制字符(0~f)
         *
         * \param nSrc int    待转十进制数(0~16)
         * \return char       输出16进制数(0~f)
         *
         */
        char GetCharByHexInt(int nSrc);

        /** \brief 字符混淆处理
         *
         * \param cSrc char    待混淆字符
         * \return char        输出混淆后的字符
         *
         */
        char ConfuseChar(char cSrc);

    private:
        short m_nLen;       /**< 输出密码的长度 */
        short m_nEdition;   /**< 密码版本 */
};

#endif // PROCPWCORE_H
