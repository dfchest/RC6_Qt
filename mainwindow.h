#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "rc6.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    RC6 *alg;

public slots:
    void Encryption();
    void Decryption();

    void BrowseIn();
    void BrowseOut();
};

#endif // MAINWINDOW_H
