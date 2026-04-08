#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <cmath>

class Rational
{
private:
    int numer;
    int denom;

    void simplify();
    void limitPrecision(int maxDenom);
    static int gcdInt(int a, int b);
    static bool fitsInt(long long value);
    static const int LIMIT = 2147483647;

public:
    Rational();
    Rational(int number);
    Rational(int n, int d);

    int getNumerator() const;
    int getDenominator() const;

    Rational absValue() const;
    Rational sqrtRational() const;

    Rational& operator +=(const Rational& r);
    Rational operator +(const Rational& r) const;

    Rational operator -() const;
    Rational& operator -=(const Rational& r);
    Rational operator -(const Rational& r) const;

    Rational& operator *=(const Rational& r);
    Rational operator *(const Rational& r) const;

    Rational& operator /=(const Rational& r);
    Rational operator /(const Rational& r) const;

    Rational& operator ++();
    Rational operator ++(int);

    bool operator ==(const Rational& r) const;
    bool operator !=(const Rational& r) const;
    bool operator <(const Rational& r) const;
    bool operator >(const Rational& r) const;
    bool operator <=(const Rational& r) const;
    bool operator >=(const Rational& r) const;

    friend std::istream& operator >>(std::istream& in, Rational& r);
    friend std::ostream& operator <<(std::ostream& out, const Rational& r);
};

#endif