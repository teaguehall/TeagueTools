#ifndef IIRTRANSDIRECTFORM1_H
#define IIRTRANSDIRECTFORM1_H

#include "iirfilter.h"
#include "../../DataStructures/circularbuffer.h"
#include <vector>

/// The IIRTransDirectForm1 class implements an IIR filter using transposed direct form 1.
class IIRTransDirectForm1 : public IIRFilter
{
    public:
        /// Constructs an IIR filter
        /// @param a_coefs Denominator coefficients
        /// @param b_coefs Numerator coefficients
        IIRTransDirectForm1(std::vector<double> b_coefs = {1}, std::vector<double> a_coefs = {1});

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
        std::vector<double> m_buffer_1; // corresponds to input side
        std::vector<double> m_buffer_2; // corresponds to output side

    private:
        /// Calculates the normalized coefficients
        void calcNormalizedCoefs();

        void initFilter();
};

#endif // IIRTRANSDIRECTFORM1_H
