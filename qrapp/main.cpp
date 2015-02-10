#include "qrwidget.h"
#include <QApplication>

#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QRWidget w;

    return a.exec();
}
