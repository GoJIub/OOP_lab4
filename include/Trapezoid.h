#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"
#include "Point.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <iostream>

template <IsScalar T>
class Trapezoid : public Figure<T> {
private:
    int n{4};
    std::unique_ptr<Point<T>> vertices[4];

public:
    Trapezoid() {
        for (auto& v : vertices) v = std::make_unique<Point<T>>();
    }

    Trapezoid(const Trapezoid& other) {
        for (int i = 0; i < 4; ++i) vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }

    Trapezoid(Trapezoid&& other) noexcept {
        for (int i = 0; i < 4; ++i) vertices[i] = std::move(other.vertices[i]);
    }

    Trapezoid& operator=(const Trapezoid& other) {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i) vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        return *this;
    }

    Trapezoid& operator=(Trapezoid&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i) vertices[i] = std::move(other.vertices[i]);
        return *this;
    }

    void print(std::ostream& os) const override {
        for (const auto& v : vertices) os << *v << " ";
    }

    void read(std::istream& is) override {
        if (is.rdbuf() == std::cin.rdbuf())
            std::cout << "Enter 4 trapezoid vertices separated by spaces (in x y format):\n";

        for (auto& v : vertices) is >> *v;
        if (!validate()) throw std::invalid_argument("The entered points do not form a trapezoid!");
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
        T a = vertices[0]->distanceTo(*vertices[1]);
        T b = vertices[2]->distanceTo(*vertices[3]);
        T h = std::abs(vertices[0]->y - vertices[2]->y);
        return static_cast<double>((a + b) * h / 2.0);
    }

    operator double() const override {
        return surface();
    }

    bool operator==(const Figure<T>& other) const override {
        const auto* o = dynamic_cast<const Trapezoid*>(&other);
        if (!o) return false;

        for (int shift = 0; shift < 4; ++shift) {
            bool match = true;
            for (int i = 0; i < 4; ++i) {
                int j = (i + shift) % 4;
                if (vertices[i]->x != o->vertices[j]->x ||
                    vertices[i]->y != o->vertices[j]->y) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }
        return false;
    }

    bool operator!=(const Figure<T>& other) const override {
        return !(*this == other);
    }

    bool validate() const override {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (*vertices[i] == *vertices[j])
                    return false;

        if (std::abs(vertices[0]->y - vertices[1]->y) != std::abs(vertices[2]->y - vertices[3]->y))
            return false;

        double side1 = vertices[1]->distanceTo(*vertices[2]);
        double side2 = vertices[0]->distanceTo(*vertices[3]);
        return std::abs(side1 - side2) < 1e-6;
    }

    ~Trapezoid() override = default;
};

#endif
