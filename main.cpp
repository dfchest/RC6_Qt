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

    /*RC6 *tmp = new RC6(32, 20, 16, "1234567890123456");

    tmp->Encryption_mode_4("D:\\in.txt", "D:\\out.txt", "1234567890123456", 3);
    tmp->Decryption_mode_4("D:\\out.txt", "D:\\in_d.txt", "1234567890123456", 3);*/

    return a.exec();
}
