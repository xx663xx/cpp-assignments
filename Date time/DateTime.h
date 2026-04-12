#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>

class DateTime {
private:
    int y;
    int mo;
    int d;
    int h;
    int mi;
    int s;

public:
    DateTime();
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

    void readDate();
    void readFull();
    void showDate() const;
    void showTime() const;
    void showFull() const;

    bool ok() const;
    int getWeekDay() const;
    int countDays() const;

    int operator-(const DateTime& other) const;
    DateTime operator+(int plusDays) const;

    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator==(const DateTime& other) const;
};

void sortDates(DateTime arr[], int left, int right);
void showWeekDayName(int num);

#endif