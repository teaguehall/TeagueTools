#ifndef IIRTRANSDIRECTFORM2_H
#define IIRTRANSDIRECTFORM2_H

#include "iirfilter.h"
#include <vector>

/// The IIRTransDirectForm2 class implements an IIR filter using transposed direct form 2.
class IIRTransDirectForm2 : public IIRFilter
{
    public:
        /// Constructs an IIR filter
        /// @param a_coefs Denominator coefficients
        /// @param b_coefs Numerator coefficients
        IIRTransDirectForm2(std::vector<double> b_coefs = {1}, std::vector<double> a_coefs = {1});

        /// Returns the normalized 'a' (denominator) coefficients
        /// @return Returns the normalized 'a' (denominator) coefficients
        std::vector<double> getNormalizedACoefs();

        /// Returns the normalized 'b' (numerator) coefficients
        /// @return Returns the normalized 'b' (numerator) coefficients
        std::vector<double> getNormalizedBCoefs();

        double update(double input);
        void clear();

    protected:
        std::vector<double> m_norm_a_coefs;
        std::vector<double> m_norm_b_coefs;
        std::vector<double> m_buffer;

    private:
        /// This method sizes memory buffer based by checking what coefficient array is larger (a or b)
        void sizeBuffer();

        /// Calculates the normalized coefficients
        void calcNormalizedCoefs();

        void initFilter();
};

#endif // IIRTRANSDIRECTFORM2_H
