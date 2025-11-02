#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"

template <IsScalar T>
class Trapezoid : public Figure<T>
{
public:
    Trapezoid() = default;

    Trapezoid(const Trapezoid<T>& other) = default;
    Trapezoid(Trapezoid<T>&& other) noexcept = default;

    Trapezoid& operator=(const Trapezoid<T>& other) = default;
    Trapezoid& operator=(Trapezoid<T>&& other) noexcept = default;

    virtual void print(std::ostream& os) const override;
    virtual void read(std::istream& is) override;

    virtual Point<T> center() const override;
    virtual double surface() const override;

    virtual operator double() const override;
    virtual bool operator==(const Figure<T>& other) const override;
    virtual bool operator!=(const Figure<T>& other) const override;
    
    virtual bool validate() const override;

    ~Trapezoid() = default;

private:
    Point<T> vertices[4];
    int n{4};
};

#endif