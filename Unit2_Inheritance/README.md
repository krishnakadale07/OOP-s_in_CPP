Div : B
Course : B.Tech (AI & DS)
Unit : 1 
List of Programs :  Abstract Class
                    Basic Single Innheritance
                    Constructor and Destructor Order
                    Employee Payrol System
                    Friend Class
                    Function Overriding
                    Heirarchical inheritance
                    Multilevel Innheritance
                    Multiple Inheritance
                    Multiple Inhertance Ambiguity
                    Nested Class
                    Parameterized Base Constructor
                    Protected member access
                    Public and Private Inheritance
                    Vehicle Rental System
                    Virtual Base Class 
Brief Description :
1. Abstract Class
This program demonstrates the use of abstract classes and 
pure virtual functions to enforce a standard interface 
across different shapes. It defines an abstract base class 
Shape with a pure virtual function area(), meaning Shape 
itself cannot be instantiated. Instead, it is inherited by 
Rectangle and Circle classes, which are forced to provide 
their own specific mathematical implementations for 
calculating their respective areas. The main function then 
successfully creates objects of these derived classes and 
calls their overridden area() methods to output the 
results.  

2. Basic Single Innheritance
This file illustrates the concept of basic single inheritance, where one class acquires the properties of another. The base class, Person, is designed to store and display a name string. The derived class, Student, inherits from Person and extends its functionality by adding a private integer for a roll number. By calling the inherited displayName() method inside its own displayStudent() method, the Student class cleanly displays both the inherited name and its specific roll number.  

3. Constructor and Destructor Order
This code provides a clear demonstration of the execution 
sequence for constructors and destructors in an inheritance 
hierarchy. It defines a simple Base class and a Derived 
class that inherits from it, with each containing print 
statements in their respective constructors and destructors. 
When a Derived object is instantiated and then destroyed in 
the main function, the terminal output proves that 
constructors are executed top-down (Base first, then 
Derived), while destructors are executed in the exact 
reverse order (Derived first, then Base).  

4. Employee Payrol System
This program implements a practical payroll system using 
abstract classes and polymorphism. The abstract base class 
Employee stores common details like an ID and name, while 
defining a pure virtual function calculateSalary(). Two 
specialized derived classes, PermanentEmployee and 
ContractEmployee, override this function to apply their 
distinct payment logic—adding allowances to a basic salary 
for permanent staff, or multiplying an hourly rate by hours 
worked for contractors. A standalone displayPaySlip function 
accepts a base class reference to dynamically calculate and 
print the correct salary for any given employee type at 
runtime.  

5. Friend Class
This file explains how to grant a separate class full access 
to another class's private members using the friend keyword. 
The Account class encapsulates a private balance variable 
and explicitly declares the Auditor class as a friend. 
Because of this declaration, when the Auditor class's 
inspect method is called, it is legally permitted to bypass 
standard object-oriented encapsulation limits to directly 
read and output the private balance of the passed Account 
object.  

6. Function Overriding
This code demonstrates function overriding, a key feature of 
runtime polymorphism where derived classes alter the 
behavior of a base class method. The base Vehicle class 
contains a virtual move() method that prints a generic 
movement message. The Car and Boat derived classes override 
this method to print specific messages reflecting how they 
move on roads or water, respectively. When move() is called 
on individual Car and Boat objects, the program 
automatically executes the specialized version of the 
function defined in each derived class.  

7. Heirarchical inheritance
This program showcases hierarchical inheritance, a structure 
where multiple distinct derived classes inherit from one 
common base class. Both the Car and Bike classes inherit the 
shared registrationNumber variable and the start() method 
from the Vehicle base class. While they share these core 
vehicle traits, each derived class also implements its own 
unique functionality—such as openBoot() for the car and 
helmetReminder() for the bike—proving how a single base can 
branch into entirely different specializations.  

