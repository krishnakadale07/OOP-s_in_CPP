#include <iostream>

class Base {
public:
    virtual void display() const {
        std::cout << "Base object\n";
    }

    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void display() const override {
        std::cout << "Derived object\n";
    }
};

void displayByValue(Base object) {
    object.display();
}

void displayByReference(const Base& object) {
    object.display();
}

int main() {

    Derived derived;

    std::cout << "Passing by value: ";
    displayByValue(derived);

    std::cout << "Passing by reference: ";
    displayByReference(derived);

    return 0;
}