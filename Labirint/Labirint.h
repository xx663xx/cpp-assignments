#ifndef LABIRINT_H
#define LABIRINT_H

class Labirint
{
private:
    // Первые 54 байта BMP-файла. Там лежат размеры картинки и другая служебная информация.
    unsigned char head[54];

    // Сами пиксели картинки. Для 24-битного BMP один пиксель занимает 3 байта.
    unsigned char *pic;

    // w и h - ширина и высота, row - длина одной строки BMP с выравниванием.
    int w, h, row;

    // sx, sy - вход в лабиринт, fx, fy - выход из лабиринта.
    int sx, sy, fx, fy;

    int getInt(int p);
    int pos(int x, int y);
    bool isBlack(int x, int y);
    void putBlue(int x, int y);

public:
    Labirint();
    ~Labirint();

    bool load(const char *name);
    bool findWay();
    bool save(const char *name);
};

#endif
