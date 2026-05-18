#include <iostream>
#include <clocale>
#include "Function.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // Указатель базового класса. В него потом запишем адрес выбранной функции.
    Function *fun = 0;
    int num;
    double a, b, c, x, l, r;

    // Сначала пользователь выбирает, с какой функцией работать.
    cout << "Выберите функцию:\n";
    cout << "1 - Гипербола y = a / x + b\n";
    cout << "2 - Парабола y = a*x^2 + b*x + c\n";
    cout << "3 - Экспонента y = a*e^(b*x) + c\n";
    cout << "4 - Полином y = a0 + a1*x + ... + an*x^n\n";
    cout << "Ваш выбор: ";
    cin >> num;

    // По номеру создается нужный объект.
    // Дальше программа работает с ним через общий указатель fun.
    switch (num) {
    case 1:
        cout << "Введите a и b через пробел: ";
        cin >> a >> b;
        fun = new Hiperbola(a, b);
        break;
    case 2:
        cout << "Введите a, b, c через пробел: ";
        cin >> a >> b >> c;
        fun = new Parabola(a, b, c);
        break;
    case 3:
        cout << "Введите a, b, c через пробел: ";
        cin >> a >> b >> c;
        fun = new Exponenta(a, b, c);
        break;
    case 4: {
        int n;
        cout << "Введите степень полинома n: ";
        cin >> n;

        // Отрицательной степени у обычного полинома здесь не рассматриваем.
        if (n < 0) {
            cout << "Степень не может быть отрицательной\n";
            return 0;
        }

        double *k = new double[n + 1];

        // Коэффициенты вводятся от свободного члена к старшей степени.
        cout << "Введите коэффициенты a0 a1 ... an через пробел:\n";
        for (int i = 0; i <= n; i++)
            cin >> k[i];

        // Polinom копирует коэффициенты в свой массив, поэтому k можно удалить.
        fun = new Polinom(n, k);
        delete[] k;
        break;
    }
    default:
        cout << "Нет такого варианта\n";
        return 0;
    }

    // Точка нужна для обычного вычисления f(x) и производной.
    cout << "Введите x для вычисления f(x): ";
    cin >> x;

    // Интервал нужен для минимума, максимума и интеграла.
    cout << "Введите интервал [a b] для минимума, максимума и интеграла: ";
    cin >> l >> r;

    // Если пользователь ввел границы наоборот, меняем их местами.
    if (l > r) {
        double t = l;
        l = r;
        r = t;
    }

    // Все вычисления вызываются через указатель на базовый класс.
    fun->print(x);
    cout << "Минимум на интервале = " << fun->minimum(l, r) << endl;
    cout << "Максимум на интервале = " << fun->maximum(l, r) << endl;
    cout << "Интеграл на интервале = " << fun->integral(l, r) << endl;
    cout << "Производная в точке x = " << fun->derivative(x) << endl;

    // Удаляем созданный объект перед завершением программы.
    delete fun;
    return 0;
}
