#include "../include/Array.h"
#include <iomanip>
#include <iostream>

Array::Array() : size(0), capacity(4) {
    data = std::make_unique<std::unique_ptr<Figure>[]>(capacity);
}

void Array::add(std::unique_ptr<Figure> fig) {
    if (size >= capacity) resize();
    data[size++] = std::move(fig);
}

void Array::remove(size_t index) {
    if (index >= size) throw std::out_of_range("Invalid index");
    data[index].reset();
    for (size_t i = index; i < size - 1; ++i) data[i] = std::move(data[i + 1]);
    data[--size].reset();
}

Figure& Array::operator[](size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    return *data[index];
}

const Figure& Array::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of range");
    return *data[index];
}

void Array::printSurfaces() const {
    std::cout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < size; ++i) {
        std::cout << i << ": " << *data[i]
                  << " | Surface = " << double(*data[i]) << std::endl;
    }
}

void Array::printCenters() const {
    for (size_t i = 0; i < size; ++i) {
        Point c = data[i]->center();
        std::cout << i << ": Center = (" << c.x << ", " << c.y << ")" << std::endl;
    }
}

double Array::totalSurface() const {
    double total = 0;
    for (size_t i = 0; i < size; ++i) total += double(*data[i]);
    return total;
}

size_t Array::getSize() const {
    return size;
}

void Array::resize() {
    capacity *= 2;
    auto newData = std::make_unique<std::unique_ptr<Figure>[]>(capacity);
    for (size_t i = 0; i < size; ++i) newData[i] = std::move(data[i]);
    data = std::move(newData);
}