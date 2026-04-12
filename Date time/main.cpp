#include "datetime.h"

int main() {
    DateTime first;
    DateTime second;

    std::cout << "Работа с датой и временем\n\n";

    std::cout << "Введите первую дату\n";
    first.readDate();

    std::cout << "Введите вторую дату\n";
    second.readDate();

    std::cout << "\nПервая дата: ";
    first.showDate();
    std::cout << "\nВторая дата: ";
    second.showDate();
    std::cout << "\n\n";

    std::cout << "Разность в днях: " << first - second << "\n\n";

    int n;
    while (true) {
        try {
            std::cout << "Сколько дней прибавить к первой дате: ";
            std::cin >> n;

            if (std::cin.fail()) {
                throw "Ошибка ввода";
            }

            if (n < 0) {
                throw "Введите число 0 или больше";
            }

            break;
        }
        catch (const char* msg) {
            std::cout << msg << "\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    DateTime result = first + n;
    std::cout << "Получилось: ";
    result.showDate();
    std::cout << "\n\n";

    std::cout << "Сравнение:\n";
    std::cout << "first > second : " << (first > second) << "\n";
    std::cout << "first >= second : " << (first >= second) << "\n";
    std::cout << "first < second : " << (first < second) << "\n";
    std::cout << "first <= second : " << (first <= second) << "\n";
    std::cout << "first == second : " << (first == second) << "\n\n";

    std::cout << "День недели первой даты: ";
    showWeekDayName(first.getWeekDay());
    std::cout << "\n\n";

    DateTime full;
    std::cout << "Проверка полного формата даты и времени\n";
    full.readFull();
    std::cout << "Вы ввели: ";
    full.showFull();
    std::cout << "\n\n";

    DateTime list[] = {
        DateTime(1995, 1, 1),
        DateTime(1994, 4, 26),
        DateTime(1992, 12, 5),
        DateTime(1994, 7, 12),
        DateTime(1993, 9, 11),
        DateTime(1992, 7, 21),
        DateTime(1997, 6, 29),
        DateTime(1997, 2, 6),
        DateTime(1995, 10, 31),
        DateTime(1993, 8, 18),
        DateTime(1995, 3, 2),
        DateTime(1996, 8, 12),
        DateTime(1997, 1, 28),
        DateTime(1995, 12, 15),
        DateTime(1997, 6, 9),
        DateTime(1993, 11, 10),
        DateTime(1994, 7, 5),
        DateTime(1993, 6, 6),
        DateTime(1997, 8, 21),
        DateTime(1996, 9, 28),
        DateTime(1993, 1, 14),
        DateTime(1992, 10, 2),
        DateTime(1997, 6, 13),
        DateTime(1996, 8, 18),
        DateTime(1994, 6, 8),
        DateTime(1993, 5, 4)
    };

    int size = sizeof(list) / sizeof(list[0]);
    sortDates(list, 0, size - 1);

    std::cout << "Даты после сортировки:\n";
    for (int i = 0; i < size; i++) {
        list[i].showDate();
        std::cout << "\n";
    }

    return 0;
}
