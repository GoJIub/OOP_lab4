#ifndef SQUARE_H
#define SQUARE_H

#include "Figure.h"

template <IsScalar T>
class Square : public Figure<T>
{
public:
    Square() = default;

    Square(const Square<T>& other) = default;
    Square(Square<T>&& other) noexcept = default;

    Square& operator=(const Square<T>& other) = default;
    Square& operator=(Square<T>&& other) noexcept = default;

    virtual void print(std::ostream& os) const override;
    virtual void read(std::istream& is) override;

    virtual Point<T> center() const override;
    virtual double surface() const override;

    virtual operator double() const override;
    virtual bool operator==(const Figure<T>& other) const override;
    virtual bool operator!=(const Figure<T>& other) const override;
    
    virtual bool validate() const override;

    ~Square() = default;

private:
    Point<T> vertices[4];
    int n{4};
};

#endif