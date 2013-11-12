#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QDebug>
#include <QFile>

#include "fourwords.h"
#include "roundkey.h"
#include "bcs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    /*FourWords a1(1, 2, 3, 4);
    qDebug() << a1[0];

    a1.ShiftLeft();
    qDebug() << a1[0];

    a1.set(5, 6, 7, 8);

    a1[3] = 3;

    a1.ShiftRight();
    qDebug() << a1[0];

    uint16_t t1 = 1;
    uint32_t t2 = 1;
    quint64 t3 = 1;

    qDebug() << BCS::Shift(t1, 16, 1);
    qDebug() << BCS::Shift(t2, 32, 1);
    qDebug() << BCS::Shift(t3, 64, 1);

    qDebug() << BCS::Shift(t1, 16, -15);
    qDebug() << BCS::Shift(t2, 32, -31);
    qDebug() << BCS::Shift(t3, 64, -63);

    RoundKey key1(16, 20, 16, "1111111111111111");
    RoundKey key2(16, 20, 16, "9999999999999999");

    key1.Advanced();
    key2.Advanced();
    key1.Advanced();
    key2.Advanced();*/

    QFile* f1 = new QFile("D:\\in.txt");
    f1->open(QIODevice::ReadOnly);
    QDataStream in;

    return a.exec();
}
