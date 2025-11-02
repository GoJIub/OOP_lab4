#include "../include/Point.h"
#include <cmath>

template <IsScalar T>
Point<T>::Point(T x, T y) : x(x), y(y)
{
}

template <IsScalar T>
double Point<T>::distanceTo(const Point& other) const {
    return std::sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
}

template <IsScalar T>
double Point<T>::dot(const Point& other) const {
    return x * other.x + y * other.y;
}