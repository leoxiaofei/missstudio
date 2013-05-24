#include "MissCoreConfig.h"
#include "..\Common\MissPaths.h"
#include "MissTools\MissConfigFile.h"


MissCoreConfig::MissCoreConfig()
{
}

MissCoreConfig::~MissCoreConfig()
{
}

void MissCoreConfig::Init()
{
    wxString strPath = MissPaths::Instance().GetDataBasePath() + wxT("Globle.ini");
    MissConfigFile config(strPath);
    long nPcdType = 0;
    if(config.Read(wxT("System//PathType"), nPcdType))
    {
        MissPaths::Instance().SetConfigDirType(nPcdType);
    }
    else
    {
        config.Write(wxT("System//PathType"), nPcdType);
    }
}
