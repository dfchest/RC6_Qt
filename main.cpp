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

    RC6 *tmp = new RC6(32, 20, 16, "1234567890123456");

    tmp->Encryption_mode_3("C:\\QtProject\\in.txt", "C:\\QtProject\\out.txt", "1234567890123456", 1);
    tmp->Decryption_mode_3("C:\\QtProject\\out.txt", "C:\\QtProject\\in_d.txt", "1234567890123456", 1);

    return a.exec();
}
