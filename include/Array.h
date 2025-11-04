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
    Array() : size(0), capacity(4) {
        data = std::make_unique<std::shared_ptr<T>[]>(capacity);
    }

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    void add(std::shared_ptr<T> fig) {
        if (size >= capacity) resize();
        data[size++] = std::move(fig);
    }

    void remove(size_t index) {
        if (index >= size) throw std::out_of_range("Invalid out of range");
        data[index].reset();
        for (size_t i = index; i < size - 1; ++i) data[i] = std::move(data[i + 1]);
        data[--size].reset();
    }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return *data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return *data[index];
    }

    void printSurfaces() const {
        std::cout << std::fixed << std::setprecision(2);
        for (size_t i = 0; i < size; ++i) {
            std::cout << i << ": " << *data[i]
                    << " | Surface = " << double(*data[i]) << std::endl;
        }
    }

    void printCenters() const {
        for (size_t i = 0; i < size; ++i) {
            auto c = data[i]->center();
            std::cout << i << ": Center = (" << c.x << ", " << c.y << ")" << std::endl;
        }
    }

    double totalSurface() const {
        double total = 0;
        for (size_t i = 0; i < size; ++i) total += double(*data[i]);
        return total;
    }

    void print() const {
        for (size_t i = 0; i < size; ++i) std::cout << "[" << i << "] " << data[i] << "\n";
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }
    
    ~Array() = default;

private:
    std::unique_ptr<std::shared_ptr<T>[]> data;
    size_t size;
    size_t capacity;

    void resize() {
        capacity *= 2;
        auto newData = std::make_unique<std::shared_ptr<T>[]>(capacity);
        for (size_t i = 0; i < size; ++i) newData[i] = std::move(data[i]);
        data = std::move(newData);
    }
};

#endif
