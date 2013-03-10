#ifndef MISSTIMERFUNCBASE_H
#define MISSTIMERFUNCBASE_H

struct tm;

class MissTimerFuncBase
{
    public:
        virtual ~MissTimerFuncBase(){}
        virtual void TimeUp(const tm* tmNow) = 0;

    protected:
    private:
};

#endif // MISSTIMERFUNCBASE_H
