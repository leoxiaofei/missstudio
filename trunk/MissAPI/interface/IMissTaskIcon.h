#ifndef IMISSTASKICON_H
#define IMISSTASKICON_H


class IMissTaskIcon
{
    public:
        virtual ~IMissTaskIcon() {}

        virtual bool ShowBalloon(const wxString &strTitle,
                         const wxString &strMsg,
                         int iconID = 0x00000001,
                         unsigned int timeout = 3000) = 0;

    protected:
    private:
};

#endif // IMISSTASKICON_H
