#include <QtGui/QApplication>
#include "mainwindow.h"

#include "block.h"
#include "roundkey.h"
#include "bcs.h"
#include "rc6.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
