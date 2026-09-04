#include <iostream>
using namespace std;

int main(){
    int a , b , c , i , largest;
    cout << "Enter the value of a :";
    cin >> a;

    cout <<"Enter the value of b :";
    cin >> b;

    cout <<"Enter the value of c :";
    cin >> c;
     

    if(a > b && b > c){
        largest = a;
    }else if(b > a && b > c){
        largest = b;
    }else{
        largest = c;
    }

    cout << "The largest number is : " << largest << endl;
}
    
