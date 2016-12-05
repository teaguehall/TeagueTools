#ifndef FIRFACTORY_H
#define FIRFACTORY_H

#include "firfilter.h"
#include <memory>
#include <vector>

class FIRFactory
{
    public:
        static std::unique_ptr<FIRFilter> getFilter(std::vector<double> impulse_response);

    private:
        static bool isLinearPhaseType1(std::vector<double> impulse_response);
        static bool isLinearPhaseType2(std::vector<double> impulse_response);
        static bool isLinearPhaseType3(std::vector<double> impulse_response);
        static bool isLinearPhaseType4(std::vector<double> impulse_response);
};

#endif // FIRFACTORY_H
