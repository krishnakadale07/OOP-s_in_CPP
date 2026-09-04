#include <iostream>
#include <string>
#include <utility>

class Employee {
protected:
    int employeeId;
    std::string name;

public:
    Employee(int id, std::string employeeName)
        : employeeId(id), name(std::move(employeeName)) {}

    virtual double calculateSalary() const = 0;

    void displayBasicDetails() const {
        std::cout << "Employee ID: " << employeeId << '\n';
        std::cout << "Name: " << name << '\n';
    }

    virtual ~Employee() = default;
};

class PermanentEmployee : public Employee {
private:
    double basicSalary;
    double allowance;

public:
    PermanentEmployee(int id, std::string employeeName, double basic, double extra)
        : Employee(id, std::move(employeeName)),
          basicSalary(basic),
          allowance(extra) {}

    double calculateSalary() const override {
        return basicSalary + allowance;
    }
};

class ContractEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;

public:
    ContractEmployee(int id, std::string employeeName, double rate, int hours)
        : Employee(id, std::move(employeeName)),
          hourlyRate(rate),
          hoursWorked(hours) {}

    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
};

void displayPaySlip(const Employee& employee) {
    employee.displayBasicDetails();
    std::cout << "Salary: " << employee.calculateSalary() << "\n\n";
}

int main() {
    PermanentEmployee permanentEmployee(101, "Asha", 40000.0, 8000.0);
    ContractEmployee contractEmployee(102, "Vikas", 500.0, 80);

    displayPaySlip(permanentEmployee);
    displayPaySlip(contractEmployee);

    return 0;
}