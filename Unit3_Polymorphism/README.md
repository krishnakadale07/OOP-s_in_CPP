Name : Krishna Kadale
ZPRN : 125UAD1240
Div : B
Course : B.Tech (AI & DS)
Unit : 3
List of Programs :  01_Function_Overloading
                    02_Area_Calculator
                    03_Unary_Minus_Operator
                    04_Prefix_Postfix_Increment
                    05_Complex_Number_Addition
                    06_Distance_Comparison
                    07_Friend_Operator_Overloading
                    08_Base_Pointer_Without_Virtual
                    09_Base_Pointer_With_Virtual
                    10_Base_Reference_Virtual_Function
                    11_Abstract_Class
                    12_Polymorphic_Shape_Collection
                    13_Virtual_Destructor
                    14_Object_Slicing
                    15_Payment_System
                    16_Employee_Payroll
Brief Description :

1. Function Overloading

This program defines several add() functions with different parameter types and counts. The compiler selects the matching overload to add two integers, two doubles, or three integers.

2. Area Calculator

This program overloads calculateArea() to calculate the area of a square, rectangle, or circle. The parameter count and type determine which formula is used.

3. Unary Minus Operator

The Number class overloads the unary minus operator. Applying - to an object creates a new Number containing the negated value while leaving the original object unchanged.

4. Prefix Postfix Increment

The current source repeats the unary-minus Number example from Program 3: it overloads operator-() and displays the original and negated values. Despite this file's name, it does not currently demonstrate prefix or postfix increment.

5. Complex Number Addition

The Complex class overloads operator+ to add the real and imaginary components of two complex numbers. Its display function formats the result using the i notation.

6. Distance Comparison

The Distance class overloads the greater-than operator to compare two distances stored in meters. The program displays both values and reports which is greater.

7. Friend Operator Overloading

This program implements addition as a non-member operator+ for an integer on the left and a Complex object on the right. The friend declaration allows the operator to access the complex number's private components.

8. Base Pointer Without Virtual

A base pointer refers to a Derived object, but Base::display() is not virtual. The call therefore uses static binding and invokes the base-class function.

9. Base Pointer With Virtual

Animal::sound() is virtual and is overridden by Dog and Cat. Calling the function through an Animal pointer demonstrates runtime dispatch to the correct derived implementation.

10. Base Reference Virtual Function

Rectangle and Circle override the virtual area() function inherited from Shape. A function accepting a Shape reference calculates and prints the actual derived object's area.

11. Abstract Class

Shape declares area() as a pure virtual function, so it cannot be instantiated directly. Rectangle implements the required function and demonstrates use of the abstract interface.

12. Polymorphic Shape Collection

The program stores Rectangle and Circle objects as unique_ptr<Shape> values in one vector. It iterates over the collection and calls virtual functions to display each shape and calculate its area.

13. Virtual Destructor

A Derived object is created and deleted through a Base pointer. The virtual base destructor ensures both Derived and Base destructors run during cleanup.

14. Object Slicing

A Derived object is passed once by value and once by reference to Base parameters. Passing by value slices off the derived portion and calls Base::display(), while passing by reference preserves runtime dispatch to Derived::display().

15. Payment System

The current source repeats the object-slicing example from Program 14: it compares passing a Derived object by value and by reference. Despite this file's name, it does not currently contain payment classes or salary calculations.

16. Employee Payroll

Employee is an abstract base class with a virtual salary calculation. PermanentEmployee adds basic salary and allowance, while ContractEmployee calculates pay from hourly rate and hours worked; a shared payslip function prints their details and salary.
