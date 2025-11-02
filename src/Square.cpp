#include "../include/Square.h"
#include <cmath>

template <IsScalar T>
Square<T>::Square() {
    vertices = new Point[n];
}

template <IsScalar T>
void Square<T>::print(std::ostream& os) const {
    for (int i = 0; i < n; ++i) os << vertices[i] << " ";
}

template <IsScalar T>
void Square<T>::read(std::istream& is) {
    if (is.rdbuf() == std::cin.rdbuf())
        std::cout << "Enter 4 Square vertices separated by spaces (in x y format):\n";

    for (int i = 0; i < n; ++i) is >> vertices[i];
    if (!validate()) throw std::invalid_argument("The entered points do not form a Square!");
}

template <IsScalar T>
Point<T> Square<T>::center() const {
    T cx{0.0}, cy {0.0};
    for (int i = 0; i < n; ++i) {
        cx += vertices[i].x;
        cy += vertices[i].y;
    }
    return Point{cx / n, cy / n};
}

template <IsScalar T>
double Square<T>::surface() const {
    double a = vertices[0].distanceTo(vertices[1]);
    double b = vertices[2].distanceTo(vertices[3]);
    return a * b;
}

template <IsScalar T>
Square<T>::operator double() const {
    return surface();
}

template <IsScalar T>
bool Square<T>::operator==(const Figure<T>& other) const {
    const Square<T>* o = dynamic_cast<const Square<T>*>(&other);
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
bool Square<T>::operator!=(const Figure<T>& other) const {
    return !(other == *this);
}

template <IsScalar T>
bool Square<T>::validate() const {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (vertices[i] == vertices[j]) {
                return false;
            }
        }
    }

    T side = vertices[0].distanceTo(vertices[1]);
    for (int i = 0; i < n; ++i) {
        T current_side = vertices[i].distanceTo(vertices[(i + 1) % n]);
        if (std::abs(current_side - side) > 1e-6) {
            return false;
        }
    }

    for (int i = 0; i < n; ++i) {
        Point<T> v1 = vertices[(i + 1) % n] - vertices[i];
        Point<T> v2 = vertices[(i + 2) % n] - vertices[(i + 1) % n];
        if (std::abs(v1.dot(v2)) > 1e-6) {
            return false;
        }
    }

    return true;
}
