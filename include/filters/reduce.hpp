#if !defined(FILTER_REDUCE_HPP)
#define FILTER_REDUCE_HPP

#include "filters/subset.hpp"

namespace filters {

class Reduce : public Subset {
public:
    std::string getName();
    int getArgCount();
    bool init(int argc, char **argv);
};

};

#endif // FILTER_REDUCE_HPP
