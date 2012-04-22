#ifndef MISSHOTKEYMANAGER_H
#define MISSHOTKEYMANAGER_H

#include "../../MissAPI/interface/IMissHotKey.h"

class wxWindow;

struct SPluginHotKeyData
{
    int nStartID;
    std::vector<SHotKeyData> vecHotKey;
    MissHotKeyFuncBase* pHotKeyBase;
};

class MissHotKeyManager : public IMissHotKey
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

    ///接口实现
    bool RegHotKeys(const std::vector<SHotKeyData>& vecHotKey, MissHotKeyFuncBase* pChild);

protected:
private:
    shared_ptr<MissHotKeyManagerImpl> m_pImpl;
};

#endif // MISSHOTKEYMANAGER_H
