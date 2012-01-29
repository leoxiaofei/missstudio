#include "ProcPwCore.h"
#include <memory.h>
#include "../Tools/HashFactory.h"
#include "../Tools/IHash.h"

ProcPwCore::ProcPwCore(short nLen, short nEdition):
m_nLen(nLen),
m_nEdition(nEdition)
{
    //ctor
}

ProcPwCore::~ProcPwCore()
{
    //dtor
}

void ProcPwCore::SetOutLen(short nLen)
{
    m_nLen = nLen;
}

void ProcPwCore::SetEdition(short nEdition)
{
    m_nEdition = nEdition;
}

bool ProcPwCore::StartProc(const char* szDataSrc, short nLenSrc, char* szDataDes, short nLenDes)
{
    if(nLenDes < m_nLen)
    {
        ///输出缓冲区长度不够
        return false;
    }

    ///分配更多空间用来放长度信息
    char* szTemp = new char[nLenSrc + 1];
    memcpy(szTemp, szDataSrc, nLenSrc);
    szTemp[nLenSrc] = m_nLen;

    ///简单异或处理来产生不同的密码版本
    for(int ix = 0; ix <= nLenSrc; ++ix)
    {
        szTemp[ix] ^= m_nEdition;
    }

    ///做散列算法加密处理
    char szHashCache[20];
    short nHashLen(20);
    IHash *hTool = HashFactory::CreateHash(HashFactory::SHA1);
    hTool->ProcessMessage(szTemp, nLenSrc + 1, szHashCache, nHashLen);
    delete hTool; hTool = NULL;

    ///按所需密码长度，截取Hash值
    int nTemp(0);
    for(int ix = 0; ix < m_nLen; ++ix)
    {
        szDataDes[ix] = ConfuseChar(GetCharByHexInt((unsigned char)szHashCache[nTemp] % 16));
        if(++nTemp >= nHashLen)
        {
            nTemp = 0;
        }
    }

    /*
    ///按所需密码长度，截取Hash值
    char szHexTemp[2];
    int nTemp(0);
    for(int ix = 0; ix < nHashLen; )
    {
        CharToHex(szHashCache[ix],szHexTemp);
        if(nTemp < m_nLen)
        {
            szDataDes[nTemp] = ConfuseChar(szHexTemp[0]);
        }
        else
        {
            break;
        }
        ++nTemp;

        if(nTemp < m_nLen)
        {
            szDataDes[nTemp] = ConfuseChar(szHexTemp[1]);
        }
        else
        {
            break;
        }
        ++nTemp;

        ++ix;
        if(ix >= nHashLen)
        {
            ix = 0;
        }
    }
    */
    return true;
}

bool ProcPwCore::CharToHex(char cSrc, char szDes[2])
{
    int nTemp(0);
    nTemp = (unsigned char)cSrc / 16;
    szDes[0] = GetCharByHexInt(nTemp);
    nTemp = (unsigned char)cSrc % 16;
    szDes[1] = GetCharByHexInt(nTemp);
    return true;
}

char ProcPwCore::GetCharByHexInt(int nSrc)
{
    if(nSrc >= 10)
    {
        return 'a' + nSrc - 10;
    }
    else
    {
        return '0' + nSrc;
    }
}

char ProcPwCore::ConfuseChar(char cSrc)
{
    char cRet(cSrc);
    switch(cSrc)
    {
    case '6':
        cRet = '!';
        break;
    case '7':
        cRet = '@';
        break;
    case '8':
        cRet = '#';
        break;
    case '9':
        cRet = '$';
        break;
    case '0':
        cRet = '%';
        break;
    }
    return cRet;
}
