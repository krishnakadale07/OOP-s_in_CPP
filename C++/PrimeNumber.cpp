#include <iostream>
using namespace std;

bool isPrime(int number) {
    if (number < 2) {
        return false;
    }

    for (int divisor = 2; divisor * divisor <= number; divisor++) {
        if (number % divisor == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int start, end;

    cout << "Enter the range: ";
    cin >> start >> end;

    if (start > end) {
        swap(start, end);
    }

    cout << "Prime numbers are: ";
    for (int number = start; number <= end; number++) {
        if (isPrime(number)) {
            cout << number << " ";
        }
    }

    cout << endl;
    return 0;
}