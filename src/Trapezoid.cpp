#include "../include/Trapezoid.h"
#include <cmath>

template <IsScalar T>
Trapezoid<T>::Trapezoid() : vertices(std::make_unique<Point<T>[]>(n)) {}

template <IsScalar T>
Trapezoid<T>::Trapezoid(const Trapezoid& other) : vertices(std::make_unique<Point<T>[]>(n)) {
    for (int i = 0; i < n; ++i)
        vertices[i] = other.vertices[i];
}

template <IsScalar T>
Trapezoid<T>::Trapezoid(Trapezoid&& other) noexcept : vertices(std::move(other.vertices)) {}

template <IsScalar T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid& other) {
    if (this == &other)
        return *this;
    vertices = std::make_unique<Point<T>[]>(n);
    for (int i = 0; i < n; ++i)
        vertices[i] = other.vertices[i];
    return *this;
}

template <IsScalar T>
Trapezoid<T>& Trapezoid<T>::operator=(Trapezoid&& other) noexcept {
    if (this == &other)
        return *this;
    vertices = std::move(other.vertices);
    return *this;
}

template <IsScalar T>
void Trapezoid<T>::print(std::ostream& os) const {
    for (int i = 0; i < n; ++i) os << vertices[i] << " ";
}

template <IsScalar T>
void Trapezoid<T>::read(std::istream& is) {
    if (is.rdbuf() == std::cin.rdbuf())
        std::cout << "Enter 4 trapezoid vertices separated by spaces (in x y format):\n";

    for (int i = 0; i < n; ++i) is >> vertices[i];
    if (!validate()) throw std::invalid_argument("The entered points do not form a trapezoid!");
}

template <IsScalar T>
Point<T> Trapezoid<T>::center() const {
    T cx{0.0}, cy {0.0};
    for (int i = 0; i < n; ++i) {
        cx += vertices[i].x;
        cy += vertices[i].y;
    }
    return Point{cx / n, cy / n};
}

template <IsScalar T>
double Trapezoid<T>::surface() const {
    double a = vertices[0].distanceTo(vertices[1]);
    double b = vertices[2].distanceTo(vertices[3]);
    double h = std::abs(vertices[0].y - vertices[2].y);
    return (a + b) * h / 2.0;
}

template <IsScalar T>
Trapezoid<T>::operator double() const {
    return surface();
}

template <IsScalar T>
bool Trapezoid<T>::operator==(const Figure<T>& other) const {
    const Trapezoid<T>* o = dynamic_cast<const Trapezoid<T>*>(&other);
    if (!o) return false;

    for (int shift = 0; shift < n; ++shift) {
        bool match = true;
        for (int i = 0; i < n; ++i) {
            int shifted_index = (i + shift) % n;
            if (vertices[i].x != o->vertices[shifted_index].x ||
                vertices[i].y != o->vertices[shifted_index].y) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

template <IsScalar T>
bool Trapezoid<T>::operator!=(const Figure<T>& other) const {
    return !(other == *this);
}

template <IsScalar T>
bool Trapezoid<T>::validate() const {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (vertices[i].x == vertices[j].x &&
                vertices[i].y == vertices[j].y) {
                return false;
            }
        }
    }

    if (std::abs(vertices[0].y - vertices[1].y) != std::abs(vertices[2].y - vertices[3].y))
        return false;

    double side1 = vertices[1].distanceTo(vertices[2]);
    double side2 = vertices[0].distanceTo(vertices[3]);
    return std::abs(side1 - side2) < 1e-6;
}

template class Trapezoid<double>;
