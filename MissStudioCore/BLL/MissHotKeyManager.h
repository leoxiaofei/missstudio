#ifndef MISSHOTKEYMANAGER_H
#define MISSHOTKEYMANAGER_H

#include "../../MissAPI/interface/IMissHotKey.h"

class wxWindow;

struct ChildData
{
    int nStartID;
    //int nCount;
    //wxString strPluginName;
    std::vector<SHotKey> vecHotKey;
    MissHotKeyFuncBase* pChild;
};

class MissHotKeyManager : public IMissHotKey
{
    class MissHotKeyManagerImpl;
    public:
        MissHotKeyManager(wxWindow* pParent);
        virtual ~MissHotKeyManager();

        std::vector<ChildData>& GetChildData();

        void RunFuncFromHotKey(int nHotKeyID);

        bool RegHotKey(int nHotKeyID, const wxString &strHotKey);
        bool UnRegHotKey(int nHotKeyID);

        bool ModifyHotKey(int nPlugin, int nFunc, const wxString &strHotKey);

        ///接口实现
        bool RegHotKeys(const std::vector<SHotKey>& vecHotKey, MissHotKeyFuncBase* pChild);

    protected:
    private:
        shared_ptr<MissHotKeyManagerImpl> m_pImpl;
};

#endif // MISSHOTKEYMANAGER_H
