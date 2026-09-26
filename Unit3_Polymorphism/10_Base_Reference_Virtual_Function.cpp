#include <iostream>

class Shape {
public:
    virtual double area() const {
        return 0.0;
    }

    virtual ~Shape() = default;
};

class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double givenLength, double givenWidth)
        : length(givenLength), width(givenWidth) {}

    double area() const override {
        return length * width;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double givenRadius)
        : radius(givenRadius) {}

    double area() const override {
        constexpr double PI = 3.141592653589793;
        return PI * radius * radius;
    }
};

void printArea(const Shape& shape) {
    std::cout << "Area: " << shape.area() << '\n';
}

int main() {

    Rectangle rectangle(5.0, 3.0);
    Circle circle(2.0);

    printArea(rectangle);
    printArea(circle);

    return 0;
}