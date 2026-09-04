# include <iostream>
using namespace std;

int main() {
    int a, b, c ,n;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    cout << "Enter the Operation" << endl;
    cout << "1] Addition \n 2] Substraction \n 3] Multiplication \n 4] Division \n";
    cin >> n;

    if( n == 1){
    c = a + b;
    cout << "Sum is: " << c << endl;
    }

    if( n == 2 ){
    c = a * b;
    cout << "Multiplication is: " << c << endl;
    }

    if( n == 3){
    c = a - b;
    cout << "Sub is: " << c << endl;
    }

    if (n == 4){
    c = a / b;
    cout << "Division is: " << c << endl;
    }
    
    return 0;
}