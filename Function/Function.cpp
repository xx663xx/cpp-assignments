#include <iostream>
#include <cmath>
#include "Function.h"

using namespace std;

double Function::minimum(double a, double b) {
    // Если интервал состоит из одной точки, то минимум равен f(a).
    if (a == b)
        return f(a);

    // Идем по интервалу маленькими шагами и просто ищем меньшее значение.
    // Это не 100% точный математический метод.
    double h = (b - a) / 1000;
    double mn = f(a);

    for (double x = a; x <= b; x += h) {
        if (f(x) < mn)
            mn = f(x);
    }

    return mn;
}

double Function::maximum(double a, double b) {
    // Для одной точки максимум тоже равен значению функции в этой точке.
    if (a == b)
        return f(a);

    // Максимум ищется так же перебором точек на интервале.
    double h = (b - a) / 1000;
    double mx = f(a);

    for (double x = a; x <= b; x += h) {
        if (f(x) > mx)
            mx = f(x);
    }

    return mx;
}

double Function::integral(double a, double b) {
    // На нулевом интервале площадь равна нулю.
    if (a == b)
        return 0;

    // Интеграл считается приближенно как сумма прямоугольников.
    double h = (b - a) / 1000;
    double s = 0;

    for (double x = a; x < b; x += h)
        s += f(x) * h;

    return s;
}

double Function::derivative(double x) {
    // Производная считается приближенно по значениям слева и справа от x.
    double h = 0.0001;
    return (f(x + h) - f(x - h)) / (2 * h);
}

Function::~Function() {
    // В базовом классе ничего удалять не надо.
}

Hiperbola::Hiperbola(double aa, double bb) {
    // Сохраняем коэффициенты гиперболы.
    a = aa;
    b = bb;
}

double Hiperbola::f(double x) {
    // Делить на ноль нельзя, поэтому выводим сообщение и возвращаем 0.
    if (x == 0) {
        cout << "x = 0 нельзя для гиперболы\n";
        return 0;
    }
    return a / x + b;
}

void Hiperbola::print(double x) {
    cout << "y = " << a << " / x + " << b << endl;
    cout << "f(" << x << ") = " << f(x) << endl;
}

Parabola::Parabola(double aa, double bb, double cc) {
    // Сохраняем коэффициенты квадратной функции.
    a = aa;
    b = bb;
    c = cc;
}

double Parabola::f(double x) {
    return a * x * x + b * x + c;
}

void Parabola::print(double x) {
    cout << "y = " << a << "*x^2 + " << b << "*x + " << c << endl;
    cout << "f(" << x << ") = " << f(x) << endl;
}

Exponenta::Exponenta(double aa, double bb, double cc) {
    // Сохраняем коэффициенты показательной функции.
    a = aa;
    b = bb;
    c = cc;
}

double Exponenta::f(double x) {
    return a * exp(b * x) + c;
}

void Exponenta::print(double x) {
    cout << "y = " << a << "*e^(" << b << "*x) + " << c << endl;
    cout << "f(" << x << ") = " << f(x) << endl;
}

Polinom::Polinom(int nn, double *aa) {
    n = nn;

    // Создаем свой массив, чтобы объект Polinom сам хранил коэффициенты.
    a = new double[n + 1];

    for (int i = 0; i <= n; i++)
        a[i] = aa[i];
}

double Polinom::f(double x) {
    double y = 0;
    double p = 1;

    // p хранит текущую степень x: 1, x, x^2 и так далее.
    for (int i = 0; i <= n; i++) {
        y += a[i] * p;
        p *= x;
    }

    return y;
}

void Polinom::print(double x) {
    cout << "Полином степени " << n << endl;
    cout << "f(" << x << ") = " << f(x) << endl;
}

Polinom::~Polinom() {
    // Освобождаем память, которую выделяли под коэффициенты.
    delete[] a;
}
