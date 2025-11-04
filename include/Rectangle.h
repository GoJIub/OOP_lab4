#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"
#include "Point.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <iostream>

template <IsScalar T>
class Rectangle : public Figure<T> {
private:
    int n{4};
    std::unique_ptr<Point<T>> vertices[4];

public:
    Rectangle() {
        for (auto& v : vertices) v = std::make_unique<Point<T>>();
    }

    Rectangle(const Rectangle& other) {
        for (int i = 0; i < 4; ++i) vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }

    Rectangle(Rectangle&& other) noexcept {
        for (int i = 0; i < 4; ++i) vertices[i] = std::move(other.vertices[i]);
    }

    Rectangle& operator=(const Rectangle& other) {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i) vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        return *this;
    }

    Rectangle& operator=(Rectangle&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i) vertices[i] = std::move(other.vertices[i]);
        return *this;
    }

    void print(std::ostream& os) const override {
        for (const auto& v : vertices) os << *v << " ";
    }

    void read(std::istream& is) override {
        if (is.rdbuf() == std::cin.rdbuf())
            std::cout << "Enter 4 rectangle vertices separated by spaces (in x y format):\n";

        for (auto& v : vertices) is >> *v;
        if (!validate()) throw std::invalid_argument("The entered points do not form a rectangle!");
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
        double b = vertices[1]->distanceTo(*vertices[2]);
        return a * b;
    }

    operator double() const override {
        return surface();
    }

    bool operator==(const Figure<T>& other) const override {
        const Rectangle<T>* o = dynamic_cast<const Rectangle<T>*>(&other);
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

    bool validate() const {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (*vertices[i] == *vertices[j])
                    return false;

        double a = vertices[0]->distanceTo(*vertices[1]);
        double b = vertices[1]->distanceTo(*vertices[2]);
        double c = vertices[2]->distanceTo(*vertices[3]);
        double d = vertices[3]->distanceTo(*vertices[0]);

        if (std::abs(a - c) > 1e-6 || std::abs(b - d) > 1e-6)
            return false;

        for (int i = 0; i < n; ++i) {
            Point<T> v1 = *vertices[(i + 1) % n] - *vertices[i];
            Point<T> v2 = *vertices[(i + 2) % n] - *vertices[(i + 1) % n];
            if (std::abs(v1.dot(v2)) > 1e-6)
                return false;
        }

        return true;
    }

    ~Rectangle() override = default;
};

#endif
