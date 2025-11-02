#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <memory>
#include <stdexcept>

#include "Figure.h"

class Array {
public:
    Array();

    ~Array() = default;

    // unique_ptr нельзя копировать
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    void add(std::unique_ptr<Figure> fig);

    void remove(size_t index);

    Figure& operator[](size_t index);
    const Figure& operator[](size_t index) const;

    void printSurfaces() const;

    void printCenters() const;

    double totalSurface() const;

    size_t getSize() const;

private:
    std::unique_ptr<std::unique_ptr<Figure>[]> data;
    size_t size;
    size_t capacity;

    void resize();
};

#endif