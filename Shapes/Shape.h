#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <vector>

struct Point {
    double x;
    double y;

    Point();
    Point(double x, double y);
};

// Базовый абстрактный класс. через него main.cpp работает с любыми фигурами одинаково.
class Shape {
public:
    virtual double calc_area() const = 0;
    virtual double calc_perimetr() const = 0;
    virtual std::string name() const = 0;
    virtual ~Shape();
};

class Rectangle : public Shape {
private:
    double a;
    double b;

public:
    Rectangle(double a, double b);
    Rectangle(const Point& leftTop, const Point& rightBottom);
    // Конструктор по вершинам. прямоугольник можно задавать координатами.
    Rectangle(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    double calc_area() const;
    double calc_perimetr() const;
    std::string name() const;
};

class Circle : public Shape {
private:
    Point center;
    double r;

public:
    Circle(double r);
    // Центр можно задавать как Point или отдельными координатами.
    Circle(const Point& center, double r);
    Circle(double x, double y, double r);
    double calc_area() const;
    double calc_perimetr() const;
    std::string name() const;
};

class Ellipse : public Shape {
private:
    Point center;
    double a;
    double b;

public:
    Ellipse(double a, double b);
    Ellipse(const Point& center, double a, double b);
    Ellipse(double x, double y, double a, double b);
    double calc_area() const;
    double calc_perimetr() const;
    std::string name() const;
};

class Triangle : public Shape {
private:
    double a;
    double b;
    double c;
    double h;
    bool byHeight;
    bool byPoints;
    Point p1;
    Point p2;
    Point p3;

public:
    Triangle(double a, double b, double c);
    // В распознавании треугольников из картинки используется основание и высота.
    Triangle(double a, double h, bool byHeight);
    Triangle(const Point& p1, const Point& p2, const Point& p3);
    double calc_area() const;
    double calc_perimetr() const;
    std::string name() const;
};

class Polygon : public Shape {
private:
    std::vector<Point> points;

public:
    Polygon(const std::vector<Point>& points);
    // По заданию многоугольник должен уметь забирать координаты из файла.
    Polygon(const std::string& fileName);
    double calc_area() const;
    double calc_perimetr() const;
    std::string name() const;
};

#endif
