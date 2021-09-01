#include "mainwindow.h"
#include "logowanie.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Logowanie l;
    l.show();
    return a.exec();
}
