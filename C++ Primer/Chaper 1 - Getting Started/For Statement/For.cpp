//
// Created by David Jiang on 8/9/2020.
//

#include <iostream>

int For() {
    int sum = 0;

    for (int val = 1; val <= 10; ++val) {
        sum += val;
    }

    std::cout << "sum of 1 to 10 inclusive is " << sum << std::endl;

    return 0;
}