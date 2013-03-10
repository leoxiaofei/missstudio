#include "HashFactory.h"
#include "MissSha1.h"

IHash* HashFactory::CreateHash(HashType eType)
{
    IHash *pRet(0);
    switch(eType)
    {
    case MD5:
        break;
    case SHA1:
        pRet = new MissSha1();
        break;
    }
    return pRet;
}
