#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include "firfilter.h"
#include <vector>

/// MovingAverage is a class that implements a moving average FIR filter.
class MovingAverage : public FIRFilter
{
    public:
        /// Constructs a moving average filter of specified size
        /// @param size Size is used to determine how many previous inputs will be used to compute the average.
        MovingAverage(unsigned size);

        /// Constructs a moving average filter of specified impulse response. Note that this constructor
        /// will look at the first coefficient and will assume the rest are equivalent.
        /// @param impulse_response Impulse response of moving average filter. All elements should be equal and sum to 1.
        MovingAverage(std::vector<double> impulse_response);

        /// Sets the size of the moving average filter
        /// @param size Size is used to determine how many previous inputs will be used to compute the average.
        void setSize(unsigned size);

        /// Sets the impulse response of the FIR filter
        /// @param impulse_response Impulse response
        void setImpulseResponse(std::vector<double> impulse_response);

        double update(double input);

        void clear();

    protected:
        double m_avg;
        unsigned m_size;
        double m_weight;

        /// Creates the associated impulse response when the 'setSize' method has been called. Example:
        /// 'MovingAverage::setSize(5)' -> impulse response = {0.2, 0.2, 0.2, 0.2, 0.2}
        void createImpResponse();
};

#endif // MOVINGAVERAGE_H
