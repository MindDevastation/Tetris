#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    GameWindow* GameWindow;

private slots:
    void on_Start_clicked();

    void on_Close_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
