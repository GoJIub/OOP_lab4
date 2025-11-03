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
    static constexpr int n = 4;
    std::unique_ptr<Point<T>[]> vertices;

public:
    Rectangle();
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    Point<T> center() const override;
    double surface() const override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
    bool operator!=(const Figure<T>& other) const override;
    bool validate() const override;

    ~Rectangle() override = default;
};

#endif
