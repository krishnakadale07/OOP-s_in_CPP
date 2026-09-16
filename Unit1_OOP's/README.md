Name : Krishna Kadale
ZPRN : 125UAD1240
Div : B
Course : B.Tech (AI & DS)
Unit : 1 
List of Programs :  Class and Object
                    Constructor and Destructor 
                    Inline Member function and Friend Function
                    Static Member 
Brief Description : 

1. Class and Object Program

The program demonstrates the basic concept of classes and 
objects in C++. A Student class is created with two data 
members, name and age, and a member function show() to 
display them. An object s1 of the Student class is created, 
its values are assigned, and the show() function is called 
to display the student details.

2. Constructor and Destructor Program

The program demonstrates constructors and destructors in C
++. The Demo() constructor automatically executes when the 
object d is created, while the ~Demo() destructor 
automatically executes when the object goes out of scope at 
the end of main(). Both display messages to show when they 
are called.

3. Inline Member Function and Friend Function

This program demonstrates how to access a class's private 
data using both inline and friend functions. The Test class 
encapsulates a private integer that can be retrieved through 
getValue(), an inline member function that is optimized for 
quick execution because it is defined directly within the 
class body. Additionally, the program declares an external 
show function as a friend, which grants this non-member 
function the special permission to bypass standard 
encapsulation rules and directly access and print the 
private value of a Test object.

4. Static Member 

This program illustrates the concept of a shared class state 
by utilizing a static member variable. Inside the Student 
class, a static integer named count is declared and then 
initialized to zero outside the class. Because static 
variables belong to the class itself rather than to any 
individual object instance, this count variable is shared 
across all objects. Every time a new Student object is 
instantiated, the constructor increments this shared 
variable, allowing the program to effectively track and 
display the total number of created objects.
