#include <iostream>
#include <fstream>
#include "datetime.h"

int main() {
    try {
        DateTime date;
        date.readDate();

        char fileName[30] = "Moon/00000000.dat";
        int num = date.getYmdNumber();

        for (int i = 12; i >= 5; i--) {
            fileName[i] = char(num % 10 + '0');
            num /= 10;
        }

        std::ifstream file(fileName);
        if (!file) {
            file.clear();
            char fileName2[30] = "Moon/moon0000.dat";
            num = date.getYear();

            for (int i = 12; i >= 9; i--) {
                fileName2[i] = char(num % 10 + '0');
                num /= 10;
            }

            file.open(fileName2);
            if (!file) {
                throw "Файл с данными за эту дату не найден";
            }
        }

        int needDate = date.getYmdNumber();
        int ymd, hms;
        double t, r, el, az, fi, lg;
        double lastEl = 0;
        double maxEl = -1000;
        bool wasLine = false;
        bool wasDate = false;
        bool riseOk = false;
        bool kulmOk = false;
        bool setOk = false;

        DateTime rise = date;
        DateTime kulm = date;
        DateTime set = date;

        char title[100];
        file.getline(title, 100);

        while (file >> ymd >> hms >> t >> r >> el >> az >> fi >> lg) {
            if (ymd < needDate) {
                continue;
            }

            if (ymd > needDate) {
                break;
            }

            wasDate = true;

            if (!kulmOk || el > maxEl) {
                maxEl = el;
                kulm.setTimeByNumber(hms);
                kulmOk = true;
            }

            if (wasLine) {
                if (!riseOk && lastEl < 0 && el >= 0) {
                    rise.setTimeByNumber(hms);
                    riseOk = true;
                }

                if (!setOk && lastEl > 0 && el <= 0) {
                    set.setTimeByNumber(hms);
                    setOk = true;
                }
            }

            lastEl = el;
            wasLine = true;
        }

        if (!wasDate) {
            throw "Данных за эту дату в файле нет";
        }

        std::cout << "\nДата: ";
        date.showDate();

        std::cout << "\nВосход Луны: ";
        if (riseOk) rise.showTime();
        else std::cout << "не найден";

        std::cout << "\nКульминация Луны: ";
        if (kulmOk) kulm.showTime();
        else std::cout << "не найдена";

        std::cout << "\nЗаход Луны: ";
        if (setOk) set.showTime();
        else std::cout << "не найден";

        std::cout << "\n";
    }
    catch (const char* msg) {
        std::cout << msg << "\n";
    }

    return 0;
}
