#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <typeinfo>

// Заголовки
#include "../include/Figure.h"
#include "../include/Trapezoid.h"
#include "../include/Rhomb.h"
#include "../include/Pentagon.h"
#include "../include/Array.h"

// Вспомогательная функция для имитации пользовательского ввода
void inputFigure(Figure& fig, const std::string& input) {
    std::istringstream iss(input);
    iss >> fig;
}

// --- ТЕСТЫ ДЛЯ Trapezoid ---
TEST(TrapezoidTest, InputAndOutput) {
    Trapezoid t;
    inputFigure(t, "0 0  4 0  3 3  1 3");
    std::ostringstream oss;
    oss << t;
    EXPECT_EQ(oss.str(), "(0, 0) (4, 0) (3, 3) (1, 3) ");
}

TEST(TrapezoidTest, AreaAndCenter) {
    Trapezoid t;
    inputFigure(t, "0 0  6 0  4 4  2 4");
    EXPECT_DOUBLE_EQ(double(t), 16.0);
    Point c = t.center();
    EXPECT_DOUBLE_EQ(c.x, 3.0);
    EXPECT_DOUBLE_EQ(c.y, 2.0);
}

TEST(TrapezoidTest, ValidateCorrectAndIncorrect) {
    Trapezoid t1;
    inputFigure(t1, "0 0  4 0  3 3  1 3");
    EXPECT_TRUE(t1.validate()); // корректная трапеция

    Trapezoid t2;
    EXPECT_THROW(inputFigure(t2, "0 0  4 0  3 3  0 3"), std::invalid_argument); // некорректная трапеция

}

TEST(TrapezoidTest, ValidateDegenerateCase) {
    Trapezoid t;
    EXPECT_THROW(inputFigure(t, "1 1  1 1  1 1  1 1"), std::invalid_argument); // все точки совпадают
}

TEST(TrapezoidTest, CopyAndMove) {
    Trapezoid t1;
    inputFigure(t1, "0 0  4 0  3 3  1 3");
    Trapezoid t2 = t1;
    EXPECT_TRUE(t1 == t2);

    Trapezoid t3 = std::move(t1);
    std::ostringstream oss;
    oss << t3;
    EXPECT_EQ(oss.str(), "(0, 0) (4, 0) (3, 3) (1, 3) ");
}

// --- ТЕСТЫ ДЛЯ Rhomb ---
TEST(RhombTest, AreaAndValidate) {
    Rhomb r;
    inputFigure(r, "3 0  0 4  -3 0  0 -4");
    EXPECT_TRUE(r.validate());
    EXPECT_NEAR(double(r), 24.0, 1e-6);
}

TEST(RhombTest, DegenerateAndInvalid) {
    Rhomb r1;
    EXPECT_THROW(inputFigure(r1, "0 0  3 0  4 3  1 3"), std::invalid_argument);

    Rhomb r2;
    EXPECT_THROW(inputFigure(r2, "2 2  2 2  2 2  2 2"), std::invalid_argument);
}

// --- ТЕСТЫ ДЛЯ Pentagon ---
TEST(PentagonTest, RegularAndDegenerate) {
    Pentagon p;
    inputFigure(p, "3.20 1.50  2.03 3.12  0.12 2.50  0.12 0.50  2.03 -0.12");
    EXPECT_TRUE(p.validate());
    EXPECT_NEAR(double(p), 7.0, 0.5);

    Pentagon p2;
    EXPECT_THROW(inputFigure(p2, "1 1  1 1  1 1  1 1  1 1"), std::invalid_argument);
}

// --- ТЕСТЫ ДЛЯ Array ---
TEST(ArrayTest, AddRemoveSize) {
    Array arr;
    arr.add(std::make_unique<Trapezoid>());
    arr.add(std::make_unique<Rhomb>());
    arr.add(std::make_unique<Pentagon>());
    EXPECT_EQ(arr.getSize(), 3);

    arr.remove(1);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_THROW(arr.remove(5), std::out_of_range);
}

TEST(ArrayTest, TotalSurface) {
    Array arr;

    auto t = std::make_unique<Trapezoid>();
    inputFigure(*t, "0 0  4 0  3 3  1 3");
    arr.add(std::move(t)); // площадь 9

    auto r = std::make_unique<Rhomb>();
    inputFigure(*r, "3 0  0 4  -3 0  0 -4"); // площадь 24
    arr.add(std::move(r));

    EXPECT_NEAR(arr.totalSurface(), 33.0, 1.0);
}

TEST(ArrayTest, OutOfRangeAccess) {
    Array arr;
    arr.add(std::make_unique<Trapezoid>());
    EXPECT_THROW(arr[10], std::out_of_range);
}

TEST(ArrayTest, Polymorphism) {
    Array arr;
    arr.add(std::make_unique<Trapezoid>());
    arr.add(std::make_unique<Rhomb>());
    arr.add(std::make_unique<Pentagon>());

    for (size_t i = 0; i < arr.getSize(); ++i) {
        // проверяем, что это производный тип
        EXPECT_NE(typeid(arr[i]), typeid(Figure));
    }
}

// --- ТЕСТЫ ДЛЯ Figure ---
TEST(FigureTest, AbstractClass) {
    static_assert(!std::is_constructible<Figure>::value,
                  "Figure must be abstract");
}

// --- НЕГАТИВНЫЕ ТЕСТЫ ДЛЯ ВАЛИДАЦИИ ЧЕРЕЗ Read() ---

TEST(TrapezoidTest, InvalidInputThrows) {
    Trapezoid t;
    std::istringstream iss("0 0  0 0  0 0  0 0"); // все точки совпадают
    EXPECT_THROW(iss >> t, std::invalid_argument);
}

TEST(TrapezoidTest, NonIsoscelesTrapezoidThrows) {
    Trapezoid t;
    std::istringstream iss("0 0  4 0  3 3  0 3"); // неравнобокая
    EXPECT_THROW(iss >> t, std::invalid_argument);
}

TEST(RhombTest, InvalidRhombThrows) {
    Rhomb r;
    std::istringstream iss("0 0  3 0  4 3  1 3"); // не ромб
    EXPECT_THROW(iss >> r, std::invalid_argument);
}

TEST(RhombTest, DegenerateRhombThrows) {
    Rhomb r;
    std::istringstream iss("1 1  1 1  1 1  1 1");
    EXPECT_THROW(iss >> r, std::invalid_argument);
}

TEST(PentagonTest, DegeneratePentagonThrows) {
    Pentagon p;
    std::istringstream iss("1 1  1 1  1 1  1 1  1 1");
    EXPECT_THROW(iss >> p, std::invalid_argument);
}

TEST(PentagonTest, InvalidPentagonThrows) {
    Pentagon p;
    // неправильная форма, нарушен угол
    std::istringstream iss("0 0  10 0  11 0.5  1 3  0.5 3");
    EXPECT_THROW(iss >> p, std::invalid_argument);
}

// --- MAIN ---
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}