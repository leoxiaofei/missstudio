#ifndef MISSTIMERFUNCBASE_H
#define MISSTIMERFUNCBASE_H

enum MissTimerType{MTT_SEC,MTT_MIN};

class MissTimerFuncBase
{
    public:
        virtual ~MissTimerFuncBase(){}
        virtual void TimeUp(const tm* tmNow, MissTimerType eType)=0;

    protected:
    private:
};

#endif // MISSTIMERFUNCBASE_H
