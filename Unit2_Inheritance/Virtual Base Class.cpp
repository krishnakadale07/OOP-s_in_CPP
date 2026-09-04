#include <iostream>
#include <string>
#include <utility>

class Person {
protected:
    std::string name;

public:
    explicit Person(std::string personName) : name(std::move(personName)) {}

    void displayName() const {
        std::cout << "Name: " << name << '\n';
    }
};

class Student : virtual public Person {
public:
    Student() : Person("Unknown") {}
};

class Employee : virtual public Person {
public:
    Employee() : Person("Unknown") {}
};

class TeachingAssistant : public Student, public Employee {
public:
    explicit TeachingAssistant(std::string assistantName)
        : Person(std::move(assistantName)), Student(), Employee() {}
};

int main() {
    TeachingAssistant assistant("Riya");
    assistant.displayName();
    return 0;
}