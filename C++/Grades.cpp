#include <iostream>
using namespace std;

int main( ){
    int n ;
    cout << " Enter Marks :";
    cin >> n;

    if(n >= 90 && n <= 100)
    { 
        cout << " Grade A" << endl;
    }
    else if(n >= 80 && n <= 89)
    { 
        cout << " Grade B" << endl;
    }
    else if(n >= 70 && n <= 79)  { 
        cout << " Grade C" << endl;
    }
    else if(n >= 60 && n <= 69)  { 
        cout << " Grade D" << endl;
    }
    else if(n >= 50 && n <= 59)  { 
        cout << " Grade F" << endl;
    }
    else if(n >= 0 && n <= 49){
        cout << "fail" << endl;
    }
    else
    {
        cout << " Invalid Marks" << endl;
    }
}