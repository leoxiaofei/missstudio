#include "MissSha1.h"
#include <memory.h>

///常量
/**
K(t) = 0x5A827999 ( 0 <= t <= 19)
K(t) = 0x6ED9EBA1 (20 <= t <= 39)
K(t) = 0x8F1BBCDC (40 <= t <= 59)
K(t) = 0xCA62C1D6 (60 <= t <= 79)
*/

const unsigned int K[]=
{
    0x5A827999,
    0x6ED9EBA1,
    0x8F1BBCDC,
    0xCA62C1D6
};

///

///函数
/**
ft (B,C,D) = (B AND C) or ((NOT B) AND D)        ( 0 <= t <= 19)
ft (B,C,D) = B XOR C XOR D                       (20 <= t <= 39)
ft (B,C,D) = (B AND C) or (B AND D) or (C AND D) (40 <= t <= 59)
ft (B,C,D) = B XOR C XOR D                       (60 <= t <= 79)
*/

unsigned int f0( unsigned int B, unsigned int C, unsigned int D )
{
    return ((B & C) | ((~B) & D));
}

unsigned int f1( unsigned int B, unsigned int C, unsigned int D )
{
    return (B ^ C ^ D);
}

unsigned int f2( unsigned int B, unsigned int C, unsigned int D )
{
    return ((B & C) | (B & D) | (C & D));
}

unsigned int f3( unsigned int B, unsigned int C, unsigned int D )
{
    return (B ^ C ^ D);
}

typedef unsigned int (*pFUNC)(unsigned int B, unsigned int C, unsigned int D );
pFUNC pFunc[] = {&f0,&f1,&f2,&f3};

///

unsigned int SHA1CircularShift( unsigned int bits, unsigned int word )
{
    return ((((word) << (bits)) & 0xFFFFFFFF) | ((word) >> (32-(bits))));
}


MissSha1::MissSha1()
{
    //ctor
}

MissSha1::~MissSha1()
{
    //dtor
}

bool MissSha1::ProcessMessage(const char* szDataSrc, short nLenSrc, char* szDataDes, short &nLenDes)
{
    unsigned int A,B,C,D,E;
    unsigned int nszResult[5];
    unsigned int nszBuffer[80];
    unsigned int nTemp;

    if((unsigned short)nLenDes < sizeof(nszResult))
    {
        ///缓冲区太小
        return false;
    }
    nLenDes = sizeof(nszResult);

    MessageBlock mbLastMessBlock;
    InitResult(nszResult);
    FillLastMessageBlock(mbLastMessBlock, nLenSrc, szDataSrc);

    MessageBlock *pMessBlock(0);
    int nGCount = nLenSrc / 512;
    for(int nGroup = 0; nGroup <= nGCount; ++nGroup)
    {
        if(nGCount == nGroup)
        {
            pMessBlock = &mbLastMessBlock;
        }
        else
        {
            pMessBlock = (MessageBlock*)(&szDataSrc[nGroup*512]);
        }

        ///开始处理
        ///第一步
        for(int t = 0; t < 16; t++)
        {
        nszBuffer[t]  = pMessBlock->cData[t * 4]     << 24;
        nszBuffer[t] |= pMessBlock->cData[t * 4 + 1] << 16;
        nszBuffer[t] |= pMessBlock->cData[t * 4 + 2] << 8;
        nszBuffer[t] |= pMessBlock->cData[t * 4 + 3];
        }

        ///第二步
        for(int t = 16; t < 80; ++t)
        {
            nszBuffer[t] = SHA1CircularShift(1, nszBuffer[t-3] ^ nszBuffer[t-8] ^ nszBuffer[t-14] ^ nszBuffer[t-16]);
        }

        ///第三步
        A = nszResult[0];
        B = nszResult[1];
        C = nszResult[2];
        D = nszResult[3];
        E = nszResult[4];

        ///第四步
        int nOrder(0);
        for(int t = 0; t < 80; ++t)
        {
            nOrder = t / 20;
            nTemp = SHA1CircularShift(5,A) + pFunc[nOrder](B,C,D) + E + nszBuffer[t] + K[nOrder];
            E = D;
            D = C;
            C = SHA1CircularShift(30,B);
            B = A;
            A = nTemp;
        }

        ///第五步
        nszResult[0] += A;
        nszResult[1] += B;
        nszResult[2] += C;
        nszResult[3] += D;
        nszResult[4] += E;
    }

    ///逆序输出
    for(int ix = 0; ix < 5; ++ix)
    {
        szDataDes[ix*4]   = (nszResult[ix] >> 24) & 0xFF;
        szDataDes[ix*4+1] = (nszResult[ix] >> 16) & 0xFF;
        szDataDes[ix*4+2] = (nszResult[ix] >> 8)  & 0xFF;
        szDataDes[ix*4+3] = (nszResult[ix])       & 0xFF;
    }
    //memcpy(szDataDes, nszResult, nLenDes);
    return true;
}

void MissSha1::InitResult(unsigned int nszResult[5])
{
    ///初始化
    nszResult[0] = 0x67452301;
    nszResult[1] = 0xEFCDAB89;
    nszResult[2] = 0x98BADCFE;
    nszResult[3] = 0x10325476;
    nszResult[4] = 0xC3D2E1F0;
}

void MissSha1::FillLastMessageBlock(MessageBlock& mbLastMessBlock, int nLen, const char *szDataSrc)
{
    ///初始化消息块
    memset(&mbLastMessBlock, 0, sizeof(MessageBlock));

    ///计算补位
    unsigned int nLenRemainder = nLen % 512;
    memcpy(&mbLastMessBlock, &szDataSrc[nLen - nLenRemainder], nLenRemainder);
    mbLastMessBlock.cData[nLenRemainder] = 0x80;
    //mbLastMessBlock.uData[14] = 0; ///这个是预留长度扩展用的。
    //mbLastMessBlock.uData[15] = nLen*8;
    ///填充长度信息
    long long nLenBit = nLen * 8;

    mbLastMessBlock.cData[56]= (nLenBit >> 56) & 0xFF;
    mbLastMessBlock.cData[57]= (nLenBit >> 48) & 0xFF;
    mbLastMessBlock.cData[58]= (nLenBit >> 40) & 0xFF;
    mbLastMessBlock.cData[59]= (nLenBit >> 32) & 0xFF;

    mbLastMessBlock.cData[60]= (nLenBit >> 24) & 0xFF;
    mbLastMessBlock.cData[61]= (nLenBit >> 16) & 0xFF;
    mbLastMessBlock.cData[62]= (nLenBit >> 8)  & 0xFF;
    mbLastMessBlock.cData[63]= (nLenBit)       & 0xFF;
    ///
}
