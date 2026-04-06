#include "DateTime.h"

bool DateTime::isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int DateTime::daysInMonth(int year, int month) {
    static const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeap(year)) {
        return 29;
    }
    return days[month];
}

bool DateTime::isValidTime(int hour, int minute, int second) {
    return hour >= 0 && hour < 24 &&
           minute >= 0 && minute < 60 &&
           second >= 0 && second < 60;
}

bool DateTime::isValidDate(int year, int month, int day, int hour, int minute, int second) {
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }
    if (day > daysInMonth(year, month)) {
        return false;
    }
    return isValidTime(hour, minute, second);
}

int DateTime::toDays() const {
    int days = 0;
    for (int yr = 1900; yr < year_; ++yr) {
        days += isLeap(yr) ? 366 : 365;
    }
    for (int mo = 1; mo < month_; ++mo) {
        days += daysInMonth(year_, mo);
    }
    days += day_;
    return days;
}

DateTime DateTime::fromDays(int totalDays) {
    int y = 1900;
    int remaining = totalDays;
    while (true) {
        int daysInYear = isLeap(y) ? 366 : 365;
        if (remaining <= daysInYear) {
            break;
        }
        remaining -= daysInYear;
        ++y;
    }
    int m = 1;
    while (true) {
        int dim = daysInMonth(y, m);
        if (remaining <= dim) {
            break;
        }
        remaining -= dim;
        ++m;
    }
    int d = remaining;
    return DateTime(y, m, d);
}

int DateTime::dayOfWeek() const {
    int y = year_;
    int m = month_;
    int q = day_;
    if (m < 3) {
        m += 12;
        --y;
    }
    int k = y % 100;
    int j = y / 100;
    int h = (q + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
    return (h + 6) % 7;
}

DateTime::DateTime() : year_(1900), month_(1), day_(1), hour_(0), minute_(0), second_(0) {}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
    : year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}

int DateTime::getYear() const { return year_; }
int DateTime::getMonth() const { return month_; }
int DateTime::getDay() const { return day_; }
int DateTime::getHour() const { return hour_; }
int DateTime::getMinute() const { return minute_; }
int DateTime::getSecond() const { return second_; }

void DateTime::setDateTime(int year, int month, int day, int hour, int minute, int second) {
    year_ = year;
    month_ = month;
    day_ = day;
    hour_ = hour;
    minute_ = minute;
    second_ = second;
}

bool DateTime::isValid() const {
    return isValidDate(year_, month_, day_, hour_, minute_, second_);
}

void DateTime::getDayOfWeekName(char* out, int outSize) const {
    static const char* names[] = {
        "Воскресенье", "Понедельник", "Вторник", "Среда",
        "Четверг", "Пятница", "Суббота"
    };
    int idx = dayOfWeek();
    int i = 0;
    while (names[idx][i] != '\0' && i < outSize - 1) {
        out[i] = names[idx][i];
        ++i;
    }
    out[i] = '\0';
}

DateTime DateTime::operator+(int days) const {
    int currentDays = toDays() + days;
    DateTime result = fromDays(currentDays);
    result.hour_ = hour_;
    result.minute_ = minute_;
    result.second_ = second_;
    return result;
}

DateTime DateTime::operator-(int days) const {
    return *this + (-days);
}

int DateTime::operator-(const DateTime& other) const {
    return toDays() - other.toDays();
}

bool DateTime::operator>(const DateTime& other) const {
    if (year_ != other.year_) return year_ > other.year_;
    if (month_ != other.month_) return month_ > other.month_;
    if (day_ != other.day_) return day_ > other.day_;
    if (hour_ != other.hour_) return hour_ > other.hour_;
    if (minute_ != other.minute_) return minute_ > other.minute_;
    return second_ > other.second_;
}

bool DateTime::operator>=(const DateTime& other) const {
    return !(*this < other);
}

bool DateTime::operator<(const DateTime& other) const {
    if (year_ != other.year_) return year_ < other.year_;
    if (month_ != other.month_) return month_ < other.month_;
    if (day_ != other.day_) return day_ < other.day_;
    if (hour_ != other.hour_) return hour_ < other.hour_;
    if (minute_ != other.minute_) return minute_ < other.minute_;
    return second_ < other.second_;
}

bool DateTime::operator<=(const DateTime& other) const {
    return !(*this > other);
}

bool DateTime::operator==(const DateTime& other) const {
    return year_ == other.year_ && month_ == other.month_ && day_ == other.day_ &&
           hour_ == other.hour_ && minute_ == other.minute_ && second_ == other.second_;
}

bool DateTime::operator!=(const DateTime& other) const {
    return !(*this == other);
}

static void printPadded(std::ostream& os, int value, int width) {
    if (value < 10 && width == 2) {
        os << '0' << value;
    } else if (value < 100 && width == 2) {
        os << value;
    } else if (value < 10 && width == 4) {
        os << "000" << value;
    } else if (value < 100 && width == 4) {
        os << "00" << value;
    } else if (value < 1000 && width == 4) {
        os << '0' << value;
    } else {
        os << value;
    }
}

static int parseNumber(const char* str, int& pos) {
    int result = 0;
    while (str[pos] >= '0' && str[pos] <= '9') {
        result = result * 10 + (str[pos] - '0');
        ++pos;
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
    printPadded(os, dt.year_, 4);
    os << '-';
    printPadded(os, dt.month_, 2);
    os << '-';
    printPadded(os, dt.day_, 2);
    os << 'T';
    printPadded(os, dt.hour_, 2);
    os << ':';
    printPadded(os, dt.minute_, 2);
    os << ':';
    printPadded(os, dt.second_, 2);
    return os;
}

std::istream& operator>>(std::istream& is, DateTime& dt) {
    char input[64];
    is >> input;

    bool hasDash = false;
    bool hasColon = false;
    bool hasT = false;
    int len = 0;
    while (input[len] != '\0') {
        if (input[len] == '-') hasDash = true;
        if (input[len] == ':') hasColon = true;
        if (input[len] == 'T') hasT = true;
        ++len;
    }

    int pos = 0;
    if (hasT && hasColon) {
        dt.year_ = parseNumber(input, pos);
        ++pos;
        dt.month_ = parseNumber(input, pos);
        ++pos;
        dt.day_ = parseNumber(input, pos);
        ++pos;
        dt.hour_ = parseNumber(input, pos);
        ++pos;
        dt.minute_ = parseNumber(input, pos);
        ++pos;
        dt.second_ = parseNumber(input, pos);
    } else if (hasColon && !hasDash) {
        dt.hour_ = parseNumber(input, pos);
        ++pos;
        dt.minute_ = parseNumber(input, pos);
        ++pos;
        dt.second_ = parseNumber(input, pos);
        dt.year_ = 1900;
        dt.month_ = 1;
        dt.day_ = 1;
    } else {
        dt.year_ = parseNumber(input, pos);
        ++pos;
        dt.month_ = parseNumber(input, pos);
        ++pos;
        dt.day_ = parseNumber(input, pos);
        dt.hour_ = 0;
        dt.minute_ = 0;
        dt.second_ = 0;
    }

    return is;
}

static void swapDT(DateTime& a, DateTime& b) {
    DateTime tmp = a;
    a = b;
    b = tmp;
}

void DateTime::quickSort(DateTime* arr, int low, int high) {
    if (low < high) {
        DateTime pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                swapDT(arr[i], arr[j]);
            }
        }
        swapDT(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void DateTime::quickSort(DateTime* arr, int count) {
    if (count > 1) {
        quickSort(arr, 0, count - 1);
    }
}