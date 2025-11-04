#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <typeinfo>

#include "../include/Figure.h"
#include "../include/Trapezoid.h"
#include "../include/Square.h"
#include "../include/Rectangle.h"
#include "../include/Array.h"

template <typename T>
void inputFigure(Figure<T>& fig, const std::string& input) {
    std::istringstream iss(input);
    iss >> fig;
}

// --- TRAPEZOID TESTS ---
TEST(TrapezoidTest, InputAndOutput) {
    Trapezoid<double> t;
    inputFigure(t, "0 0  4 0  3 3  1 3");
    std::ostringstream oss;
    oss << t;
    EXPECT_EQ(oss.str(), "(0, 0) (4, 0) (3, 3) (1, 3) ");
}

TEST(TrapezoidTest, AreaAndCenter) {
    Trapezoid<double> t;
    inputFigure(t, "0 0  6 0  4 4  2 4");
    EXPECT_DOUBLE_EQ(double(t), 16.0);
    Point<double> c = t.center();
    EXPECT_DOUBLE_EQ(c.x, 3.0);
    EXPECT_DOUBLE_EQ(c.y, 2.0);
}

TEST(TrapezoidTest, ValidateCorrectAndIncorrect) {
    Trapezoid<double> t1;
    inputFigure(t1, "0 0  4 0  3 3  1 3");
    EXPECT_TRUE(t1.validate());

    Trapezoid<double> t2;
    EXPECT_THROW(inputFigure(t2, "0 0  4 0  3 3  0 3"), std::invalid_argument);
}

TEST(TrapezoidTest, DegenerateCaseThrows) {
    Trapezoid<double> t;
    EXPECT_THROW(inputFigure(t, "1 1  1 1  1 1  1 1"), std::invalid_argument);
}

TEST(TrapezoidTest, CopyAndMove) {
    Trapezoid<double> t1;
    inputFigure(t1, "0 0  4 0  3 3  1 3");
    Trapezoid<double> t2 = t1;
    EXPECT_TRUE(t1 == t2);

    Trapezoid<double> t3 = std::move(t1);
    std::ostringstream oss;
    oss << t3;
    EXPECT_EQ(oss.str(), "(0, 0) (4, 0) (3, 3) (1, 3) ");
}

// --- SQUARE TESTS ---
TEST(SquareTest, ValidateAndArea) {
    Square<double> s;
    inputFigure(s, "0 0  2 0  2 2  0 2");
    EXPECT_TRUE(s.validate());
    EXPECT_DOUBLE_EQ(double(s), 4.0);
}

TEST(SquareTest, InvalidThrows) {
    Square<double> s;
    EXPECT_THROW(inputFigure(s, "0 0  3 0  4 3  1 3"), std::invalid_argument);
}

TEST(SquareTest, DegenerateThrows) {
    Square<double> s;
    EXPECT_THROW(inputFigure(s, "1 1  1 1  1 1  1 1"), std::invalid_argument);
}

// --- RECTANGLE TESTS ---
TEST(RectangleTest, ValidateAndArea) {
    Rectangle<double> r;
    inputFigure(r, "0 0  4 0  4 2  0 2");
    EXPECT_TRUE(r.validate());
    EXPECT_DOUBLE_EQ(double(r), 8.0);
}

TEST(RectangleTest, Center) {
    Rectangle<double> r;
    inputFigure(r, "0 0  4 0  4 2  0 2");
    Point<double> c = r.center();
    EXPECT_DOUBLE_EQ(c.x, 2.0);
    EXPECT_DOUBLE_EQ(c.y, 1.0);
}

TEST(RectangleTest, InvalidThrows) {
    Rectangle<double> r;
    EXPECT_THROW(inputFigure(r, "0 0  3 0  5 2  1 3"), std::invalid_argument);
}

// --- ARRAY TESTS ---
TEST(ArrayTest, AddRemoveSize) {
    Array<Figure<double>> arr;
    arr.add(std::make_shared<Trapezoid<double>>());
    arr.add(std::make_shared<Square<double>>());
    arr.add(std::make_shared<Rectangle<double>>());
    EXPECT_EQ(arr.getSize(), 3);

    arr.remove(1);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_THROW(arr.remove(10), std::out_of_range);
}

TEST(ArrayTest, TotalSurface) {
    Array<Figure<double>> arr;
    auto t = std::make_shared<Trapezoid<double>>();
    inputFigure(*t, "0 0  4 0  3 3  1 3");
    arr.add(t);

    auto s = std::make_shared<Square<double>>();
    inputFigure(*s, "0 0  2 0  2 2  0 2");
    arr.add(s);

    EXPECT_NEAR(arr.totalSurface(), 13.0, 1.0);
}

TEST(ArrayTest, OutOfRangeAccess) {
    Array<Figure<double>> arr;
    arr.add(std::make_shared<Trapezoid<double>>());
    EXPECT_THROW(arr[10], std::out_of_range);
}

TEST(ArrayTest, Polymorphism) {
    Array<Figure<double>> arr;
    arr.add(std::make_shared<Trapezoid<double>>());
    arr.add(std::make_shared<Square<double>>());
    arr.add(std::make_shared<Rectangle<double>>());

    for (size_t i = 0; i < arr.getSize(); ++i)
        EXPECT_NE(typeid(arr[i]), typeid(Figure<double>));
}

TEST(FigureTest, AbstractClass) {
    static_assert(!std::is_constructible<Figure<double>>::value,
                  "Figure must be abstract");
}

// --- MAIN ---
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
