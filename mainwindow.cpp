#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->encryption_Button, SIGNAL(pressed()), this, SLOT(Encryption()));
    QObject::connect(ui->decryption_Button, SIGNAL(pressed()), this, SLOT(Decryption()));

    QObject::connect(ui->browse_In, SIGNAL(pressed()), this, SLOT(BrowseIn()));
    QObject::connect(ui->browse_Out, SIGNAL(pressed()), this, SLOT(BrowseOut()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Encryption()
{
    int w, r, l;
    QString key;

    if(ui->w_16bit->isChecked())
        w = 16;
    else if(ui->w_32bit->isChecked())
        w = 32;
    else if(ui->w_64bit->isChecked())
        w = 64;

    r = ui->RoungCount->value();
    l = ui->PassLength->value();

    key = ui->line_Pass->text();

    alg = new RC6(w, r, l, key);

    if(ui->mode_1->isChecked())
    {
        alg->Encryption_mode_1(ui->line_In->text(), ui->line_Out->text());
        return;
    }

    if(ui->mode_2->isChecked())
    {
        alg->Encryption_mode_2(ui->line_In->text(), ui->line_Out->text(),
                               ui->line_InitVect->text().toStdString());
        return;
    }

    int shift = 1;

    if(ui->shift_1_word->isChecked())
        shift = 1;
    else if(ui->shift_2_word->isChecked())
        shift = 2;
    else if(ui->shift_3_word->isChecked())
        shift = 3;

    if(ui->mode_3->isChecked())
    {
        alg->Encryption_mode_3(ui->line_In->text(), ui->line_Out->text(),
                               ui->line_InitVect->text().toStdString(), shift);

        return;
    }

    if(ui->mode_4->isChecked())
    {
        alg->Encryption_mode_4(ui->line_In->text(), ui->line_Out->text(),
                               ui->line_InitVect->text().toStdString(), shift);

        return;
    }

    delete(alg);
}

void MainWindow::Decryption()
{
    int w, r, l;
    QString key;

    if(ui->w_16bit->isChecked())
        w = 16;
    else if(ui->w_32bit->isChecked())
        w = 32;
    else if(ui->w_64bit->isChecked())
        w = 64;

    r = ui->RoungCount->value();
    l = ui->PassLength->value();

    key = ui->line_Pass->text();

    alg = new RC6(w, r, l, key);

    if(ui->mode_1->isChecked())
    {
        alg->Decryption_mode_1(ui->line_In->text(), ui->line_Out->text());
        return;
    }

    if(ui->mode_2->isChecked())
    {
        alg->Decryption_mode_2(ui->line_In->text(), ui->line_Out->text(),
                               ui->line_InitVect->text().toStdString());
        return;
    }


    int shift = 1;

    if(ui->shift_1_word->isChecked())
        shift = 1;
    else if(ui->shift_2_word->isChecked())
        shift = 2;
    else if(ui->shift_3_word->isChecked())
        shift = 3;

    if(ui->mode_3->isChecked())
    {
        alg->Decryption_mode_3(ui->line_In->text(), ui->line_Out->text(),
                               ui->line_InitVect->text().toStdString(), shift);

        return;
    }

    if(ui->mode_4->isChecked())
    {
        alg->Decryption_mode_4(ui->line_In->text(), ui->line_Out->text(),
                               ui->line_InitVect->text().toStdString(), shift);

        return;
    }

    delete(alg);
}

void MainWindow::BrowseIn()
{
    QString path = QFileDialog::getOpenFileName( this, tr("Input File"), "C:\\QtProject", tr("*.*") );

    if( path != "" )
        ui->line_In->setText(path);
}

void MainWindow::BrowseOut()
{
    QString path = QFileDialog::getSaveFileName( this, tr("Output File"), "C:\\QtProject", tr("*.*") );

    if( path != "" )
        ui->line_Out->setText(path);
}
