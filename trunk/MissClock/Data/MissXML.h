#ifndef MISSXML_H
#define MISSXML_H

class MissSkin;
class MissRemindSkin;

namespace MissXML
{
    bool SaveSkin(const MissSkin* pSkin);
    void LoadSkin(MissSkin* pSkin, const wxString& strSkinPath);
};

#endif // MISSXML_H
