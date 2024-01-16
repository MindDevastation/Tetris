#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->GameWindow = new class GameWindow(this);

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
    GameWindow->exec();
    GameWindow->setFixedHeight(1);
    GameWindow->setFixedWidth(1);

}


void MainWindow::on_Close_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit",
                                                              "Are you sure you want to exit?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        close();
    }
}

