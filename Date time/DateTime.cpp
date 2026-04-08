#include "DateTime.h"

DateTime::DateTime() {
    year = 1900;
    month = 1;
    day = 1;
    hour = 0;
    minute = 0;
    second = 0;
}

DateTime::DateTime(int y, int m, int d, int h, int min, int s) {
    year = y;
    month = m;
    day = d;
    hour = h;
    minute = min;
    second = s;
}

bool DateTime::isLeapYear(int y) const {
    if (y % 400 == 0) {
        return true;
    }
    if (y % 100 == 0) {
        return false;
    }
    if (y % 4 == 0) {
        return true;
    }
    return false;
}

int DateTime::daysInMonth(int y, int m) const {
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
        return 31;
    }
    if (m == 4 || m == 6 || m == 9 || m == 11) {
        return 30;
    }
    if (m == 2) {
        if (isLeapYear(y)) {
            return 29;
        }
        return 28;
    }
    return 0;
}

bool DateTime::isValid() const {
    if (year < 1) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > daysInMonth(year, month)) {
        return false;
    }
    if (hour < 0 || hour > 23) {
        return false;
    }
    if (minute < 0 || minute > 59) {
        return false;
    }
    if (second < 0 || second > 59) {
        return false;
    }
    return true;
}

bool DateTime::setFromString(const char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len == 10) {
        year = (str[0] - '0') * 1000 + (str[1] - '0') * 100 + (str[2] - '0') * 10 + (str[3] - '0');
        month = (str[5] - '0') * 10 + (str[6] - '0');
        day = (str[8] - '0') * 10 + (str[9] - '0');
        hour = 0;
        minute = 0;
        second = 0;
        return isValid();
    }

    if (len == 8) {
        year = 1900;
        month = 1;
        day = 1;
        hour = (str[0] - '0') * 10 + (str[1] - '0');
        minute = (str[3] - '0') * 10 + (str[4] - '0');
        second = (str[6] - '0') * 10 + (str[7] - '0');
        return isValid();
    }

    if (len == 19) {
        year = (str[0] - '0') * 1000 + (str[1] - '0') * 100 + (str[2] - '0') * 10 + (str[3] - '0');
        month = (str[5] - '0') * 10 + (str[6] - '0');
        day = (str[8] - '0') * 10 + (str[9] - '0');
        hour = (str[11] - '0') * 10 + (str[12] - '0');
        minute = (str[14] - '0') * 10 + (str[15] - '0');
        second = (str[17] - '0') * 10 + (str[18] - '0');
        return isValid();
    }

    return false;
}

void DateTime::input() {
    char str[25];
    cin >> str;

    if (!setFromString(str)) {
        cout << "Некорректная дата или время\n";
    }
}

int DateTime::toDays() const {
    int total = 0;

    for (int y = 1; y < year; y++) {
        if (isLeapYear(y)) {
            total += 366;
        } else {
            total += 365;
        }
    }

    for (int m = 1; m < month; m++) {
        total += daysInMonth(year, m);
    }

    total += day;

    return total;
}

void DateTime::fromDays(int totalDays) {
    year = 1;

    while (true) {
        int daysInYear;
        if (isLeapYear(year)) {
            daysInYear = 366;
        } else {
            daysInYear = 365;
        }

        if (totalDays > daysInYear) {
            totalDays -= daysInYear;
            year++;
        } else {
            break;
        }
    }

    month = 1;
    while (totalDays > daysInMonth(year, month)) {
        totalDays -= daysInMonth(year, month);
        month++;
    }

    day = totalDays;
    hour = 0;
    minute = 0;
    second = 0;
}

const char* DateTime::dayOfWeek() const {
    int days = toDays();
    int number = days % 7;

    if (number == 1) return "Понедельник";
    if (number == 2) return "Вторник";
    if (number == 3) return "Среда";
    if (number == 4) return "Четверг";
    if (number == 5) return "Пятница";
    if (number == 6) return "Суббота";
    return "Воскресенье";
}

void DateTime::printDate() const {
    cout << year << "-";
    if (month < 10) cout << "0";
    cout << month << "-";
    if (day < 10) cout << "0";
    cout << day;
}

void DateTime::printTime() const {
    if (hour < 10) cout << "0";
    cout << hour << ":";
    if (minute < 10) cout << "0";
    cout << minute << ":";
    if (second < 10) cout << "0";
    cout << second;
}

void DateTime::printDateTime() const {
    printDate();
    cout << "T";
    printTime();
}

int DateTime::operator-(const DateTime& other) const {
    return toDays() - other.toDays();
}

DateTime DateTime::operator+(int days) const {
    DateTime temp = *this;
    int totalDays = temp.toDays() + days;
    temp.fromDays(totalDays);
    return temp;
}

bool DateTime::operator>(const DateTime& other) const {
    if (year != other.year) return year > other.year;
    if (month != other.month) return month > other.month;
    if (day != other.day) return day > other.day;
    if (hour != other.hour) return hour > other.hour;
    if (minute != other.minute) return minute > other.minute;
    return second > other.second;
}

bool DateTime::operator>=(const DateTime& other) const {
    return (*this > other) || (*this == other);
}

bool DateTime::operator<(const DateTime& other) const {
    return !(*this >= other);
}

bool DateTime::operator<=(const DateTime& other) const {
    return !(*this > other);
}

bool DateTime::operator==(const DateTime& other) const {
    return year == other.year &&
           month == other.month &&
           day == other.day &&
           hour == other.hour &&
           minute == other.minute &&
           second == other.second;
}

void quickSort(DateTime arr[], int left, int right) {
    int i = left;
    int j = right;
    DateTime middle = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < middle) {
            i++;
        }
        while (arr[j] > middle) {
            j--;
        }

        if (i <= j) {
            DateTime temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(arr, left, j);
    }
    if (i < right) {
        quickSort(arr, i, right);
    }
}
