#include <iostream>
#include <memory>
#include <iomanip>
#include <typeinfo>

#include "include/Array.h"
#include "include/Trapezoid.h"
#include "include/Rhomb.h"
#include "include/Pentagon.h"

std::string typeName(const Figure& f) {
    if (dynamic_cast<const Trapezoid*>(&f)) return "Trapezoid";
    if (dynamic_cast<const Rhomb*>(&f))     return "Rhomb";
    if (dynamic_cast<const Pentagon*>(&f))  return "Pentagon";
    return "What have you done?";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    try {
        // 1. Создание контейнера фигур
        Array figures;

        // 2. Добавление трёх фигур разных типов
        figures.add(std::make_unique<Trapezoid>());
        figures.add(std::make_unique<Rhomb>());
        figures.add(std::make_unique<Pentagon>());

        // 3. Ввод вершин для каждой фигуры
        std::cout << "=== Input of vertex coordinates ===\n";
        for (size_t i =  0; i < figures.getSize(); ++i) {
            std::cout << "\nFigure " << i << " - " 
                      << typeName(figures[i]) << ":\n";
            std::cin >> figures[i];
        }

        // 4. Вывод всех фигур и их площадей
        std::cout << "\n=== List of figures ===\n";
        figures.printSurfaces();

        // 5. Вывод центров фигур
        std::cout << "\n=== Geometric centers ===\n";
        figures.printCenters();

        // 6. Общая площадь
        std::cout << "\n=== Total surface of all figures ===\n";
        std::cout << "Total surface = " << figures.totalSurface() << std::endl;

        // 7. Проверка operator== и приведения к double
        std::cout << "\n=== Operator checks ===\n";
        if (figures[0] == figures[1])
            std::cout << "Figure 0 is equal to figure 1\n";
        else
            std::cout << "Figure 0 is not equal to figure 1\n";

        std::cout << "surface of figure 0 = " 
                  << double(figures[0]) << std::endl;

        // 8. Проверка копирования и перемещения Trapezoid
        std::cout << "\n=== Copy and move semantics test (Trapezoid) ===\n";
        Trapezoid t1;
        std::cin >> t1;
        std::cout << "Original trapezoid:\n" << t1 << std::endl;

        Trapezoid t2 = t1;
        std::cout << "After copying (t2):\n" << t2 << std::endl;

        Trapezoid t3 = std::move(t1);
        std::cout << "After moving (t3):\n" << t3 << std::endl;

        // 9. Удаление фигуры
        std::cout << "\n=== Deleting figure 1 ===\n";
        figures.remove(1);
        figures.printSurfaces();

        // 10. Проверка обработки исключения
        std::cout << "\n=== Testing array index out of bounds ===\n";
        std::cout << "Trying to access figure 10...\n";
        std::cout << figures[10]; // вызовет исключение

    } catch (const std::out_of_range& e) {
        std::cerr << "Error: index out of bounds - " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}