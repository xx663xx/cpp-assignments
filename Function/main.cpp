#include <iostream>
#include <clocale>
#include <vector>
#include "Function.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // Вектор указателей на базовый класс.
    // В нем могут храниться адреса объектов разных дочерних классов.
    vector<Function*> functions;
    double a, b, c, x, l, r;

    cout << "Введите a и b для гиперболы y = a / x + b: ";
    cin >> a >> b;
    functions.push_back(new Hiperbola(a, b));

    cout << "Введите a, b, c для параболы y = a*x^2 + b*x + c: ";
    cin >> a >> b >> c;
    functions.push_back(new Parabola(a, b, c));

    cout << "Введите a, b, c для экспоненты y = a*e^(b*x) + c: ";
    cin >> a >> b >> c;
    functions.push_back(new Exponenta(a, b, c));

    int n;
    cout << "Введите степень полинома n: ";
    cin >> n;

    // Отрицательной степени у обычного полинома здесь не рассматриваем.
    if (n < 0) {
        cout << "Степень не может быть отрицательной\n";
        for (int i = 0; i < 3; i++)
            delete functions[i];
        return 0;
    }

    double *k = new double[n + 1];

    // Коэффициенты вводятся от свободного члена к старшей степени.
    cout << "Введите коэффициенты полинома a0 a1 ... an через пробел:\n";
    for (int i = 0; i <= n; i++)
        cin >> k[i];

    // Polinom копирует коэффициенты в свой массив, поэтому k можно удалить.
    functions.push_back(new Polinom(n, k));
    delete[] k;

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

    // Все вычисления вызываются через указатели на базовый класс.
    for (int i = 0; i < 4; i++) {
        cout << "\nФункция " << i + 1 << endl;
        functions[i]->print(x);
        cout << "Минимум на интервале = " << functions[i]->minimum(l, r) << endl;
        cout << "Максимум на интервале = " << functions[i]->maximum(l, r) << endl;
        cout << "Интеграл на интервале = " << functions[i]->integral(l, r) << endl;
        cout << "Производная в точке x = " << functions[i]->derivative(x) << endl;
    }

    // Удаляем все созданные объекты перед завершением программы.
    for (int i = 0; i < 4; i++)
        delete functions[i];

    return 0;
}
