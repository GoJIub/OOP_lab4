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
    static constexpr int n = 4;
    std::unique_ptr<Point<T>[]> vertices;

public:
    Trapezoid();
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    Point<T> center() const override;
    double surface() const override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
    bool operator!=(const Figure<T>& other) const override;
    bool validate() const override;

    ~Trapezoid() override = default;
};

#endif
