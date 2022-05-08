//
// Created by Aquit on 2022/5/3.
//

#ifndef FTP_CLIPBOARD_KEYBOARD_MOUSE_HOOK_H
#define FTP_CLIPBOARD_KEYBOARD_MOUSE_HOOK_H

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <inttypes.h>

#include <string>

#include <QDebug>
#include <QThread>

#include "Public_Func/PubilcFunc.h"
#include "libiohook/include/uiohook.h"

class KeyBoard_Mouse_Hook : public QThread, public Pubilc_Func{
    Q_OBJECT
public:
    KeyBoard_Mouse_Hook();
    static KeyBoard_Mouse_Hook* instance();
    void run();

public slots:
    QString getRcvBuf(emitBundle &emitBundle);

signals:
    //void sndSignal(emitBundle& buf);

private:
    static bool logger_proc(unsigned int level, const char *format, ...);

    static void dispatch_proc(uiohook_event * const event);

    int startHook();

    static KeyBoard_Mouse_Hook* kbmh;
};



#endif //FTP_CLIPBOARD_KEYBOARD_MOUSE_HOOK_H
