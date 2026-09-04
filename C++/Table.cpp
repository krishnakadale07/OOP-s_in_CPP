#include<iostream>
using namespace std;

int main()
{
    int n , i ;
    cout << "Enter the number of the table you want :";

    cin >> n ;

    for ( i = 1 ; i<= 10 ; i++ ){
        cout << n << " * " << i << " = " << n * i << endl ;
        
    }

}