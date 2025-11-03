#include "../include/Rectangle.h"
#include <cmath>

template <IsScalar T>
Rectangle<T>::Rectangle() : vertices(std::make_unique<Point<T>[]>(n)) {}

template <IsScalar T>
Rectangle<T>::Rectangle(const Rectangle& other) : vertices(std::make_unique<Point<T>[]>(n)) {
    for (int i = 0; i < n; ++i)
        vertices[i] = other.vertices[i];
}

template <IsScalar T>
Rectangle<T>::Rectangle(Rectangle&& other) noexcept : vertices(std::move(other.vertices)) {}

template <IsScalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle& other) {
    if (this == &other)
        return *this;
    vertices = std::make_unique<Point<T>[]>(n);
    for (int i = 0; i < n; ++i)
        vertices[i] = other.vertices[i];
    return *this;
}

template <IsScalar T>
Rectangle<T>& Rectangle<T>::operator=(Rectangle&& other) noexcept {
    if (this == &other)
        return *this;
    vertices = std::move(other.vertices);
    return *this;
}

template <IsScalar T>
void Rectangle<T>::print(std::ostream& os) const {
    for (int i = 0; i < n; ++i) os << vertices[i] << " ";
}

template <IsScalar T>
void Rectangle<T>::read(std::istream& is) {
    if (is.rdbuf() == std::cin.rdbuf())
        std::cout << "Enter 4 Rectangle vertices separated by spaces (in x y format):\n";

    for (int i = 0; i < n; ++i) is >> vertices[i];
    if (!validate()) throw std::invalid_argument("The entered points do not form a Rectangle!");
}

template <IsScalar T>
Point<T> Rectangle<T>::center() const {
    T cx{0.0}, cy {0.0};
    for (int i = 0; i < n; ++i) {
        cx += vertices[i].x;
        cy += vertices[i].y;
    }
    return Point{cx / n, cy / n};
}

template <IsScalar T>
double Rectangle<T>::surface() const {
    double a = vertices[0].distanceTo(vertices[1]);
    double b = vertices[1].distanceTo(vertices[2]);
    return a * b;
}

template <IsScalar T>
Rectangle<T>::operator double() const {
    return surface();
}

template <IsScalar T>
bool Rectangle<T>::operator==(const Figure<T>& other) const {
    const Rectangle<T>* o = dynamic_cast<const Rectangle<T>*>(&other);
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
bool Rectangle<T>::operator!=(const Figure<T>& other) const {
    return !(other == *this);
}

template <IsScalar T>
bool Rectangle<T>::validate() const {
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (vertices[i] == vertices[j])
                return false;

    double a = vertices[0].distanceTo(vertices[1]);
    double b = vertices[1].distanceTo(vertices[2]);
    if (std::abs(a - vertices[2].distanceTo(vertices[3])) > 1e-6 ||
        std::abs(b - vertices[3].distanceTo(vertices[0])) > 1e-6)
        return false;

    for (int i = 0; i < n; ++i) {
        Point<T> v1 = vertices[(i + 1) % n] - vertices[i];
        Point<T> v2 = vertices[(i + 2) % n] - vertices[(i + 1) % n];
        if (std::abs(v1.dot(v2)) > 1e-6)
            return false;
    }

    return true;
}

template class Rectangle<double>;
