#ifndef MISSHOTKEYMANAGER_H
#define MISSHOTKEYMANAGER_H

#include "../../MissAPI/interface/IMissHotKey.h"

class wxWindow;
class MissHotKeyFuncBase;

struct SPluginHotKeyData
{
    int                 nStartID;
    HotKeyDataSet       vecHotKey;
    MissHotKeyFuncBase* pHotKeyBase;
};


class MissHotKeyManager
{
    class MissHotKeyManagerImpl;
public:
    MissHotKeyManager();
    virtual ~MissHotKeyManager();

    void SetMainWindow(wxWindow* pParent);
    bool GetHotkeyString(unsigned int nPlugin, unsigned int nFunc,
                         wxString& strValue);

    std::vector<SPluginHotKeyData>& GetHotKeyData();


    void RunFuncFromHotKey(int nHotKeyID);

    bool RegHotKey(int nHotKeyID, const wxString &strHotKey);
    bool UnRegHotKey(int nHotKeyID);

    bool ModifyHotKey(unsigned int nPlugin, unsigned int nFunc,
                      const wxString &strHotKey);

    bool RegHotKeys(const HotKeyDataSet& vecHotKey, MissHotKeyFuncBase* pChild);
    bool UnRegHotKeys(MissHotKeyFuncBase* pChild);

protected:
private:
    shared_ptr<MissHotKeyManagerImpl> m_pImpl;
};

#endif // MISSHOTKEYMANAGER_H
