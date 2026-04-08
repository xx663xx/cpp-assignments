#include <iostream>
#include "rational.h"

int main()
{
    Rational a;
    Rational b;
    Rational c;

    std::cout << "Введите a (числитель знаменатель): ";
    std::cin >> a;
    std::cout << "Введите b (числитель знаменатель): ";
    std::cin >> b;
    std::cout << "Введите c (числитель знаменатель): ";
    std::cin >> c;

    if (a == Rational(0))
    {
        if (b == Rational(0))
        {
            if (c == Rational(0))
            {
                std::cout << "Бесконечно много решений\n";
            }
            else
            {
                std::cout << "Решений нет\n";
            }
        }
        else
        {
            Rational x = (-c) / b;
            std::cout << "Линейное уравнение\n";
            std::cout << "x = " << x << "\n";
        }
        return 0;
    }

    Rational d = b * b - Rational(4) * a * c;
    std::cout << "D = " << d << "\n";

    if (d < Rational(0))
    {
        std::cout << "Действительных корней нет\n";
        return 0;
    }

    if (d == Rational(0))
    {
        Rational x = (-b) / (Rational(2) * a);
        std::cout << "Один корень\n";
        std::cout << "x = " << x << "\n";
        return 0;
    }

    Rational sqrtD = d.sqrtRational();
    Rational x1 = (-b - sqrtD) / (Rational(2) * a);
    Rational x2 = (-b + sqrtD) / (Rational(2) * a);

    std::cout << "sqrt(D) = " << sqrtD << "\n";
    std::cout << "x1 = " << x1 << "\n";
    std::cout << "x2 = " << x2 << "\n";

    return 0;
}
