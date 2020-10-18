//
// Created by David Jiang on 10/18/2020.

#include <iostream>

void ifStatement() {
    int curVal = 0, val = 0;

    if (std::cin >> curVal) {
        int count = 1;

        while (std::cin >> val) {
            if (val == curVal) {
                count++;
            } else {
                std::cout << curVal << " occurs "
                          << count << " times" << std::endl;
                curVal = val;
                count = 1;
            }
        }

        std::cout << curVal << " occurs "
                  << count << " times" << std::endl;
    }
}