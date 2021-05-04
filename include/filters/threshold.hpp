#if !defined(FILTER_THRESHOLD_HPP)
#define FILTER_THRESHOLD_HPP

#include "filter.hpp"

namespace filters {

class Threshold : public AbstractFilter {
public:
    std::string getName();
    bool init(int argc, char **argv);
    sf::Color apply(sf::Color old, unsigned int x, unsigned int y, sf::Image *oldImage);

private:
    int thresholdR;
    int thresholdG;
    int thresholdB;
};

};

#endif // FILTER_THRESHOLD_HPP
