#include "filters/isolate.hpp"

#include <iostream>

static sf::Color isolateR(sf::Color oldColor) {
    return sf::Color(oldColor.r, 0, 0);
}

static sf::Color isolateG(sf::Color oldColor) {
    return sf::Color(0, oldColor.g, 0);
}

static sf::Color isolateB(sf::Color oldColor) {
    return sf::Color(0, 0, oldColor.b);
}

std::string filters::Isolate::getName() {
    return "isolate";
}

bool filters::Isolate::init(int argc, char **argv) {
    if (argc != 1) {
        std::cerr << "The isolate filter requires one argument." << std::endl;
        return false;
    }

    std::string channel = argv[0];

    if (channel == "r" || channel == "R") {
        this->isolator = isolateR;
        return true;
    } else if (channel == "g" || channel == "G") {
        this->isolator = isolateG;
        return true;
    } else if (channel == "b" || channel == "B") {
        this->isolator = isolateB;
        return true;
    }

    std::cerr << "You can only isolate the r, g or b channel." << std::endl;
    return false;
}

sf::Color filters::Isolate::apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage) {
    return (*this->isolator)(old);
}