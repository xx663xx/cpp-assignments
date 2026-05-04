#include <iostream>
#include "Field.h"

using namespace std;

Field::Field(bool isRedFirst)
{
    clear(isRedFirst);
}

void Field::clear(bool isRedFirst)
{
    isRedTurn = isRedFirst;
    winner = EMPTY;

    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            cells[i][j] = EMPTY;
}

bool Field::makeTurn(int column)
{
    if (winner != EMPTY || column < 1 || column > FIELD_WIDTH)
        return false;

    int i = column - 1;

    for (int j = 0; j < FIELD_HEIGHT; j++)
        if (cells[i][j] == EMPTY)
        {
            if (isRedTurn)
                cells[i][j] = RED;
            else
                cells[i][j] = YELLOW;

            checkWinner();
            isRedTurn = !isRedTurn;
            return true;
        }

    return false;
}

bool Field::isWon(bool red) const
{
    if (red)
        return winner == RED;
    else
        return winner == YELLOW;
}

bool Field::isOver() const
{
    if (winner != EMPTY)
        return true;

    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            if (cells[i][j] == EMPTY)
                return false;

    return true;
}

Cell Field::getCell(int i, int j) const
{
    if (i < 0 || i >= FIELD_WIDTH || j < 0 || j >= FIELD_HEIGHT)
        return EMPTY;

    return cells[i][j];
}

bool Field::isRedTurnNow() const
{
    return isRedTurn;
}

void Field::print() const
{
    cout << endl;

    for (int j = FIELD_HEIGHT - 1; j >= 0; j--)
    {
        cout << "|";

        for (int i = 0; i < FIELD_WIDTH; i++)
        {
            switch (cells[i][j])
            {
            case RED:
                cout << "R";
                break;
            case YELLOW:
                cout << "Y";
                break;
            default:
                cout << " ";
            }

            cout << "|";
        }

        cout << endl;
    }

    cout << " 1 2 3 4 5 6 7" << endl << endl;
}

void Field::printResult() const
{
    print();

    if (winner == RED)
        cout << "Победил красный игрок" << endl;
    else if (winner == YELLOW)
        cout << "Победил желтый игрок" << endl;
    else
        cout << "Ничья" << endl;
}

void Field::checkWinner()
{
    const int DIR_NUMBER = 4;
    const int di[] = { 1, 0, 1, 1 };
    const int dj[] = { 0, 1, -1, 1 };
    const int WIN_LENGTH = 4;

    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
        {
            Cell start = cells[i][j];

            if (start == EMPTY)
                continue;

            for (int dir = 0; dir < DIR_NUMBER; dir++)
            {
                int length = 0;
                int iline = i;
                int jline = j;

                while (++length < WIN_LENGTH)
                {
                    iline += di[dir];
                    jline += dj[dir];

                    if (iline < 0 || iline >= FIELD_WIDTH ||
                        jline < 0 || jline >= FIELD_HEIGHT)
                        break;

                    if (cells[iline][jline] != start)
                        break;
                }

                if (length == WIN_LENGTH)
                {
                    winner = start;
                    return;
                }
            }
        }
}
