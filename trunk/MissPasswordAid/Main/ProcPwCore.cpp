#include "ProcPwCore.h"
#include <memory.h>
#include "../Tools/HashFactory.h"
#include "../Tools/IHash.h"
#include <algorithm>

ProcPwCore::ProcPwCore(short nLen, short nEdition, PWTYPE eType)
: m_nLen(nLen)
, m_nEdition(nEdition)
, m_eType(eType)
{
    //ctor
}

ProcPwCore::~ProcPwCore()
{
    //dtor
}

int ProcPwCore::InitConfuse()
{
    int nRet(0);
    switch(m_eType)
    {
    case PW_HAS1_STANDARD:
        m_szConfuse[0] = ConfuseLower;
        m_szConfuse[1] = ConfuseUpper;
        m_szConfuse[2] = ConfuseNumericFront;
        m_szConfuse[3] = ConfuseAdditional;
        nRet           = 4;
        break;
    case PW_HAS1_NUMERIC:
        m_szConfuse[0] = ConfuseNumeric;
        nRet           = 1;
        break;
    default:
        break;
    }
    return nRet;
    /*
    m_vecConfuse.clear();
    m_vecConfuse.push_back(ConfuseLower);
    m_vecConfuse.push_back(ConfuseUpper);
    m_vecConfuse.push_back(ConfuseNumeric);
    m_vecConfuse.push_back(ConfuseAdditional);
    */
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

    ///准备加密器
    int nConfuseCount = InitConfuse();
    short nCount = szHashCache[19] % 24;
    while(nCount)
    {
        std::next_permutation(m_szConfuse, m_szConfuse+nConfuseCount);
        --nCount;
    }

    ///按所需密码长度，截取Hash值
    int nTemp(0);
    for(int ix = 0; ix < m_nLen; ++ix)
    {
        szDataDes[ix] = m_szConfuse[ix % nConfuseCount]((unsigned char)szHashCache[nTemp]);
        if(++nTemp >= nHashLen)
        {
            nTemp = 0;
        }
    }

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

char ProcPwCore::ConfuseLower(unsigned char cSrc)
{
    cSrc %= 6;
    return 'a' + cSrc;
}

char ProcPwCore::ConfuseUpper(unsigned char cSrc)
{
    cSrc %= 6;
    return 'A' + cSrc;
}

char ProcPwCore::ConfuseNumericFront(unsigned char cSrc)
{
    cSrc %= 5;
    return '1' + cSrc;
}

char ProcPwCore::ConfuseNumeric(unsigned char cSrc)
{
    cSrc %= 10;
    return '0' + cSrc;
}

const char ProcPwCore::s_szAdditional[] = {'!','@','#','$','%'};

char ProcPwCore::ConfuseAdditional(unsigned char cSrc)
{
    int nSrc = cSrc % 5;
    return s_szAdditional[nSrc];
}
