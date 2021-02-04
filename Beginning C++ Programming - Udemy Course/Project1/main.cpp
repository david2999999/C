//
// Created by David Jiang on 2/3/2021.
//
#include <iostream>

using namespace std;

void inputTwoNumbers() {
    int num1;
    int num2;

    cout << "Enter first integer:";
    cin >> num1;

    cout << "Enter second integer:";
    cin >> num2;

    cout << "You entered: " << num1 << " and " << num2 << endl;
}

void inputTwoNumbersConsecutively() {
    int num1, num2;

    cout << "Enter 2 integers separated with a space:";
    cin >> num1 >> num2;
    cout << "You entered: " << num1 << " and " << num2 << endl;
}

void inputDoubleValues() {
    int num1;
    double num2;

    cout << "Enter 2 integers separated with a space:";
    cin >> num1 >> num2;
    cout << "You entered: " << num1 << " and " << num2 << endl;
}

int main() {
    inputDoubleValues();
    return 0;
}
