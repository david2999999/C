//
// Created by David Jiang on 8/9/2020.
//

#include <iostream>

int UnknownNumberOfInput() {
    int sum = 0, val = 0;

    // read until end of file, calculating a running total of all values read
    while (std::cin >> val) {
        sum += val;
    }

    std::cout << "Sum is " << sum << std::endl;

    return 0;
}