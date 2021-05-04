#include "filters/dither.hpp"

#include <iostream>
#include <algorithm>

std::string filters::Dither::getName() {
    return "dither";
}

int filters::Dither::getArgCount() {
    return 3;
}

bool filters::Dither::init(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "The dither filter requires one argument." << std::endl;
        return false;
    }

    int factor = std::stoi(argv[0]);

    if (factor <= 0 || factor > 255) {
        std::cerr << "The factor needs to be between 1 and 255, inclusive." << std::endl;
        return false;
    }

    // Oof. The triple loop
    for (int i = 0; i < factor; i++) {
        for (int j = 0; j < factor; j++) {
            for (int k = 0; k < factor; k++) {
                this->colors.push_back(sf::Color(i * (255 / factor), j * (255 / factor), k * (255 / factor)));
            }
        }
    }

    return true;
}

sf::Color filters::Dither::apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage) {
    sf::Color newColor = Subset::apply(old, x, y, oldImage);
    sf::Color tmp;
    sf::Vector2u size = oldImage->getSize();

    float quantErrorR = old.r - newColor.r;
    float quantErrorG = old.g - newColor.g;
    float quantErrorB = old.b - newColor.b;

    if (x < size.x - 1) {
        tmp = oldImage->getPixel(x + 1, y);
        oldImage->setPixel(x + 1, y, sf::Color(
            std::clamp((int) (tmp.r + quantErrorR * 7 / 16), 0, 255),
            std::clamp((int) (tmp.g + quantErrorG * 7 / 16), 0, 255),
            std::clamp((int) (tmp.b + quantErrorB * 7 / 16), 0, 255)));
    }
        
    if (y < size.y - 1) {
        tmp = oldImage->getPixel(x, y + 1);
        oldImage->setPixel(x, y + 1, sf::Color(
            std::clamp((int) (tmp.r + quantErrorR * 5 / 16), 0, 255),
            std::clamp((int) (tmp.g + quantErrorG * 5 / 16), 0, 255),
            std::clamp((int) (tmp.b + quantErrorB * 5 / 16), 0, 255)));
        
        if (x < size.x - 1) {
            tmp = oldImage->getPixel(x + 1, y + 1);
            oldImage->setPixel(x + 1, y + 1, sf::Color(
                std::clamp((int) (tmp.r + quantErrorR * 1 / 16), 0, 255),
                std::clamp((int) (tmp.g + quantErrorG * 1 / 16), 0, 255),
                std::clamp((int) (tmp.b + quantErrorB * 1 / 16), 0, 255)));
        }

        if (x > 0) {
            tmp = oldImage->getPixel(x - 1, y + 1);
            oldImage->setPixel(x - 1, y + 1, sf::Color(
                std::clamp((int) (tmp.r + quantErrorR * 3 / 16), 0, 255),
                std::clamp((int) (tmp.g + quantErrorG * 3 / 16), 0, 255),
                std::clamp((int) (tmp.b + quantErrorB * 3 / 16), 0, 255)));
        }
    }

    return newColor;
}