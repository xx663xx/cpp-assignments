#include "datetime.h"

DateTime::DateTime() {
    y = 2000;
    mo = 1;
    d = 1;
    h = 0;
    mi = 0;
    s = 0;
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) {
    y = year;
    mo = month;
    d = day;
    h = hour;
    mi = minute;
    s = second;
}

void DateTime::readDate() {
    char x1, x2;

    while (true) {
        try {
            std::cout << "Введите дату, формат год-месяц-день: ";
            std::cin >> y >> x1 >> mo >> x2 >> d;

            h = 0;
            mi = 0;
            s = 0;

            if (std::cin.fail()) {
                throw "Ошибка ввода";
            }

            if (x1 != '-' || x2 != '-') {
                throw "Неправильный формат. Пример: 2021-12-21";
            }

            if (!ok()) {
                throw "Дата введена неверно";
            }

            break;
        }
        catch (const char* msg) {
            std::cout << msg << "\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}

void DateTime::readFull() {
    char x1, x2, x3, x4, x5;

    while (true) {
        try {
            std::cout << "Введите дату и время, формат год-месяц-деньTчасы:минуты:секунды: ";
            std::cin >> y >> x1 >> mo >> x2 >> d >> x3 >> h >> x4 >> mi >> x5 >> s;

            if (x1 != '-' || x2 != '-' || x3 != 'T' || x4 != ':' || x5 != ':') {
                throw "Неправильный формат. Пример: 2026-04-08T14:26:53";
            }

            if (!ok()) {
                throw "Дата или время введены неверно";
            }

            break;
        }
        catch (const char* msg) {
            std::cout << msg << "\n";
        }
    }
}

void DateTime::showDate() const {
    if (y < 1000) std::cout << '0';
    if (y < 100) std::cout << '0';
    if (y < 10) std::cout << '0';
    std::cout << y << "-";

    if (mo < 10) std::cout << '0';
    std::cout << mo << "-";

    if (d < 10) std::cout << '0';
    std::cout << d;
}

void DateTime::showTime() const {
    if (h < 10) std::cout << '0';
    std::cout << h << ":";

    if (mi < 10) std::cout << '0';
    std::cout << mi << ":";

    if (s < 10) std::cout << '0';
    std::cout << s;
}

void DateTime::showFull() const {
    showDate();
    std::cout << "T";
    showTime();
}

bool DateTime::ok() const {
    if (y < 1) return false;
    if (mo < 1 || mo > 12) return false;
    if (d < 1) return false;
    if (h < 0 || h > 23) return false;
    if (mi < 0 || mi > 59) return false;
    if (s < 0 || s > 59) return false;

    int mDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
        mDays[1] = 29;
    }

    if (d > mDays[mo - 1]) return false;

    return true;
}

int DateTime::countDays() const {
    int sum = 0;

    for (int year = 1; year < y; year++) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            sum += 366;
        } else {
            sum += 365;
        }
    }

    int mDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
        mDays[1] = 29;
    }

    for (int i = 0; i < mo - 1; i++) {
        sum += mDays[i];
    }

    sum += d;

    return sum;
}

int DateTime::getWeekDay() const {
    int day = d;
    int month = mo;
    int year = y;

    if (month < 3) {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;
    int res = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

    if (res == 0) return 6;
    if (res == 1) return 7;
    return res - 1;
}

int DateTime::operator-(const DateTime& other) const {
    return countDays() - other.countDays();
}

DateTime DateTime::operator+(int plusDays) const {
    DateTime ans = *this;

    while (plusDays > 0) {
        int mDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if ((ans.y % 4 == 0 && ans.y % 100 != 0) || ans.y % 400 == 0) {
            mDays[1] = 29;
        }

        ans.d++;

        if (ans.d > mDays[ans.mo - 1]) {
            ans.d = 1;
            ans.mo++;

            if (ans.mo > 12) {
                ans.mo = 1;
                ans.y++;
            }
        }

        plusDays--;
    }

    return ans;
}

bool DateTime::operator>(const DateTime& other) const {
    if (y != other.y) return y > other.y;
    if (mo != other.mo) return mo > other.mo;
    if (d != other.d) return d > other.d;
    if (h != other.h) return h > other.h;
    if (mi != other.mi) return mi > other.mi;
    return s > other.s;
}

bool DateTime::operator>=(const DateTime& other) const {
    return *this > other || *this == other;
}

bool DateTime::operator<(const DateTime& other) const {
    if (y != other.y) return y < other.y;
    if (mo != other.mo) return mo < other.mo;
    if (d != other.d) return d < other.d;
    if (h != other.h) return h < other.h;
    if (mi != other.mi) return mi < other.mi;
    return s < other.s;
}

bool DateTime::operator<=(const DateTime& other) const {
    return *this < other || *this == other;
}

bool DateTime::operator==(const DateTime& other) const {
    return y == other.y && mo == other.mo && d == other.d &&
           h == other.h && mi == other.mi && s == other.s;
}

void sortDates(DateTime arr[], int left, int right) {
    int i = left;
    int j = right;
    DateTime mid = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < mid) {
            i++;
        }

        while (arr[j] > mid) {
            j--;
        }

        if (i <= j) {
            DateTime t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
            i++;
            j--;
        }
    }

    if (left < j) sortDates(arr, left, j);
    if (i < right) sortDates(arr, i, right);
}

void showWeekDayName(int num) {
    switch (num) {
        case 1:
            std::cout << "Понедельник";
            break;
        case 2:
            std::cout << "Вторник";
            break;
        case 3:
            std::cout << "Среда";
            break;
        case 4:
            std::cout << "Четверг";
            break;
        case 5:
            std::cout << "Пятница";
            break;
        case 6:
            std::cout << "Суббота";
            break;
        case 7:
            std::cout << "Воскресенье";
            break;
        default:
            std::cout << "Неизвестно";
            break;
    }
}