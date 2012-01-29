#ifndef MISSAUTOINPUTTHREAD_H
#define MISSAUTOINPUTTHREAD_H

#include <wx/Thread.h>


class MissAutoInputThread : public wxThread
{
    public:
        MissAutoInputThread();
        virtual ~MissAutoInputThread();

        static void SendUnicode(wchar_t wch);
        static void SendKey(char ch);
    protected:
        virtual ExitCode Entry();

    private:
};

#endif // MISSAUTOINPUTTHREAD_H
