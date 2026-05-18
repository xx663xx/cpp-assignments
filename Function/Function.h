#ifndef FUNCTION_H
#define FUNCTION_H

// Абстрактный класс Function задает общий вид любой функции.
// Через указатель на Function можно работать с любой дочерней функцией.
class Function {
public:
    // Значение функции в точке x. В каждом классе формула своя.
    virtual double f(double x) = 0;

    // Вывод формулы функции и значения в заданной точке.
    virtual void print(double x) = 0;

    // Эти методы общие для всех функций, потому что используют f(x).
    virtual double minimum(double a, double b);
    virtual double maximum(double a, double b);
    virtual double integral(double a, double b);
    virtual double derivative(double x);

    virtual ~Function();
};

class Hiperbola : public Function {
    double a, b;
public:
    // y = a / x + b
    Hiperbola(double aa, double bb);
    double f(double x);
    void print(double x);
};

class Parabola : public Function {
    double a, b, c;
public:
    // y = a*x^2 + b*x + c
    Parabola(double aa, double bb, double cc);
    double f(double x);
    void print(double x);
};

class Exponenta : public Function {
    double a, b, c;
public:
    // y = a*e^(b*x) + c
    Exponenta(double aa, double bb, double cc);
    double f(double x);
    void print(double x);
};

class Polinom : public Function {
    int n;

    // Массив коэффициентов: a[0] + a[1]*x + ... + a[n]*x^n
    double *a;
public:
    Polinom(int nn, double *aa);
    double f(double x);
    void print(double x);
    ~Polinom();
};

#endif
