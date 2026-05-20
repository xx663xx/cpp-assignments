#include <iostream>
#include "Labirint.h"

using namespace std;

int main()
{
    // Файлы заданы сразу, чтобы каждый раз не вводить их руками.
    const char *inName = "ДНК_Лабиринт.bmp";
    const char *outName = "result.bmp";

    cout << "Входной файл: " << inName << endl;
    cout << "Выходной файл: " << outName << endl;

    Labirint lab;

    // Сначала читаем BMP-файл в память.
    if (!lab.load(inName))
    {
        cout << "Не получилось открыть BMP файл." << endl;
        return 1;
    }

    // Потом ищем путь и сразу закрашиваем его на картинке.
    if (!lab.findWay())
    {
        cout << "Путь не найден." << endl;
        return 1;
    }

    // Сохраняем уже измененную картинку в новый файл.
    if (!lab.save(outName))
    {
        cout << "Не получилось сохранить файл." << endl;
        return 1;
    }

    cout << "Готово, путь записан в файл " << outName << endl;

    return 0;
}
