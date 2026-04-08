#include "rational.h"

int Rational::gcdInt(int a, int b)
{
    a = std::abs(a);
    b = std::abs(b);

    while (b != 0)
    {
        int t = a % b;
        a = b;
        b = t;
    }

    if (a == 0)
    {
        return 1;
    }

    return a;
}

bool Rational::fitsInt(long long value)
{
    return value >= -LIMIT && value <= LIMIT;
}

void Rational::simplify()
{
    if (denom == 0)
    {
        numer = 0;
        denom = 1;
        return;
    }

    if (denom < 0)
    {
        numer = -numer;
        denom = -denom;
    }

    if (numer == 0)
    {
        denom = 1;
        return;
    }

    int g = gcdInt(numer, denom);
    numer /= g;
    denom /= g;
}

void Rational::limitPrecision(int maxDenom)
{
    simplify();

    if (denom <= maxDenom)
    {
        return;
    }

    long long scaled = (long long)numer * maxDenom;
    long long q = scaled / denom;
    long long rem = std::abs(scaled % denom);

    if (rem * 2 >= denom)
    {
        if (scaled >= 0)
        {
            q++;
        }
        else
        {
            q--;
        }
    }

    if (!fitsInt(q))
    {
        q = 0;
    }

    numer = (int)q;
    denom = maxDenom;
    simplify();
}

Rational::Rational()
{
    numer = 0;
    denom = 1;
}

Rational::Rational(int number)
{
    numer = number;
    denom = 1;
}

Rational::Rational(int n, int d)
{
    numer = n;
    if (d == 0)
    {
        denom = 1;
    }
    else
    {
        denom = d;
    }
    simplify();
}

int Rational::getNumerator() const
{
    return numer;
}

int Rational::getDenominator() const
{
    return denom;
}

Rational Rational::absValue() const
{
    if (numer < 0)
    {
        return Rational(-numer, denom);
    }
    return *this;
}

Rational Rational::sqrtRational() const
{
    if (*this < Rational(0))
    {
        return Rational(0);
    }

    if (*this == Rational(0))
    {
        return Rational(0);
    }

    Rational x;
    if (*this > Rational(1))
    {
        x = *this;
    }
    else
    {
        x = Rational(1);
    }

    Rational prev;
    Rational eps(1, 10000);

    for (int i = 0; i < 20; i++)
    {
        prev = x;
        x = (x + (*this / x)) / Rational(2);
        x.limitPrecision(10000);

        if ((x - prev).absValue() < eps)
        {
            break;
        }
    }

    return x;
}

Rational& Rational::operator +=(const Rational& r)
{
    int g = gcdInt(denom, r.denom);
    long long left = (long long)numer * (r.denom / g);
    long long right = (long long)r.numer * (denom / g);
    long long newNumer = left + right;
    long long newDenom = (long long)(denom / g) * r.denom;

    if (!fitsInt(newNumer) || !fitsInt(newDenom))
    {
        return *this;
    }

    numer = (int)newNumer;
    denom = (int)newDenom;
    simplify();
    return *this;
}

Rational Rational::operator +(const Rational& r) const
{
    Rational res(*this);
    return res += r;
}

Rational Rational::operator -() const
{
    return Rational(-numer, denom);
}

Rational& Rational::operator -=(const Rational& r)
{
    return (*this += (-r));
}

Rational Rational::operator -(const Rational& r) const
{
    Rational res(*this);
    return res -= r;
}

Rational& Rational::operator *=(const Rational& r)
{
    int a = numer;
    int b = denom;
    int c = r.numer;
    int d = r.denom;

    int g1 = gcdInt(a, d);
    int g2 = gcdInt(c, b);

    a /= g1;
    d /= g1;
    c /= g2;
    b /= g2;

    long long newNumer = (long long)a * c;
    long long newDenom = (long long)b * d;

    if (!fitsInt(newNumer) || !fitsInt(newDenom))
    {
        return *this;
    }

    numer = (int)newNumer;
    denom = (int)newDenom;
    simplify();
    return *this;
}

Rational Rational::operator *(const Rational& r) const
{
    Rational res(*this);
    return res *= r;
}

Rational& Rational::operator /=(const Rational& r)
{
    if (r.numer == 0)
    {
        return *this;
    }

    return (*this *= Rational(r.denom, r.numer));
}

Rational Rational::operator /(const Rational& r) const
{
    Rational res(*this);
    return res /= r;
}

Rational& Rational::operator ++()
{
    *this += Rational(1);
    return *this;
}

Rational Rational::operator ++(int)
{
    Rational old(*this);
    *this += Rational(1);
    return old;
}

bool Rational::operator ==(const Rational& r) const
{
    return numer == r.numer && denom == r.denom;
}

bool Rational::operator !=(const Rational& r) const
{
    return !(*this == r);
}

bool Rational::operator <(const Rational& r) const
{
    long long left = (long long)numer * r.denom;
    long long right = (long long)r.numer * denom;
    return left < right;
}

bool Rational::operator >(const Rational& r) const
{
    return r < *this;
}

bool Rational::operator <=(const Rational& r) const
{
    return !(*this > r);
}

bool Rational::operator >=(const Rational& r) const
{
    return !(*this < r);
}

std::istream& operator >>(std::istream& in, Rational& r)
{
    in >> r.numer >> r.denom;
    if (r.denom == 0)
    {
        r.numer = 0;
        r.denom = 1;
    }
    r.simplify();
    return in;
}

std::ostream& operator <<(std::ostream& out, const Rational& r)
{
    out << r.numer;
    if (r.denom != 1)
    {
        out << "/" << r.denom;
    }
    return out;
}