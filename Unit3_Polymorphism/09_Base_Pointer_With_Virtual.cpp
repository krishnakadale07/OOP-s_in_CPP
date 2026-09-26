#include <iostream>

class Animal {
public:
    virtual void sound() const {
        std::cout << "Animal makes a sound\n";
    }

    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void sound() const override {
        std::cout << "Dog barks\n";
    }
};

class Cat : public Animal {
public:
    void sound() const override {
        std::cout << "Cat meows\n";
    }
};

int main() {

    Dog dog;
    Cat cat;

    Animal* animal = &dog;
    animal->sound();

    animal = &cat;
    animal->sound();

    return 0;
}