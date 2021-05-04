#include "filters/threshold.hpp"

#include <iostream>

std::string filters::Threshold::getName() {
    return "threshold";
}

int filters::Threshold::getArgCount() {
    return 3;
}

bool filters::Threshold::init(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "The threshold filter requires three arguments." << std::endl;
        return false;
    }

    thresholdR = std::stoi(argv[0]);
    thresholdG = std::stoi(argv[1]);
    thresholdB = std::stoi(argv[2]);

    if (thresholdR < 0 || thresholdR > 255 || thresholdG < 0 || thresholdG > 255 || thresholdB < 0 || thresholdB > 255) {
        std::cerr << "The factors need to be between 0 and 255, inclusive." << std::endl;
        return false;
    }

    return true;
}

sf::Color filters::Threshold::apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage) {
    return sf::Color(
        old.r >= this->thresholdG ? 255 : 0,
        old.g >= this->thresholdG ? 255 : 0,
        old.b >= this->thresholdB ? 255 : 0
    );
}