#include <iostream>

int calculateArea(int side) {
    return side * side;
}

int calculateArea(int length, int width) {
    return length * width;
}

double calculateArea(double radius) {
    constexpr double PI = 3.141592653589793;
    return PI * radius * radius;
}

int main() {

    std::cout << "Square Area: "
              << calculateArea(5) << '\n';

    std::cout << "Rectangle Area: "
              << calculateArea(6, 4) << '\n';

    std::cout << "Circle Area: "
              << calculateArea(2.0) << '\n';

    return 0;
}