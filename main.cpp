#include "loginservice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if (false && (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()))
    {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    QApplication a(argc, argv);
    LoginService loginService;
    loginService.show();
    return a.exec();
}
