#include "filters/reducebw.hpp"

#include <iostream>

std::string filters::ReduceBW::getName() {
    return "reducebw";
}

int filters::ReduceBW::getArgCount() {
    return 1;
}

bool filters::ReduceBW::init(int argc, char **argv) {
    if (argc != 1) {
        std::cerr << "The reducebw filter requires one argument." << std::endl;
        return false;
    }

    int factor = std::stoi(argv[0]);

    if (factor <= 0 || factor > 255) {
        std::cerr << "The factor needs to be between 1 and 255, inclusive." << std::endl;
        return false;
    }

    for (int i = 0; i < factor; i++) {
        this->colors.push_back(sf::Color(i * (255 / factor), i * (255 / factor), i * (255 / factor)));
    }

    return true;
}