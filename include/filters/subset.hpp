#if !defined(FILTER_SUBSET_HPP)
#define FILTER_SUBSET_HPP

#include "filter.hpp"

#include <vector>

namespace filters {

class Subset : public AbstractFilter {
public:
    virtual std::string getName() = 0;
    virtual int getArgCount() = 0;
    virtual bool init(int argc, char **argv) = 0;
    sf::Color apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage);

protected:
    std::vector<sf::Color> colors;
};

};

#endif // FILTER_SUBSET_HPP
