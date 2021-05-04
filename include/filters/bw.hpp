#if !defined(FILTER_BW_HPP)
#define FILTER_BW_HPP

#include "filter.hpp"

namespace filters {

class BW : public AbstractFilter {
public:
    std::string getName();
    bool init(int argc, char **argv);
    sf::Color apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage);
};

};

#endif // FILTER_BW_HPP
