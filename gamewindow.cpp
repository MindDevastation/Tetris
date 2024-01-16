#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QPixmap>
#include <random>
#include <QPalette>

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->gameField->setEnabled(false);
    gameProp.fill();
    gameField();

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(play()));
    timer->setInterval(1000);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::gameField()
{
    //creating game field

    ui->gameField->setColumnCount(this->gameProp.getCols());
    ui->gameField->setRowCount(this->gameProp.getRows());
    //ui->gameField->setFixedSize(this->gameProp.getCols() * 40, this->gameProp.getRows() * 40);

    //resize cols and rows
    for(int i = 0; i < this->gameProp.getRows(); i++){
        ui->gameField->setRowHeight(i, 40);
    }

    for(int i = 0; i < this->gameProp.getCols(); i++){
        ui->gameField->setColumnWidth(i, 40);
    }




    //render field
    for(int i = 0; i < this->gameProp.getRows(); i++){
        for (int k = 0; k < this->gameProp.getCols(); k++){
            renderField(i, k);
        }
    }
}


void GameWindow::renderFigure()
{
    figNum = this->figures.figNumber();

    posX = 0;
    posY = 4;

    int m = 0;
    for(int i = 0; i < 3; i++){
        for(int k = 4; k < 7; k++){
            if(this->figures.shapes[figNum][m] == '1'){
                gameProp.gameField[i][k] = this->figures.shapes[figNum][m];
            }
            m++;
        }
    }
    for(int i = 0; i < 3; i++){
        for (int k = 4; k < 7; k++){
            if (gameProp.gameField[i][k] == '1'){
                renderFigure(i, k);
            }
        }
    }
}

void GameWindow::renderField(int i, int k)
{
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setBackground(QColor(0, 0, 53));
    ui->gameField->setItem(i, k, item);
}

void GameWindow::renderFigure(int i, int k)
{
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setBackground(QColor(170, 247, 245));
    ui->gameField->setItem(i, k, item);
}


void GameWindow::play()
{
    //move down
    this->gameProp.moveDown();
    posX++;

    //render new figure`s position
    for(int i = 0; i < this->gameProp.getRows(); i++){
        for (int k = 0; k < this->gameProp.getCols(); k++){
            if (gameProp.gameField[i][k] == '1' || gameProp.gameField[i][k] == '*'){
                renderFigure(i, k);
            }else{
                renderField(i, k);
            }
        }
    }

    //check to fixate figure

    this->gameProp.fixateShape();

    //check if line is full

    this->gameProp.lineIsFull();

    ui->score->setText("Score: " + QString::number(this->gameProp.getScore()));

    //render new figure

    if(this->gameProp.getCheckNewFig() == true){
        this->gameProp.setCheckNewFig(false);
        renderFigure();
    }

    jumpLetters();

    end();

}

void GameWindow::end()
{
    for(int i = 0; i < this->gameProp.getCols(); i++){
        if(this->gameProp.gameField[1][i] == '*'){
            timer->stop();
            status = false;
            ui->status->setText("GAME OVER!");
            QString gameOver = "GAME OVER! Your score is " + QString::number(this->gameProp.getScore()) + " \n Start a new game?";
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Game over",
                                                                      gameOver,
                                                                      QMessageBox::Yes | QMessageBox::No);
            if(reply == QMessageBox::Yes){
                ui->gameField->clear();
                this->gameProp.fill();
                renderFigure();
                play();
                timer->start();
                status = true;
            }else{
                close();
            }
            break;
        }
    }
}

int GameWindow::rndGen()
{
    int num;
    std::random_device rnd;
    std::mt19937 en(rnd());
    std::uniform_int_distribution<int> dist(15, 35);

    num = dist(en);
    return num;
}

