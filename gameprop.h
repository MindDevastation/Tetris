#ifndef GAMEPROP_H
#define GAMEPROP_H

#include <QTableWidgetItem>
#include <QString>
#include <random>

class gameProp
{
public:
    gameProp();
};


class figure
{
public:

    QString shapes[20]{"010010010",
                       "010010011",
                       "010010110",
                       "010010111",
                       "111010010",
                       "000110011",
                       "000011110",
                       "110110000",
                       "000111000",
                       "100110010",
                       "001011010",
                       "110010010",
                       "011010010",
                       "000010000",
                       "000111001",
                       "000111100",
                       "001111000",
                       "100111000",
                       "001111001",
                       "100111100"};

    int colorRed[5]{255, 0, 0, 255, 0};
    int colorGreen[5]{0, 255, 0, 255, 255};
    int colorBlue[5]{0, 0, 255, 0, 255};

    int getBlue(int i){return colorBlue[i];}

    int figNumber(){
        int num;
        std::random_device rnd;
        std::mt19937 en(rnd());
        std::uniform_int_distribution<int> dist(0, 19);

        num = dist(en);
        return num;
    }
};

class playField
{
private:
    static const int row = 20, col = 11;
    bool check = false;
    bool checkNewFig = false;
    int score = 0;

protected:



public:

    QString gameField [20][11];
    int getRows(){return row;}
    int getCols(){return col;}
    int getScore(){return score;}
    bool getCheck(){return check;}
    void setCheck(bool newCheck){check = newCheck;}
    bool getCheckNewFig(){return checkNewFig;}
    void setCheckNewFig(bool newCheckFig){checkNewFig = newCheckFig;}
    QString getGameField(int rows, int cols) {return this->gameField[rows][cols];}

    const void fill(){
        for(int i = 0; i < 20; i++){
            for(int k = 0; k < 11; k++){
                gameField[i][k] = '0';
            }
        }
    }

     void fixateShape(){
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

    const int lineIsFull(){
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

    const void moveDown(){
        for(int i = this->getRows(); i >= 0; i--){
            for(int k = getCols(); k >= 0; k--){
                if(gameField[i][k] == '1'){
                    gameField[i + 1][k] = gameField[i][k];
                    gameField[i][k] = '0';
                }
            }
        }
    }

};



#endif // GAMEPROP_H
