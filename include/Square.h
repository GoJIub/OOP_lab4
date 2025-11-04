#ifndef SQUARE_H
#define SQUARE_H

#include "Figure.h"
#include "Point.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <iostream>

template <IsScalar T>
class Square : public Figure<T> {
private:
    int n{4};
    std::unique_ptr<Point<T>> vertices[4];

public:
    Square() {
        for (auto& v : vertices) v = std::make_unique<Point<T>>();
    }

    Square(const Square& other) {
        for (int i = 0; i < 4; ++i) vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }

    Square(Square&& other) noexcept {
        for (int i = 0; i < 4; ++i) vertices[i] = std::move(other.vertices[i]);
    }

    Square& operator=(const Square& other) {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i) vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        return *this;
    }

    Square& operator=(Square&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i) vertices[i] = std::move(other.vertices[i]);
        return *this;
    }

    void print(std::ostream& os) const override {
        for (const auto& v : vertices) os << *v << " ";
    }

    void read(std::istream& is) override {
        if (is.rdbuf() == std::cin.rdbuf())
            std::cout << "Enter 4 square vertices separated by spaces (in x y format):\n";

        for (auto& v : vertices) is >> *v;
        if (!validate()) throw std::invalid_argument("The entered points do not form a square!");
    }

    Point<T> center() const override {
        T cx = 0, cy = 0;
        for (const auto& v : vertices) {
            cx += v->x;
            cy += v->y;
        }
        return Point<T>{cx / 4, cy / 4};
    }

    double surface() const override {
        double a = vertices[0]->distanceTo(*vertices[1]);
        return a * a;
    }

    operator double() const override {
        return surface();
    }

    bool operator==(const Figure<T>& other) const override {
        const Square<T>* o = dynamic_cast<const Square<T>*>(&other);
        if (!o) return false;

        for (int shift = 0; shift < n; ++shift) {
            bool match = true;
            for (int i = 0; i < n; ++i) {
                int shifted_index = (i + shift) % n;
                if (vertices[i]->x != o->vertices[shifted_index]->x ||
                    vertices[i]->y != o->vertices[shifted_index]->y) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }
        return false;
    }
    
    bool operator!=(const Figure<T>& other) const override {
        return !(other == *this);
    }

    bool validate() const override {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (*vertices[i] == *vertices[j])
                    return false;

        T side = vertices[0]->distanceTo(*vertices[1]);
        for (int i = 0; i < n; ++i) {
            T current_side = vertices[i]->distanceTo(*vertices[(i + 1) % n]);
            if (std::abs(current_side - side) > 1e-6)
                return false;
        }

        for (int i = 0; i < n; ++i) {
            Point<T> v1 = *vertices[(i + 1) % n] - *vertices[i];
            Point<T> v2 = *vertices[(i + 2) % n] - *vertices[(i + 1) % n];
            if (std::abs(v1.dot(v2)) > 1e-6)
                return false;
        }

        return true;
    }
};

#endif