void GameWindow::jumpLetters()
{
    int pointSize = 0;
    QFont font = ui->T->font();

    pointSize = rndGen();
    font.setPointSize(pointSize);
    ui->T->setFont(font);

    pointSize = rndGen();
    font = ui->E->font();
    font.setPointSize(pointSize);
    ui->E->setFont(font);

    pointSize = rndGen();
    font = ui->T_2->font();
    font.setPointSize(pointSize);
    ui->T_2->setFont(font);

    pointSize = rndGen();
    font = ui->R->font();
    font.setPointSize(pointSize);
    ui->R->setFont(font);

    pointSize = rndGen();
    font = ui->I->font();
    font.setPointSize(pointSize);
    ui->I->setFont(font);

    pointSize = rndGen();
    font = ui->S->font();
    font.setPointSize(pointSize);
    ui->S->setFont(font);
}


void GameWindow::keyPressEvent(QKeyEvent *e)
{

    if(e->key() == Qt::Key_Down || e->key() == Qt::Key_S){

        this->play();

    }else if(e->key() == Qt::Key_Left || e->key() == Qt::Key_A){
        if(posY > 0){
            posY--;
        }

        //check if figure near left border
        for(int i = 0; i < this->gameProp.getRows(); i++){
            if(gameProp.gameField[i][0] == '1'){
                this->gameProp.setCheck(false);
                break;
            }else{
                this->gameProp.setCheck(true);
            }
        }

        // if there is fixed fig on the left
        if(this->gameProp.getCheck() == true){
            for(int i = 0; i < this->gameProp.getRows(); i++){
                for(int k = 1; k < this->gameProp.getCols(); k++){
                    if(gameProp.gameField[i][k - 1] == '*' && gameProp.gameField[i][k] == '1'){
                        this->gameProp.setCheck(false);
                        break;
                    }
                }
                if(this->gameProp.getCheck() == false){
                    break;
                }
            }
        }


        //Move left
        if(this->gameProp.getCheck() == true){
            for(int i = 0; i < this->gameProp.getRows(); i++){
                for(int k = 0; k < this->gameProp.getCols(); k++){
                    if(gameProp.gameField[i][k] == '1'){
                        gameProp.gameField[i][k - 1] = gameProp.gameField[i][k];
                        gameProp.gameField[i][k] = '0';
                    }
                }
            }
        }

        //check to fixate figure

        this->gameProp.fixateShape();

        //check if line is full

        this->gameProp.lineIsFull();

        ui->score->setText("Score: " + QString::number(this->gameProp.getScore()));

        //render
        for(int i = 0; i < this->gameProp.getRows(); i++){
            for (int k = 0; k < this->gameProp.getCols(); k++){
                if (gameProp.gameField[i][k] == '1' || gameProp.gameField[i][k] == '*'){
                    renderFigure(i, k);
                }else{
                    renderField(i, k);
                }
            }
        }


    }else if(e->key() == Qt::Key_Right || e->key() == Qt::Key_D){
        if(posY < this->gameProp.getCols() - 3){
            posY++;
        }

        //check if figure near right border
        for(int i = 0; i < this->gameProp.getRows(); i++){
            if(gameProp.gameField[i][this->gameProp.getCols() - 1] == '1'){
                this->gameProp.setCheck(false);
                break;
            }else{
                this->gameProp.setCheck(true);
            }
        }

        // if there is fixed fig on the right
        if(this->gameProp.getCheck() == true){
            for(int i = 0; i < this->gameProp.getRows(); i++){
                for(int k = 0; k < this->gameProp.getCols(); k++){
                    if(gameProp.gameField[i][k + 1] == '*' && gameProp.gameField[i][k] == '1'){
                        this->gameProp.setCheck(false);
                        break;
                    }
                }
                if(this->gameProp.getCheck() == false){
                    break;
                }
            }
        }


        //move right
        if(this->gameProp.getCheck() == true){
            for(int i = this->gameProp.getRows(); i >= 0; i--){
                for(int k = this->gameProp.getCols(); k >= 0; k--){
                    if(gameProp.gameField[i][k] == '1'){
                        gameProp.gameField[i][k + 1] = gameProp.gameField[i][k];
                        gameProp.gameField[i][k] = '0';
                    }
                }
            }
        }

        //check to fixate figure

        this->gameProp.fixateShape();

        //check if line is full

        this->gameProp.lineIsFull();

        ui->score->setText("Score: " + QString::number(this->gameProp.getScore()));

        //render
        for(int i = 0; i < this->gameProp.getRows(); i++){
            for (int k = 0; k < this->gameProp.getCols(); k++){
                if (gameProp.gameField[i][k] == '1' || gameProp.gameField[i][k] == '*'){
                    renderFigure(i, k);
                }else{
                    renderField(i, k);
                }
            }
        }
    }else if(e->key() == Qt::Key_V){
        int m = 0;

        switch (figNum) {
        case VLineShape:
            figNum = HLineShape;
            break;
        case LShape:
            figNum = PrefixShape;
            break;
        case ReverseLShape:
            figNum = LShape;
            break;
        case ReverseTShape:
            figNum = LayTShape;
            break;
        case TShape:
            figNum = ReverseLayTShape;
            break;
        case ZShape:
            figNum = ReverseZShape;
            break;
        case ReverseZShape:
            figNum = VZShape;
            break;
        case SquareShape:
            break;
        case HLineShape:
            figNum = VLineShape;
            break;
        case VReverseZShape:
            figNum = ReverseZShape;
            break;
        case VZShape:
            figNum = ZShape;
            break;
        case ReverseGShape:
            figNum = ReverseLayLShape;
            break;
        case GShape:
            figNum = ReverseGShape;
            break;
        case DotShape:
            break;
        case PrefixShape:
            figNum = LayLShape;
            break;
        case ReversePrefixShape:
            figNum = ReverseLShape;
            break;
        case LayLShape:
            figNum = GShape;
            break;
        case ReverseLayLShape:
            figNum = ReversePrefixShape;
            break;
        case LayTShape:
            figNum = TShape;
            break;
        case ReverseLayTShape:
            figNum = ReverseTShape;
            break;
        default:
            break;
        }

        for(int i = posX; i < posX + 3; i++){
            for(int k = posY; k < posY + 3; k++){
                this->gameProp.gameField[i][k] = '0';
            }
        }

        for(int i = posX; i < posX + 3; i++){
            for (int k = posY; k < posY + 3; k++){
                if (gameProp.gameField[i][k] == '0'){
                    renderField(i, k);
                }
            }
        }

        for(int i = posX; i < posX + 3; i++){
            for(int k = posY; k < posY + 3; k++){
                if(this->figures.shapes[figNum][m] == '1'){
                    gameProp.gameField[i][k] = this->figures.shapes[figNum][m];
                }
                m++;
            }
        }
        for(int i = posX; i < posX + 3; i++){
            for (int k = posY; k < posY + 3; k++){
                if (gameProp.gameField[i][k] == '1'){
                    renderFigure(i, k);
                }
            }
        }
    }else if(e->key() == Qt::Key_P){
        if(status == false){
            timer->start();
            status = true;
            ui->status->setText("Playing");
        }else{
            timer->stop();
            status = false;
            ui->status->setText("Pause");
        }
    }
}

void GameWindow::on_Close_clicked()
{
    timer->stop();
    status = false;
    ui->status->setText("Pause");
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit",
                                                              "Are you sure you want to exit?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        close();
    }else{
        timer->start();
        status = true;
        ui->status->setText("Playing");
    }
}


void GameWindow::on_Start_clicked()
{
    //render figure
    renderFigure();
    timer->start();
    status = true;
    ui->status->setText("Playing");
}


void GameWindow::on_NewGame_clicked()
{
    ui->gameField->clear();
    this->gameProp.fill();
    renderFigure();
    play();
    timer->start();
    status = true;
    ui->status->setText("Playing");
}

