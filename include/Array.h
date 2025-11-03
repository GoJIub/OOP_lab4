#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <iomanip>

#include "Figure.h"

template <class T>
class Array {
public:
    Array();
    ~Array() = default;

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    void add(const T& value);
    void add(T&& value);
    void remove(size_t index);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void printSurfaces() const;
    void printCenters() const;
    double totalSurface() const;

    void print() const;
    size_t getSize() const;
    size_t getCapacity() const;

private:
    std::unique_ptr<T[]> data;
    size_t size;
    size_t capacity;

    void resize();
};

#endif
