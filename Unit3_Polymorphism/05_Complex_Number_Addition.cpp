#include <iostream>

class Complex {
private:
    int real;
    int imaginary;

public:
    Complex(int realPart = 0, int imaginaryPart = 0)
        : real(realPart), imaginary(imaginaryPart) {}

    Complex operator+(const Complex& other) const {
        return Complex(
            real + other.real,
            imaginary + other.imaginary
        );
    }

    void display() const {

        std::cout << real;

        if (imaginary >= 0) {
            std::cout << " + ";
        } else {
            std::cout << " - ";
        }

        std::cout
            << (imaginary >= 0 ? imaginary : -imaginary)
            << "i\n";
    }
};

int main() {

    Complex first(2, 3);
    Complex second(4, 5);

    Complex sum = first + second;

    std::cout << "First complex number: ";
    first.display();

    std::cout << "Second complex number: ";
    second.display();

    std::cout << "Sum: ";
    sum.display();

    return 0;
}