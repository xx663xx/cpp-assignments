#ifndef LABIRINT_H
#define LABIRINT_H

class Labirint
{
private:
    unsigned char head[54];
    unsigned char *pic;
    int w, h, row;
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
