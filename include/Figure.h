#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <string.h>
#include <string_view>

#include "Point.h"

template <IsScalar T>
class Figure
{
    template <IsScalar U>
    friend std::ostream& operator<<(std::ostream& os, const Figure<U>& f);

    template <IsScalar U>
    friend std::istream& operator>>(std::istream& is, Figure<U>& f);

protected:
    Figure() = default;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual bool validate() const = 0;

public:
    virtual ~Figure() = default;

    virtual Point<T> center() const = 0;
    virtual double surface() const = 0;

    virtual operator double() const = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual bool operator!=(const Figure<T>& other) const = 0;
};

template <IsScalar T>
inline std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.print(os);
    return os;
}

template <IsScalar T>
inline std::istream& operator>>(std::istream& is, Figure<T>& fig) {
    fig.read(is);
    return is;
}

#endif