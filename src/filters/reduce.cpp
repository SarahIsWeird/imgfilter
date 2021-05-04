#include "filters/reduce.hpp"

#include <iostream>

std::string filters::Reduce::getName() {
    return "reduce";
}

bool filters::Reduce::init(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "The reduce filter requires three arguments." << std::endl;
        return false;
    }

    int rFactor = std::stoi(argv[0]);
    int gFactor = std::stoi(argv[1]);
    int bFactor = std::stoi(argv[2]);

    if (rFactor <= 0 || rFactor > 255 || gFactor <= 0 || gFactor > 255 || bFactor <= 0 || gFactor > 255) {
        std::cerr << "The factors need to be between 1 and 255, inclusive." << std::endl;
        return false;
    }

    for (int r = 0; r < rFactor; r++) {
        for (int g = 0; g < gFactor; g++) {
            for (int b = 0; b < bFactor; b++) {
                this->colors.push_back(sf::Color(r * (255 / rFactor), g * (255 / gFactor), b * (255 / bFactor)));
            }
        }
    }

    return true;
}