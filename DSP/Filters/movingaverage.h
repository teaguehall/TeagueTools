#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include "digitalfilter.h"
#include "../../DataStructures/circularbuffer.h"

/// MovingAverage is a class that implements a moving average FIR filter.
class MovingAverage : public DigitalFilter
{
    public:
        /// Constructs a moving average filter of specified size
        /// @param size Size is used to determine how many previous inputs will be used to compute the average.
        MovingAverage(unsigned size);

        /// Sets the size of the moving average filter
        /// @param size Size is used to determine how many previous inputs will be used to compute the average.
        void setSize(unsigned size);

        double update(double input);

        void clear();

    private:
        double m_avg;
        unsigned m_size;
        double m_weight;
        CircularBuffer m_buffer;
};

#endif // MOVINGAVERAGE_H
