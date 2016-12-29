#ifndef FIRTYPE3_H
#define FIRTYPE3_H

#include "firfilter.h"

/// FIRType3 implements an FIR filter of linear phase type 3. This implementation
/// takes advantage of the filter anti-symmetry to reduce the number of multiplications needed
/// during a filter update.
class FIRType3 : public FIRFilter
{
    public:
        /// Constructs a linear phase type 3 FIR filter using a specified impulse response
        /// @param impulse_response Impulse response
        FIRType3(std::vector<double> impulse_response);

        double update(double input);

    private:
        int m_num_relevant_coefs;
        void init();
};

#endif // FIRTYPE3_H
