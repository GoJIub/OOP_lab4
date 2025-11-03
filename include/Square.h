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
    static constexpr int n = 4;
    std::unique_ptr<Point<T>[]> vertices;

public:
    Square();
    Square(const Square& other);
    Square(Square&& other) noexcept;
    Square& operator=(const Square& other);
    Square& operator=(Square&& other) noexcept;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    Point<T> center() const override;
    double surface() const override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
    bool operator!=(const Figure<T>& other) const override;
    bool validate() const override;

    ~Square() override = default;
};

#endif
