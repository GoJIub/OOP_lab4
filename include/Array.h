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
        data = std::make_shared<T[]>(capacity);
    }

    // add — принимает shared_ptr
    void add(std::shared_ptr<typename std::remove_pointer<T>::type> fig) {
        if (size >= capacity) resize();
        data[size++] = std::move(fig);
    }

    // Универсальный add для объектов (Array<Square<double>>)
    template <class U = T>
    std::enable_if_t<!std::is_pointer_v<U>> add(const U& fig) {
        if (size >= capacity) resize();
        data[size++] = fig;
    }

    template <class U = T>
    std::enable_if_t<!std::is_pointer_v<U>> add(U&& fig) {
        if (size >= capacity) resize();
        data[size++] = std::move(fig);
    }

    void remove(size_t index) {
        if (index >= size) throw std::out_of_range("Invalid out of range");
        for (size_t i = index; i < size - 1; ++i) data[i] = std::move(data[i + 1]);
        --size;
    }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void printSurfaces() const {
        std::cout << std::fixed << std::setprecision(2);
        for (size_t i = 0; i < size; ++i) {
            if constexpr (requires { double(data[i]); }) {
                std::cout << i << ": " << *data[i]
                    << " | Surface = " << double(data[i]) << std::endl;
            } else if constexpr (requires { double(*data[i]); }) {
                std::cout << i << ": " << *data[i]
                    << " | Surface = " << double(*data[i]) << std::endl;
            }
        }
    }

    void printCenters() const {
        for (size_t i = 0; i < size; ++i) {
            if constexpr (requires { data[i].center(); }) {
                auto c = data[i].center();
                std::cout << i << ": Center = (" << c.x << ", " << c.y << ")\n";
            } else if constexpr (requires { data[i]->center(); }) {
                auto c = data[i]->center();
                std::cout << i << ": Center = (" << c.x << ", " << c.y << ")\n";
            }
        }
    }

    double totalSurface() const {
        double sum = 0;
        for (size_t i = 0; i < size; ++i) {
            if constexpr (requires { double(data[i]); }) sum += double(data[i]);
            else if constexpr (requires { double(*data[i]); }) sum += double(*data[i]);
        }
        return sum;
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
    std::shared_ptr<T[]> data;
    size_t size;
    size_t capacity;

    void resize() {
        capacity *= 2;
        auto newData = std::make_shared<T[]>(capacity);
        for (size_t i = 0; i < size; ++i) newData[i] = std::move(data[i]);
        data = std::move(newData);
    }
};

#endif
