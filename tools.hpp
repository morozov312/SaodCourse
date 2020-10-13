#pragma once
#include "record.hpp"
#include <cstring>
#include <iostream>
bool CheckCin() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        return false;
    }
    return true;
}
