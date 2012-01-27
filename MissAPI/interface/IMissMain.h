#ifndef IMISSMAIN_H
#define IMISSMAIN_H

class IMissTaskIcon;
class IMissHotKey;

class IMissMain
{
    public:
        virtual ~IMissMain() {}
        virtual void ExitApp() = 0;
        virtual IMissTaskIcon *GetTaskIcon() = 0;
        virtual IMissHotKey   *GetHotKey()   = 0;
    protected:
    private:
};

#endif // IMISSMAIN_H
