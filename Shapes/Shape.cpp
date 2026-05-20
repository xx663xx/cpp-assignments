#include "Shape.h"

#include <cmath>
#include <fstream>

const double PI = 3.1415926535;

double distanceBetween(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

double triangleAreaByPoints(const Point& a, const Point& b, const Point& c) {
    double area = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    return std::abs(area) / 2.0;
}

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Shape::~Shape() {
}

Rectangle::Rectangle(double a, double b) {
    this->a = std::abs(a);
    this->b = std::abs(b);
}

Rectangle::Rectangle(const Point& leftTop, const Point& rightBottom) {
    a = std::abs(rightBottom.x - leftTop.x);
    b = std::abs(rightBottom.y - leftTop.y);
}

Rectangle::Rectangle(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    a = (distanceBetween(p1, p2) + distanceBetween(p3, p4)) / 2.0;
    b = (distanceBetween(p2, p3) + distanceBetween(p4, p1)) / 2.0;
}

double Rectangle::calc_area() const {
    return a * b;
}

double Rectangle::calc_perimetr() const {
    return 2.0 * (a + b);
}

std::string Rectangle::name() const {
    return "Rectangle";
}

Circle::Circle(double r) {
    center = Point(0, 0);
    this->r = std::abs(r);
}

Circle::Circle(const Point& center, double r) {
    this->center = center;
    this->r = std::abs(r);
}

Circle::Circle(double x, double y, double r) {
    center = Point(x, y);
    this->r = std::abs(r);
}

double Circle::calc_area() const {
    return PI * r * r;
}

double Circle::calc_perimetr() const {
    return 2.0 * PI * r;
}

std::string Circle::name() const {
    return "Circle";
}

Ellipse::Ellipse(double a, double b) {
    center = Point(0, 0);
    this->a = std::abs(a);
    this->b = std::abs(b);
}

Ellipse::Ellipse(const Point& center, double a, double b) {
    this->center = center;
    this->a = std::abs(a);
    this->b = std::abs(b);
}

Ellipse::Ellipse(double x, double y, double a, double b) {
    center = Point(x, y);
    this->a = std::abs(a);
    this->b = std::abs(b);
}

double Ellipse::calc_area() const {
    return PI * a * b;
}

double Ellipse::calc_perimetr() const {
    double value = 3.0 * (a + b) - std::sqrt((3.0 * a + b) * (a + 3.0 * b));
    return PI * value;
}

std::string Ellipse::name() const {
    return "Ellipse";
}

Triangle::Triangle(double a, double b, double c) {
    this->a = std::abs(a);
    this->b = std::abs(b);
    this->c = std::abs(c);
    h = 0;
    byHeight = false;
    byPoints = false;
}

Triangle::Triangle(double a, double h, bool byHeight) {
    this->a = std::abs(a);
    this->b = 0;
    this->c = 0;
    this->h = std::abs(h);
    this->byHeight = byHeight;
    byPoints = false;
}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    a = distanceBetween(p1, p2);
    b = distanceBetween(p2, p3);
    c = distanceBetween(p3, p1);
    h = 0;
    byHeight = false;
    byPoints = true;
}

double Triangle::calc_area() const {
    if (byPoints) {
        return triangleAreaByPoints(p1, p2, p3);
    }

    if (byHeight) {
        return a * h / 2.0;
    }

    double p = calc_perimetr() / 2.0;
    double value = p * (p - a) * (p - b) * (p - c);

    if (value <= 0) {
        return 0;
    }

    return std::sqrt(value);
}

double Triangle::calc_perimetr() const {
    if (byPoints || !byHeight) {
        return a + b + c;
    }

    double side = std::sqrt((a / 2.0) * (a / 2.0) + h * h);
    return a + 2.0 * side;
}

std::string Triangle::name() const {
    return "Triangle";
}

Polygon::Polygon(const std::vector<Point>& points) {
    this->points = points;
}

Polygon::Polygon(const std::string& fileName) {
    std::ifstream fin(fileName.c_str());

    if (!fin.is_open()) {
        return;
    }

    int count;
    fin >> count;

    for (int i = 0; i < count; i++) {
        Point p;
        fin >> p.x >> p.y;

        if (fin) {
            points.push_back(p);
        }
    }
}

double Polygon::calc_area() const {
    double s = 0;

    for (std::size_t i = 0; i < points.size(); i++) {
        std::size_t j = (i + 1) % points.size();
        s += points[i].x * points[j].y - points[j].x * points[i].y;
    }

    return std::abs(s) / 2.0;
}

double Polygon::calc_perimetr() const {
    double perimeter = 0;

    for (std::size_t i = 0; i < points.size(); i++) {
        std::size_t j = (i + 1) % points.size();
        perimeter += distanceBetween(points[i], points[j]);
    }

    return perimeter;
}

std::string Polygon::name() const {
    return "Polygon";
}
