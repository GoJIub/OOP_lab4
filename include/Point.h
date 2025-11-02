#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <type_traits>
#include <concepts>

template <typename T>
concept IsScalar = std::is_scalar_v<T>;

template <IsScalar T>
class Point
{
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);

public:
    T x{0.0}, y{0.0};

    Point() = default;
    Point(T x, T y);

    double distanceTo(const Point& other) const;
    double dot(const Point& other) const;

    ~Point() = default;
};

template <IsScalar T>
inline std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

template <IsScalar T>
inline std::istream& operator>>(std::istream& is, Point<T>& p) {
    return is >> p.x >> p.y;
}

#endif