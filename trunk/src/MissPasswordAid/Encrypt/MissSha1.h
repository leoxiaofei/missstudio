#ifndef MISSSHA1_H
#define MISSSHA1_H

#include "IHash.h"


class MissSha1 : public IHash
{
    public:
        MissSha1();
        virtual ~MissSha1();

        bool ProcessMessage(const char* szDataSrc, short nLenSrc, char* szDataDes, short &nLenDes);

        union MessageBlock
        {
            unsigned char cData[64];
            unsigned int  uData[16];
        };

    protected:
        void InitResult(unsigned int nResult[5]);
        void FillLastMessageBlock(MessageBlock& mb, int nLen, const char *szDataSrc);

    private:
};

#endif // MISSSHA1_H
