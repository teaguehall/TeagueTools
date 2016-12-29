#ifndef FIRTYPE1_H
#define FIRTYPE1_H

#include "firfilter.h"

/// FIRType1 implements an FIR filter of linear phase type 1. This implementation
/// takes advantage of the filter symmetry to reduce the number of multiplications needed
/// during a filter update.
class FIRType1 : public FIRFilter
{
    public:
        /// Constructs a linear phase type 1 FIR filter using a specified impulse response
        /// @param impulse_response Impulse response
        FIRType1(std::vector<double> impulse_response);

        double update(double input);

    private:
        int m_num_relevant_coefs;
        void init();
};

#endif // FIRTYPE1_H