8. Multilevel Innheritance
This code illustrates multilevel inheritance by building a 
vertical chain of classes, where each derived class serves 
as the base for the next. The hierarchy starts with the 
Person class (handling the name), moves down to the Employee 
class (adding an ID), and ends at the Manager class (adding 
a team size). Because inheritance accumulates down the 
chain, the Manager object successfully inherits the traits 
of both its direct parent (Employee) and its grandparent 
(Person), allowing its showManager() method to display the 
name, ID, and team size together.  

9. Multiple Inheritance
This file demonstrates multiple inheritance, allowing a 
single derived class to inherit features from more than one 
base class concurrently. The Student class is derived from 
both the Academic class, which holds academic scores, and 
the Sports class, which manages sports scores. By inheriting 
from both, the Student class gains access to the protected 
data of both parents, enabling its showTotal() method to 
easily calculate and print the combined sum of the academic 
and sports marks.  


10. Multiple Inhertance Ambiguity
This program addresses the ambiguity problem (often related 
to the diamond problem) that occurs in multiple inheritance 
when different base classes share identically named methods. 
Because both the Academic and Sports base classes contain a 
method named display(), the derived Student class cannot 
inherently know which one to execute. To resolve this naming 
collision, the program utilizes the scope resolution 
operator (::), allowing the developer to explicitly call 
Academic::display() and Sports::display() to ensure the 
compiler knows exactly which function to run.  


11. Nested Class
This program demonstrates the creation and usage of a nested 
class, where one class is defined entirely within the scope 
of another. The University class acts as an outer container 
for the inner Department class, which is equipped with its 
own private name string and a method to display it. In the 
main function, the program successfully instantiates the 
inner class by using the scope resolution operator 
(University::Department) and calls its display method, 
illustrating how nested classes can be utilized to logically 
group dependent structures together and avoid cluttering the 
global scope. 


12. Parameterized Base Constructor
This file illustrates how a derived class can pass values to 
a parameterized constructor of its base class during 
instantiation. The base Person class requires a string 
argument to initialize its protected name variable. When the 
derived Student class is created, its constructor utilizes 
an initialization list to explicitly call the Person 
constructor and pass the name string upward, ensuring the 
base class is properly initialized before the Student class 
executes its own logic to assign its specific rollNumber 
variable. 


13. Protected member access
This code highlights the behavior of the protected access 
modifier within an inheritance relationship. The base 
Employee class contains a protected name string, meaning it 
cannot be accessed directly from outside the class, but it 
remains fully visible and accessible to any derived classes. 
The derived Developer class takes advantage of this by 
directly utilizing the inherited name variable alongside its 
own private language variable within its display() method, 
demonstrating how protected members facilitate secure data 
sharing down the inheritance chain. 


14. Public and Private Inheritance
This program contrasts the structural differences between 
public and private inheritance modes in C++. The 
PublicDerived class inherits from Base publicly, allowing 
the base class's show() method to remain public and callable 
directly from the main function. Conversely, the 
PrivateDerived class inherits from Base privately, which 
changes the inherited show() method's access level to 
private within the derived class. To execute it, the derived 
class must provide its own public wrapper function, 
callBaseShow(), to access the hidden base method internally. 


15. Vehicle Rental System
This file models a practical vehicle rental system by 
utilizing virtual functions and method overriding to achieve 
polymorphism. The base Vehicle class defines standard 
virtual methods for displaying details and calculating daily 
rent. The derived Car class overrides the display function 
to include its door count, while the derived Bike class not 
only adds engine capacity to its display but also completely 
overrides the rent calculation to apply a custom 10% 
discount on the standard calculation, demonstrating how 
derived classes can uniquely tailor inherited behaviors. 


16. Virtual Base Class
This program resolves the classic "diamond problem" in 
multiple inheritance by employing a virtual base class. Both 
the Student and Employee classes inherit from the Person 
base class using the virtual keyword. When the 
TeachingAssistant class later inherits from both Student and 
Employee, the virtual inheritance guarantees that only a 
single, shared instance of the Person class is created in 
memory, preventing data duplication and ambiguity while 
allowing the TeachingAssistant constructor to initialize the 
shared Person base directly. 
