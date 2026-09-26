#include <iostream>

class Number {
private:
    int value;

public:
    explicit Number(int givenValue)
        : value(givenValue) {}

    Number operator-() const {
        return Number(-value);
    }

    void display() const {
        std::cout << value << '\n';
    }
};

int main() {

    Number first(25);

    Number second = -first;

    std::cout << "Original value: ";
    first.display();

    std::cout << "Negated value: ";
    second.display();

    return 0;
}