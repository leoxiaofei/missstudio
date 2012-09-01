#ifndef MISSHOTKEYFUNCBASE_H
#define MISSHOTKEYFUNCBASE_H

class MissHotKeyFuncBase
{
    public:
        MissHotKeyFuncBase(){};
        virtual ~MissHotKeyFuncBase() {}

        virtual void RunFunc(int nFuncIndex) = 0;
        virtual void ModifiedHotKey(int nFuncIndex, const wxString& strHotKey) = 0;

    protected:


    private:
};

#endif // MISSHOTKEYFUNCBASE_H
