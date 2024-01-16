#ifndef GAMEPROP_H
#define GAMEPROP_H

#include <QTableWidgetItem>
#include <QString>
#include <random>


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

    QString gameField [row][col];

    int getRows();
    int getCols();
    int getScore();
    bool getCheck();
    void setCheck(bool newCheck);
    bool getCheckNewFig();
    void setCheckNewFig(bool newCheckFig);
    QString getGameField(int rows, int cols);

    const void fill();

    void fixateShape();

    const int lineIsFull();

    const void moveDown();

};



#endif // GAMEPROP_H
