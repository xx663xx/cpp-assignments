#include <iostream>
#include <fstream>
#include "Labirint.h"

using namespace std;

Labirint::Labirint()
{
    pic = 0;
    w = h = row = 0;
    sx = sy = fx = fy = 0;
}

Labirint::~Labirint()
{
    delete[] pic;
}

int Labirint::getInt(int p)
{
    return head[p] + head[p + 1] * 256 + head[p + 2] * 256 * 256 + head[p + 3] * 256 * 256 * 256;
}

int Labirint::pos(int x, int y)
{
    return (h - 1 - y) * row + x * 3;
}

bool Labirint::isBlack(int x, int y)
{
    int p = pos(x, y);
    return pic[p] < 80 && pic[p + 1] < 80 && pic[p + 2] < 80;
}

void Labirint::putBlue(int x, int y)
{
    for (int yy = y - 2; yy <= y + 2; yy++)
        for (int xx = x - 2; xx <= x + 2; xx++)
            if (xx >= 0 && xx < w && yy >= 0 && yy < h && !isBlack(xx, yy))
            {
                int p = pos(xx, yy);
                pic[p] = 255;
                pic[p + 1] = 0;
                pic[p + 2] = 0;
            }
}

bool Labirint::load(const char *name)
{
    ifstream f(name, ios::binary);
    if (!f)
        return false;

    f.read((char *)head, 54);

    if (head[0] != 'B' || head[1] != 'M')
        return false;

    if (head[28] != 24)
        return false;

    w = getInt(18);
    h = getInt(22);
    row = (w * 3 + 3) / 4 * 4;

    delete[] pic;
    pic = new unsigned char[row * h];

    f.read((char *)pic, row * h);
    f.close();

    return true;
}

bool Labirint::findWay()
{
    if (pic == 0)
        return false;

    int red = 0, green = 0;
    long redX = 0, redY = 0, greenX = 0, greenY = 0;

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
        {
            int p = pos(x, y);
            int b = pic[p];
            int g = pic[p + 1];
            int r = pic[p + 2];

            if (r > 150 && g < 120 && b < 120)
            {
                redX += x;
                redY += y;
                red++;
            }

            if (g > 120 && r < 120 && b < 120)
            {
                greenX += x;
                greenY += y;
                green++;
            }
        }

    if (red == 0 || green == 0)
        return false;

    fx = redX / red;
    fy = redY / red;
    sx = greenX / green;
    sy = greenY / green;

    int n = w * h;
    int *a = new int[n];
    int *qx = new int[n];
    int *qy = new int[n];

    for (int i = 0; i < n; i++)
        a[i] = -1;

    int begin = 0, end = 0;
    qx[end] = sx;
    qy[end] = sy;
    end++;
    a[sy * w + sx] = 0;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while (begin < end)
    {
        int x = qx[begin];
        int y = qy[begin];
        begin++;

        if (x == fx && y == fy)
            break;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < w && ny >= 0 && ny < h)
                if (a[ny * w + nx] == -1 && !isBlack(nx, ny))
                {
                    a[ny * w + nx] = a[y * w + x] + 1;
                    qx[end] = nx;
                    qy[end] = ny;
                    end++;
                }
        }
    }

    if (a[fy * w + fx] == -1)
    {
        delete[] a;
        delete[] qx;
        delete[] qy;
        return false;
    }

    int x = fx;
    int y = fy;

    while (!(x == sx && y == sy))
    {
        putBlue(x, y);

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < w && ny >= 0 && ny < h)
                if (a[ny * w + nx] == a[y * w + x] - 1)
                {
                    x = nx;
                    y = ny;
                    break;
                }
        }
    }

    delete[] a;
    delete[] qx;
    delete[] qy;

    return true;
}

bool Labirint::save(const char *name)
{
    if (pic == 0)
        return false;

    ofstream f(name, ios::binary);
    if (!f)
        return false;

    f.write((char *)head, 54);
    f.write((char *)pic, row * h);
    f.close();

    return true;
}
