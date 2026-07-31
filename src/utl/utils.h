#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

const float max_size = 5000.f;
namespace utl {
    inline void print(std::string& str) {
        std::cout << str << std::endl;
    }
    inline float get_max_size() { return max_size; }

}
