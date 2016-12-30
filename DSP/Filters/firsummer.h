#ifndef FIRSUMMER_H
#define FIRSUMMER_H

#include "firfilter.h"
#include <vector>

/// FIRSummer is a summing FIR filter. This filter has an impulse response in which every coefficient
/// equals 1.
class FIRSummer : public FIRFilter
{
    public:
        /// Constructs a FIR summer filter of specified size
        /// @param size Size is used to determine how many previous inputs will be used in the sum.
        FIRSummer(unsigned size);

        /// Constructs an FIR summer filter of specified impulse response. Note that this constructor
        /// will only look at the size of the provided impulse response and assume every coeffiecient
        /// equals 1.
        /// @param impulse_response Impulse response of FIR summer filter. All elements should equal 1.
        FIRSummer(std::vector<double> impulse_response);

        /// Sets the size of the FIR summer filter.
        /// @param size Size is used to determine how many previous inputs will be used in the sum.
        void setSize(unsigned size);

        /// Sets the impulse response of the FIR filter
        /// @param impulse_response Impulse response
        void setImpulseResponse(std::vector<double> impulse_response);

        double update(double input);

        void clear();

    protected:
        double m_sum;
        unsigned m_size;

        /// Creates the associated impulse response when the 'setSize' method has been called. Example:
        /// 'FIRSummer::setSize(5)' -> impulse response = {1, 1, 1, 1, 1}
        void createImpResponse();
};

#endif // FIRSUMMER_H
