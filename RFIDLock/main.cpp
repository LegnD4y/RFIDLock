#include "rfidlock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RFIDLock w;
    w.show();
    return a.exec();
}
