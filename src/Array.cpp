#include "../include/Array.h"
#include <iostream>

template <class T>
Array<T>::Array() : size(0), capacity(4) {
    data = std::make_unique<T[]>(capacity);
}

template <class T>
void Array<T>::add(const T& value) {
    if (size >= capacity) resize();
    data[size++] = value;
}

template <class T>
void Array<T>::add(T&& value) {
    if (size >= capacity) resize();
    data[size++] = std::move(value);
}

template <class T>
void Array<T>::remove(size_t index) {
    if (index >= size) throw std::out_of_range("Invalid index");
    for (size_t i = index; i < size - 1; ++i) data[i] = std::move(data[i + 1]);
    --size;
}

template <class T>
T& Array<T>::operator[](size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

template <class T>
const T& Array<T>::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

template <class T>
void Array<T>::resize() {
    capacity *= 2;
    auto newData = std::make_unique<T[]>(capacity);
    for (size_t i = 0; i < size; ++i) newData[i] = std::move(data[i]);
    data = std::move(newData);
}

template <class T>
void Array<T>::printSurfaces() const {
    std::cout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < size; ++i) {
        std::cout << i << ": " << *data[i]
                  << " | Surface = " << double(*data[i]) << std::endl;
    }
}

template <class T>
void Array<T>::printCenters() const {
    for (size_t i = 0; i < size; ++i)
        std::cout << i << ": Center = (" << data[i]->center().x << ", " << data[i]->center().y << ")" << std::endl;
}

template <class T>
double Array<T>::totalSurface() const {
    double total = 0;
    for (size_t i = 0; i < size; ++i) total += double(*data[i]);
    return total;
}

template <class T>
void Array<T>::print() const {
    for (size_t i = 0; i < size; ++i) std::cout << "[" << i << "] " << data[i] << "\n";
}

template <class T>
size_t Array<T>::getSize() const {
    return size;
}

template <class T>
size_t Array<T>::getCapacity() const {
    return capacity;
}

template class Array<std::shared_ptr<Figure<double>>>;
