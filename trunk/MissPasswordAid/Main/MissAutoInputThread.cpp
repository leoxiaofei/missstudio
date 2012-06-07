#include "MissAutoInputThread.h"
#include <wx/utils.h>
#include "../Common/MissGlobal.h"
//#define WINVER 0x0600
#define _WIN32_WINNT 0x0500
#include <windows.h>
//#include <atlconv.h>

MissAutoInputThread::MissAutoInputThread()
: wxThread(wxTHREAD_DETACHED)
{
    //ctor
}

MissAutoInputThread::~MissAutoInputThread()
{
    //dtor
}

wxThread::ExitCode MissAutoInputThread::Entry()
{
    wxMilliSleep(500);
    int nCount = MissGlobal::strClipbrd.length();
    for(int ix = 0; ix != nCount; ++ix)
    {
        //SendUnicode(MissGlobal::strClipbrd[ix]);
        SendKey(MissGlobal::strClipbrd[ix]);
    }
    return (wxThread::ExitCode)0;     // success
}

void MissAutoInputThread::SendUnicode(wchar_t wch)
{
    INPUT input[2];
    memset(input, 0, 2 * sizeof(INPUT));

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = 0;
    input[0].ki.wScan = wch;
    input[0].ki.dwFlags = 0x4;//KEYEVENTF_UNICODE;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = 0;
    input[1].ki.wScan = wch;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP | 0x4;//KEYEVENTF_UNICODE;

    SendInput(2, input, sizeof(INPUT));
}

void MissAutoInputThread::SendKey(char ch)
{
    DWORD sc,shift;
    unsigned char vkey;

    sc = OemKeyScan(ch);
    shift = sc >> 16;
    vkey=MapVirtualKey(sc&0xffff,1);
    if(shift)
        keybd_event(VK_SHIFT,0,0,0);
    keybd_event(vkey,0,0,0);
    keybd_event(vkey,0,KEYEVENTF_KEYUP,0);
    if(shift)
        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
}
