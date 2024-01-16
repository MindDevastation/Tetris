#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    l = new GameWindow(this);

    QPixmap pix(":/img/tetris.jpg");

    int backWidth = ui->background->width();
    int backHeight = ui->background->height();

    ui->background->setPixmap(pix.scaled(backWidth, backHeight, Qt::KeepAspectRatio));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Start_clicked()
{
    close();
    l->exec();
    l->setFixedHeight(1);
    l->setFixedWidth(1);

}

