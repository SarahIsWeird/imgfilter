#if !defined(FILTER_DITHER_HPP)
#define FILTER_DITHER_HPP

#include "filters/subset.hpp"

namespace filters {

class Dither : public Subset {
public:
    std::string getName();
    int getArgCount();
    bool init(int argc, char **argv);
    sf::Color apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage);
};

};

#endif // FILTER_DITHER_HPP
