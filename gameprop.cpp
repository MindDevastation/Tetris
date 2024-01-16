#include "gameprop.h"

int playField::getRows(){return row;}
int playField::getCols(){return col;}
int playField::getScore(){return score;}
bool playField::getCheck(){return check;}
void playField::setCheck(bool newCheck){check = newCheck;}
bool playField::getCheckNewFig(){return checkNewFig;}
void playField::setCheckNewFig(bool newCheckFig){checkNewFig = newCheckFig;}
QString playField::getGameField(int rows, int cols) {return this->gameField[rows][cols];}

const void playField::fill(){
    for(int i = 0; i < 20; i++){
        for(int k = 0; k < 11; k++){
            gameField[i][k] = '0';
        }
    }
}

void playField::fixateShape(){
    //if figure is above another one
    for(int i = 0; i < this->getRows(); i++){
        for(int k = 0; k < this->getCols(); k++){
            if(gameField[i][k] == '1' && gameField[i + 1][k] == '*'){
                for(int ii = 0; ii < this->getRows(); ii++){
                    for(int kk = 0; kk < this->getCols(); kk++){
                        if(gameField[ii][kk] == '1'){
                            gameField[ii][kk] = '*';
                            checkNewFig = false;
                        }else{
                            checkNewFig = true;
                        }
                    }
                }
            }
        }
    }

    //if figure get to the bottom of the screen
    for(int k = 0; k < this->getCols(); k++){
        if(gameField[this->getRows() - 1][k] == '1'){
            checkNewFig = true;
            for(int ii = 0; ii < this->getRows(); ii++){
                for(int kk = 0; kk < this->getCols(); kk++){
                    if(gameField[ii][kk] == '1'){
                        gameField[ii][kk] = '*';
                    }
                }
            }
            break;
        }
    }
}

const int playField::lineIsFull(){
    int ind = 0;
    //is line full of *
    for(int i = this->getRows(); i >= 0; i--){
        for(int k = 0; k < this->getCols(); k++){
            if(gameField[i][k] == '*'){
                check = true;
            }else{
                check = false;
                break;
            }
        }
        if(check == true){
            //clear line
            for(int k = 0; k < this->getCols(); k++){
                gameField[i][k] = '0';
                checkNewFig = true;
                score += 1;
            }
            //move lines down
            for(int ii = i; ii >= 1; ii--){
                for(int k = 0; k < this->getCols(); k++){
                    gameField[ii][k] = gameField[ii - 1][k];
                }
            }
            // fill top line with 0
            for(int k = 0; k < this->getCols(); k++){
                gameField[0][k] = '0';
            }
        }
    }

    return score;
}

const void playField::moveDown(){
    for(int i = this->getRows(); i >= 0; i--){
        for(int k = getCols(); k >= 0; k--){
            if(gameField[i][k] == '1'){
                gameField[i + 1][k] = gameField[i][k];
                gameField[i][k] = '0';
            }
        }
    }
}
