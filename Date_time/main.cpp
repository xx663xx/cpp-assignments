#include <iostream>
#include "DateTime.h"

int main() {
    std::cout << "=== Демонстрация работы класса DateTime ===\n\n";

    DateTime dt1(2021, 12, 21, 7, 54, 34);
    DateTime dt2(2020, 1, 1);
    DateTime dt3(2021, 12, 21, 7, 54, 34);

    std::cout << "dt1: " << dt1 << "\n";
    std::cout << "dt2: " << dt2 << "\n";
    std::cout << "dt3: " << dt3 << "\n\n";

    std::cout << "dt1 корректна? " << (dt1.isValid() ? "Да" : "Нет") << "\n";
    DateTime invalidDate(2021, 13, 32);
    std::cout << "invalidDate (2021-13-32) корректна? " << (invalidDate.isValid() ? "Да" : "Нет") << "\n\n";

    int diff = dt1 - dt2;
    std::cout << "Разница между dt1 и dt2: " << diff << " дней\n\n";

    DateTime dtPlus = dt1 + 100;
    std::cout << "dt1 + 100 дней: " << dtPlus << "\n";
    DateTime dtMinus = dt1 - 30;
    std::cout << "dt1 - 30 дней: " << dtMinus << "\n\n";

    std::cout << "dt1 > dt2? " << (dt1 > dt2 ? "Да" : "Нет") << "\n";
    std::cout << "dt1 >= dt3? " << (dt1 >= dt3 ? "Да" : "Нет") << "\n";
    std::cout << "dt1 < dt2? " << (dt1 < dt2 ? "Да" : "Нет") << "\n";
    std::cout << "dt1 <= dt3? " << (dt1 <= dt3 ? "Да" : "Нет") << "\n";
    std::cout << "dt1 == dt3? " << (dt1 == dt3 ? "Да" : "Нет") << "\n";
    std::cout << "dt1 != dt2? " << (dt1 != dt2 ? "Да" : "Нет") << "\n\n";

    char dayName[32];
    dt1.getDayOfWeekName(dayName, sizeof(dayName));
    std::cout << "dt1 (" << dt1 << ") - " << dayName << "\n";
    dt2.getDayOfWeekName(dayName, sizeof(dayName));
    std::cout << "dt2 (" << dt2 << ") - " << dayName << "\n\n";

    std::cout << "=== Сортировка дат из Приложения №1 ===\n\n";

    const int DATE_COUNT = 26;
    DateTime dates[DATE_COUNT] = {
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

    std::cout << "До сортировки:\n";
    for (int i = 0; i < DATE_COUNT; ++i) {
        dates[i].getDayOfWeekName(dayName, sizeof(dayName));
        std::cout << dates[i] << " (" << dayName << ")\n";
    }

    DateTime::quickSort(dates, DATE_COUNT);

    std::cout << "\nПосле сортировки:\n";
    for (int i = 0; i < DATE_COUNT; ++i) {
        dates[i].getDayOfWeekName(dayName, sizeof(dayName));
        std::cout << dates[i] << " (" << dayName << ")\n";
    }

    std::cout << "\n=== Тест ввода даты с клавиатуры ===\n";
    std::cout << "Введите дату в формате yyyy-MM-dd (например, 2021-12-21): ";
    DateTime userInput;
    std::cin >> userInput;
    std::cout << "Вы ввели: " << userInput << "\n";
    userInput.getDayOfWeekName(dayName, sizeof(dayName));
    std::cout << "День недели: " << dayName << "\n";

    std::cout << "\n=== Программа завершена ===\n";

    return 0;
}