#if !defined(FILTER_ISOLATE_HPP)
#define FILTER_ISOLATE_HPP

#include "filter.hpp"

namespace filters {

class Isolate : public AbstractFilter {
public:
    std::string getName();
    bool init(int argc, char **argv);
    sf::Color apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage);

private:
    sf::Color (*isolator)(sf::Color);
};

};

#endif // FILTER_ISOLATE_HPP
