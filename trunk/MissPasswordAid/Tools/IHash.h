#ifndef IHASH_H
#define IHASH_H


class IHash
{
    public:
        IHash() {}
        virtual ~IHash() {}

        /** \brief 计算哈希值
         *
         * \param szDataSrc const char* 待计算数据
         * \param nLenSrc short         待计算数据的长度
         * \param szDataDes char*       输出计算结果
         * \param nLenDes short&        计算结果的长度（in:szDataDes缓冲区长度，out:实际计算结果长度）
         * \return virtual bool         是否计算成功
         *
         */
        virtual bool ProcessMessage(const char* szDataSrc, short nLenSrc, char* szDataDes, short &nLenDes) = 0;

    protected:

    private:
};

#endif // IHASH_H
