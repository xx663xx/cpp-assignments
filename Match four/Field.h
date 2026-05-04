#ifndef FIELD_H
#define FIELD_H

const int FIELD_WIDTH = 7;
const int FIELD_HEIGHT = 6;

enum Cell
{
    EMPTY,
    RED,
    YELLOW
};

class Field
{
private:
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT];
    bool isRedTurn;
    Cell winner;

    void checkWinner();

public:
    Field(bool isRedFirst);
    void clear(bool isRedFirst);
    bool makeTurn(int column);
    bool isWon(bool red) const;
    bool isOver() const;
    Cell getCell(int i, int j) const;
    bool isRedTurnNow() const;
    void print() const;
    void printResult() const;
};

#endif
