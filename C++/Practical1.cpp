//Write a C++ program to find the sum of individual digits of a positive integer
# include <iostream>
using namespace std;

int main() {
	int number, sum = 0;

	cout << "Enter a positive integer: ";
	cin >> number;

	while (number > 0) {
		sum += number % 10;
		number /= 10;
	}

	cout << "Sum of individual digits: " << sum << endl;
	return 0;
}
