#include "DateTime.h"

int main() {
    DateTime date1;
    DateTime date2;

    cout << "Введите первую дату (yyyy-MM-dd или yyyy-MM-ddThh:mm:ss): ";
    date1.input();

    cout << "Введите вторую дату (yyyy-MM-dd или yyyy-MM-ddThh:mm:ss): ";
    date2.input();

    cout << "\nПервая дата: ";
    date1.printDateTime();
    cout << "\nВторая дата: ";
    date2.printDateTime();
    cout << "\n";

    cout << "\nПроверка корректности:\n";
    cout << "Первая дата: ";
    if (date1.isValid()) {
        cout << "корректна\n";
    } else {
        cout << "некорректна\n";
    }
    cout << "Вторая дата: ";
    if (date2.isValid()) {
        cout << "корректна\n";
    } else {
        cout << "некорректна\n";
    }

    cout << "\nРазница в днях: " << date1 - date2 << "\n";

    cout << "\nПервая дата плюс 10 дней: ";
    (date1 + 10).printDateTime();
    cout << "\n";

    cout << "\nСравнение дат:\n";
    cout << "date1 > date2: " << (date1 > date2) << "\n";
    cout << "date1 >= date2: " << (date1 >= date2) << "\n";
    cout << "date1 < date2: " << (date1 < date2) << "\n";
    cout << "date1 <= date2: " << (date1 <= date2) << "\n";
    cout << "date1 == date2: " << (date1 == date2) << "\n";

    cout << "\nДень недели для первой даты: " << date1.dayOfWeek() << "\n";
    cout << "День недели для второй даты: " << date2.dayOfWeek() << "\n";

    cout << "\nОтдельные форматы:\n";
    cout << "Только дата: ";
    date1.printDate();
    cout << "\nТолько время: ";
    date1.printTime();
    cout << "\nДата и время: ";
    date1.printDateTime();
    cout << "\n";

    DateTime arr[26];
    arr[0] = DateTime(1995, 1, 1);
    arr[1] = DateTime(1994, 4, 26);
    arr[2] = DateTime(1992, 12, 5);
    arr[3] = DateTime(1994, 7, 12);
    arr[4] = DateTime(1993, 9, 11);
    arr[5] = DateTime(1992, 7, 21);
    arr[6] = DateTime(1997, 6, 29);
    arr[7] = DateTime(1997, 2, 6);
    arr[8] = DateTime(1995, 10, 31);
    arr[9] = DateTime(1993, 8, 18);
    arr[10] = DateTime(1995, 3, 2);
    arr[11] = DateTime(1996, 8, 12);
    arr[12] = DateTime(1997, 1, 28);
    arr[13] = DateTime(1995, 12, 15);
    arr[14] = DateTime(1997, 6, 9);
    arr[15] = DateTime(1993, 11, 10);
    arr[16] = DateTime(1994, 7, 5);
    arr[17] = DateTime(1993, 6, 6);
    arr[18] = DateTime(1997, 8, 21);
    arr[19] = DateTime(1996, 9, 28);
    arr[20] = DateTime(1993, 1, 14);
    arr[21] = DateTime(1992, 10, 2);
    arr[22] = DateTime(1997, 6, 13);
    arr[23] = DateTime(1996, 8, 18);
    arr[24] = DateTime(1994, 6, 8);
    arr[25] = DateTime(1993, 5, 4);

    quickSort(arr, 0, 25);

    cout << "\nОтсортированные даты:\n";
    for (int i = 0; i < 26; i++) {
        arr[i].printDate();
        cout << "\n";
    }

    return 0;
}
