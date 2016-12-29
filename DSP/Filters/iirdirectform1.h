#ifndef IIRDIRECTFORM1_H
#define IIRDIRECTFORM1_H

#include "iirfilter.h"
#include "../../DataStructures/circularbuffer.h"
#include <vector>

/// The IIRDirectForm1 class implements an IIR filter using direct form 1.
class IIRDirectForm1 : public IIRFilter
{
    public:
        /// Constructs an IIR filter
        /// @param a_coefs Denominator coefficients
        /// @param b_coefs Numerator coefficients
        IIRDirectForm1(std::vector<double> b_coefs = {1}, std::vector<double> a_coefs = {1});

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
        CircularBuffer m_buffer_x;
        CircularBuffer m_buffer_y;

    private:
        /// Calculates the normalized coefficients
        void calcNormalizedCoefs();

        void initFilter();
};

#endif // IIRDIRECTFORM1_H
