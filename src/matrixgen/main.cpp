//
// Created by Jan on 22.11.2020.
//

#include <iostream>
#include <basics/Transform.h>

int main() {
    std::cout << crayg::Transform::withRotation(0, 90, 0).matrix << std::endl;
}