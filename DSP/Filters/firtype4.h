#ifndef FIRTYPE4_H
#define FIRTYPE4_H

#include "firfilter.h"

/// FIRType4 implements an FIR filter of linear phase type 4. This implementation
/// takes advantage of the filter anti-symmetry to reduce the number of multiplications needed
/// during a filter update.
class FIRType4 : public FIRFilter
{
    public:
        /// Constructs a linear phase type 4 FIR filter using a specified impulse response
        /// @param impulse_response Impulse response
        FIRType4(std::vector<double> impulse_response);

        double update(double input);

    private:
        int m_num_relevant_coefs;
        void init();
};

#endif // FIRTYPE4_H
