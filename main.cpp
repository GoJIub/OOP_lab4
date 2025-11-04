#include <iostream>
#include <memory>
#include <iomanip>

#include "include/Array.h"
#include "include/Trapezoid.h"
#include "include/Square.h"
#include "include/Rectangle.h"

template <typename T>
std::string typeName(const Figure<T>& f) {
    if (dynamic_cast<const Trapezoid<T>*>(&f)) return "Trapezoid";
    if (dynamic_cast<const Square<T>*>(&f)) return "Square";
    if (dynamic_cast<const Rectangle<T>*>(&f)) return "Rectangle";
    return "What have you done?";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    // ===================================================================
    // 1. ПОЛИМОРФНЫЙ КОНТЕЙНЕР: Array<Figure<double>*>
    // ===================================================================
    Array<std::shared_ptr<Figure<double>>> figures;

    // 2. Добавление трёх фигур разных типов
    figures.add(std::make_shared<Trapezoid<double>>());
    figures.add(std::make_shared<Square<double>>());
    figures.add(std::make_shared<Rectangle<double>>());

    // 3. Ввод вершин для каждой фигуры
    std::cout << "\n=== Input of vertex coordinates ===\n";
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << "\nFigure " << i << " - " 
                    << typeName(*figures[i]) << ":\n";
        std::cin >> *figures[i];
    }

    // 4. Вывод всех фигур и их площадей
    std::cout << "\n=== List of figures ===\n";
    figures.printSurfaces();

    // 5. Вывод центров фигур
    std::cout << "\n=== Geometric centers ===\n";
    figures.printCenters();

    // 6. Общая площадь
    std::cout << "\n=== Total surface  of all figures ===\n";
    std::cout << "Total surface = " << figures.totalSurface() << std::endl;

    // 7. Проверка operator== и приведения к double
    std::cout << "\n=== Operator checks ===\n";
    if (figures[0] == figures[1])
        std::cout << "Figure 0 is equal to figure 1\n";
    else
        std::cout << "Figure 0 is not equal to figure 1\n";

    std::cout << "surface of figure 0 = " 
                << double(*figures[0]) << std::endl;

    // 8. Проверка копирования и перемещения
    std::cout << "\n=== Copy and move semantics test (Trapezoid) ===\n";
    Trapezoid<double> t1;
    std::cin >> t1;
    std::cout << "Original trapezoid:\n" << t1 << std::endl;

    Trapezoid<double> t2 = t1;
    std::cout << "After copying (t2):\n" << t2 << std::endl;

    Trapezoid<double> t3 = std::move(t1);
    std::cout << "After moving (t3):\n" << t3 << std::endl;

    // 9. Удаление фигуры
    std::cout << "\n=== Deleting figure 1 ===\n";
    figures.remove(1);
    figures.printSurfaces();

    // 10. Проверка обработки исключения
    std::cout << "\n=== Testing array index out of bounds ===\n";
    std::cout << "Trying to access figure 10...\n";
    try {
        std::cout << figures[10];
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    // ===================================================================
    // 11. НЕПОЛИМОРФНЫЙ КОНТЕЙНЕР: Array<Square<double>>
    // ===================================================================
    std::cout << "\n=== Non-polymorphic container: Array<Square<double>> ===\n";

    Array<Square<double>> squares;

    // 12. Добавление трёх фигур одного типа
    squares.add(Square<double>());
    squares.add(Square<double>());
    squares.add(Square<double>());

    // 13. Ввод вершин для каждой фигуры
    std::cout << "\nInput coordinates for 3 squares:\n";
    for (size_t i = 0; i < squares.getSize(); ++i) {
        std::cout << "Square " << i << ":\n";
        std::cin >> squares[i];
    }

    // 14. Вывод всех фигур и их площадей
    std::cout << "\nSquares and their surfaces:\n";
    for (size_t i = 0; i < squares.getSize(); ++i) {
        std::cout << i << ": " << squares[i] 
                    << " | Surface = " << double(squares[i]) << "\n";
    }

    // 15. Вывод центров фигур
    std::cout << "\nGeometric centers of squares:\n";
    for (size_t i = 0; i < squares.getSize(); ++i) {
        auto c = squares[i].center();
        std::cout << i << ": Center = (" << c.x << ", " << c.y << ")\n";
    }

    // 16. Общая площадь
    double totalSquareSurface = 0.0;
    for (size_t i = 0; i < squares.getSize(); ++i) {
        totalSquareSurface += double(squares[i]);
    }
    std::cout << "\nTotal surface of all squares = " << totalSquareSurface << "\n";

    // 17. Проверка operator== и приведения к double
    std::cout << "\nEquality check (squares 0 and 1):\n";
    if (squares[0] == squares[1])
        std::cout << "Square 0 == Square 1\n";
    else
        std::cout << "Square 0 != Square 1\n";

    // 18. Проверка копирования и перемещения
    std::cout << "\nCopy and move semantics (Square):\n";
    Square<double> s1;
    std::cin >> s1;
    std::cout << "Original square (s1):\n" << s1 << "\n";

    Square<double> s2 = s1;
    std::cout << "After copy (s2):\n" << s2 << "\n";

    Square<double> s3 = std::move(s1);
    std::cout << "After move (s3):\n" << s3 << "\n";

    // 19. Удаление фигуры
    std::cout << "\nRemoving square 1...\n";
    squares.remove(1);
    std::cout << "Squares after removal:\n";
    for (size_t i = 0; i < squares.getSize(); ++i) {
        std::cout << i << ": " << squares[i] 
                    << " | Surface = " << double(squares[i]) << "\n";
    }

    // 20. Проверка обработки исключения
    std::cout << "Trying to access figure 10...\n";
    try {
        std::cout << squares[10];
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << "\n";
    }
}
