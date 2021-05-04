#include "filters/subset.hpp"

#include <iostream>

inline int colorDiff(sf::Color c1, sf::Color c2) {
    return (c1.r - c2.r) * (c1.r - c2.r) + (c1.g - c2.g) * (c1.g - c2.g) + (c1.b - c2.b) * (c1.b - c2.b);
}

sf::Color filters::Subset::apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage) {
    int oldDiff = ~(1 << 31);
    sf::Color bestColor;
    int currentDiff;

    for (sf::Color color : this->colors) {
        currentDiff = colorDiff(color, old);
        if (oldDiff < currentDiff) continue;

        oldDiff = currentDiff;
        bestColor = color;
    }

    return bestColor;
}