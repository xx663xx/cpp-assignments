#include <iostream>
#include "Field.h"

using namespace std;

int main()
{
    Field field(true);

    cout << "Игра Четыре в ряд" << endl;
    cout << "Формат ввода: номер колонки от 1 до 7" << endl;

    while (!field.isOver())
    {
        field.print();

        if (field.isRedTurnNow())
            cout << "Ходит красный игрок";
        else
            cout << "Ходит желтый игрок";

        cout << ", введите ход (1-7): ";

        int column;
        if (!(cin >> column))
        {
            cout << "Ошибка ввода" << endl;
            return 0;
        }

        if (!field.makeTurn(column))
            cout << "Такой ход сделать нельзя, попробуйте еще раз" << endl;
    }

    field.printResult();

    return 0;
}
