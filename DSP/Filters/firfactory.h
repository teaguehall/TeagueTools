#ifndef FIRFACTORY_H
#define FIRFACTORY_H

#include "firfilter.h"
#include <memory>
#include <vector>

///
class FIRFactory
{
    public:
        /// Identifies the FIR filter type (type 1, 2, 3, 4) and returns the appropraite FIR object pointer
        /// @param impulse_response Impulse response of FIR filter
        /// @return unique pointer to an appropriate FIR filter type object
        static std::unique_ptr<FIRFilter> getFilter(std::vector<double> impulse_response);

    private:
        /// Determines whether an impulse response corresponds to a linear phase type 1 FIR filter
        /// @param impulse_response Impulse response
        /// @return TRUE if impulse response corresponds to linear phase type 1 FIR filter
        static bool isLinearPhaseType1(std::vector<double> impulse_response);

        /// Determines whether an impulse response corresponds to a linear phase type 2 FIR filter
        /// @param impulse_response Impulse response
        /// @return TRUE if impulse response corresponds to linear phase type 2 FIR filter
        static bool isLinearPhaseType2(std::vector<double> impulse_response);

        /// Determines whether an impulse response corresponds to a linear phase type 3 FIR filter
        /// @param impulse_response Impulse response
        /// @return TRUE if impulse response corresponds to linear phase type 3 FIR filter
        static bool isLinearPhaseType3(std::vector<double> impulse_response);

        /// Determines whether an impulse response corresponds to a linear phase type 4 FIR filter
        /// @param impulse_response Impulse response
        /// @return TRUE if impulse response corresponds to linear phase type 4 FIR filter
        static bool isLinearPhaseType4(std::vector<double> impulse_response);
};

#endif // FIRFACTORY_H
