//
// Created by David Jiang on 8/9/2020.
//

#include <iostream>

int While() {
    int sum = 0, val = 1;

    while (val <= 10) {
        sum += val;
        ++val;
    }

    std::cout << "sum of 1 to 10 inclusive is " << sum << std::endl;

    return 0;
}
