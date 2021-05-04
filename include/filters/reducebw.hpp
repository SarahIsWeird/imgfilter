#if !defined(FILTER_REDUCEBW_HPP)
#define FILTER_REDUCEBW_HPP

#include "filters/subset.hpp"

namespace filters {

class ReduceBW : public Subset {
public:
    std::string getName();
    bool init(int argc, char **argv);
};

};

#endif // FILTER_REDUCEBW_HPP
