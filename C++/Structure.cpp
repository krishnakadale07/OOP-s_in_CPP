# include <iostream>
using namespace std;

int main() {
    string p, n;
    cout << "Enter the Structure you wanna Create: ";
    cin >> p;

    // Stairs

    if(p == "Stairs"){
    int n;
    cout << "Enter the number of stairs: ";
    cin >> n;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= i; j++){
            cout << "* ";
        }
        cout << endl;
    }
}

    // Pyramid
    
    if( p == "Pyramid"){
    int n;  
    cout << "Enter the number of rows for the pyramid: ";
    cin >> n;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n - i; j++){
            cout << " ";
        }
        for(int k = 1; k <= (2 * i - 1); k++){
            cout << "*";
        }
        cout << endl;
    }
}

    // Daimond

    if( p == "Daimond"){
     int n;

    cout << "Enter number of rows: ";
    cin >> n;

    // Upper half
    for (int i = 1; i <= n; i++) {
        for (int j = i; j < n; j++) {
            cout << " ";
        }

        for (int j = 1; j <= (2 * i - 1); j++) {
            cout << "*";
        }

        cout << endl;
    }

    // Lower half
    for (int i = n - 1; i >= 1; i--) {
        for (int j = n; j > i; j--) {
            cout << " ";
        }

        for (int j = 1; j <= (2 * i - 1); j++) {
            cout << "*";
        }

        cout << endl;
    
    }
}
}
