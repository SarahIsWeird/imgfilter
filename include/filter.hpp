#if !defined(FILTER_HPP)
#define FILTER_HPP

#include <SFML/Graphics.hpp>

namespace filters {

class AbstractFilter {
public:
    virtual std::string getName() = 0;
    virtual bool init(int argc, char **argv) = 0;
    virtual sf::Color apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage) = 0;
};

};

#endif // FILTER_HPP
