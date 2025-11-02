#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"

template <IsScalar T>
class Rectangle : public Figure<T>
{
public:
    Rectangle() = default;

    Rectangle(const Rectangle<T>& other) = default;
    Rectangle(Rectangle<T>&& other) noexcept = default;

    Rectangle& operator=(const Rectangle<T>& other) = default;
    Rectangle& operator=(Rectangle<T>&& other) noexcept = default;

    virtual void print(std::ostream& os) const override;
    virtual void read(std::istream& is) override;

    virtual Point<T> center() const override;
    virtual double surface() const override;

    virtual operator double() const override;
    virtual bool operator==(const Figure<T>& other) const override;
    virtual bool operator!=(const Figure<T>& other) const override;
    
    virtual bool validate() const override;

    ~Rectangle() = default;

private:
    Point<T> vertices[4];
    int n{4};
};

#endif