#ifndef FIRTYPE2_H
#define FIRTYPE2_H

#include "firfilter.h"

/// FIRType2 implements an FIR filter of linear phase type 2. This implementation
/// takes advantage of the filter symmetry to reduce the number of multiplications needed
/// during a filter update.
class FIRType2 : public FIRFilter
{
    public:
        /// Constructs a linear phase type 2 FIR filter using a specified impulse response
        /// @param impulse_response Impulse response
        FIRType2(std::vector<double> impulse_response);

        double update(double input);

    private:
        int m_num_relevant_coefs;
        void init();
};

#endif // FIRTYPE2_H
