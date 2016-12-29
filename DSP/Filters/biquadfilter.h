#ifndef BIQUADFILTER_H
#define BIQUADFILTER_H

#include "iirfilter.h"
#include <vector>

/// BiquadFilter is a class that implements a 2nd order IIR filter. This class is implemented in
/// transposed direct form 2.
class BiquadFilter : public IIRFilter
{
    public:
        /// Constructs a biquad IIR filter implemented in 'transposed direct form 2'
        /// @param a_coefs Denominator coefficients (3 coefs should be provided)
        /// @param b_coefs Numerator coefficients (3 coefs should be provided)
        BiquadFilter(const std::vector<double>& b_coefs = {1, 1, 1}, const std::vector<double>& a_coefs = {1, 1, 1});

        /// Returns the normalized 'a' (denominator) coefficients
        /// @return Normalized 'a' (denominator) coefficients
        std::vector<double> getNormalizedACoefs();

        /// Returns the normalized 'b' (numerator) coefficients
        /// @return Normalized 'b' (numerator) coefficients
        std::vector<double> getNormalizedBCoefs();

        double update(double input);
        void clear();

    protected:
        std::vector<double> m_norm_a_coefs;
        std::vector<double> m_norm_b_coefs;
        std::vector<double> m_buffer;

    private:

        void init();

        /// Calculates the normalized coefficients to be used in 'direct form' implementations
        void calcNormalizedCoefs();
};

#endif // BIQUADFILTER_H
