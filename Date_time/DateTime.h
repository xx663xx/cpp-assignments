#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>

class DateTime {
private:
    int year_;
    int month_;
    int day_;
    int hour_;
    int minute_;
    int second_;

    static bool isLeap(int year);
    static int daysInMonth(int year, int month);
    static bool isValidDate(int year, int month, int day, int hour, int minute, int second);
    static bool isValidTime(int hour, int minute, int second);

    int toDays() const;
    static DateTime fromDays(int totalDays);

    int dayOfWeek() const;

public:
    DateTime();
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    void setDateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

    bool isValid() const;

    void getDayOfWeekName(char* out, int outSize) const;

    DateTime operator+(int days) const;
    DateTime operator-(int days) const;
    int operator-(const DateTime& other) const;

    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;

    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);
    friend std::istream& operator>>(std::istream& is, DateTime& dt);

    static void quickSort(DateTime* arr, int low, int high);
    static void quickSort(DateTime* arr, int count);
};

#endif