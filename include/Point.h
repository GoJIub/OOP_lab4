#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <type_traits>
#include <concepts>
#include <cmath>

template <typename T>
concept IsScalar = std::is_scalar_v<T>;

template <IsScalar T>
class Point {
public:
    T x{0.0}, y{0.0};

    Point() = default;
    Point(T x, T y) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    Point operator-(const Point& other) const {
        return Point<T>(x - other.x, y - other.y);
    }

    double distanceTo(const Point& other) const {
        return std::sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
    }

    double dot(const Point& other) const {
        return x * other.x + y * other.y;
    }

    friend std::istream& operator>>(std::istream& is, Point<T>& p) {
        return is >> p.x >> p.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }

    ~Point() = default;
};

#endif