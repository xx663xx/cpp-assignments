#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>

using namespace std;

class DateTime {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

public:
    DateTime();
    DateTime(int y, int m, int d, int h = 0, int min = 0, int s = 0);

    void input();
    bool setFromString(const char str[]);
    bool isValid() const;

    bool isLeapYear(int y) const;
    int daysInMonth(int y, int m) const;
    int toDays() const;
    void fromDays(int totalDays);
    const char* dayOfWeek() const;

    void printDate() const;
    void printTime() const;
    void printDateTime() const;

    int operator-(const DateTime& other) const;
    DateTime operator+(int days) const;

    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator==(const DateTime& other) const;
};

void quickSort(DateTime arr[], int left, int right);

#endif