#include "filters/bw.hpp"

std::string filters::BW::getName() {
    return "bw";
}

bool filters::BW::init(int argc, char **argv) {
    return true;
}

sf::Color filters::BW::apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage) {
    int val = (old.r + old.g + old.b) / 3;

    return sf::Color(val, val ,val);
}