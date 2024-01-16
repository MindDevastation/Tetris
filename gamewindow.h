#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include "gameprop.h"
#include <QKeyEvent>
#include <QString>
#include <QTime>
#include <QTimer>
#include <random>

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    QTimer* timer;
    figure figures;
    playField gameProp;
    int posX = 0, posY = 0;
    int figNum = 0;
    bool status = false;
    int sc = 0;
    enum shapes{
        VLineShape,         //0
        LShape,             //1
        ReverseLShape,      //2
        ReverseTShape,      //3
        TShape,             //4
        ZShape,             //5
        ReverseZShape,      //6
        SquareShape,        //7
        HLineShape,         //8
        VReverseZShape,     //9
        VZShape,            //10
        ReverseGShape,      //11
        GShape,             //12
        DotShape,           //13
        PrefixShape,        //14
        ReversePrefixShape, //15
        LayLShape,          //16
        ReverseLayLShape,   //17
        LayTShape,          //18
        ReverseLayTShape    //19
        };

private slots:
    void gameField();

    void renderFigure();

    void renderField(int i, int k);

    void renderFigure(int i, int k);

    void play();

    void end();

    int rndGen();

    void on_Close_clicked();

    void on_Start_clicked();

    void on_NewGame_clicked();

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
