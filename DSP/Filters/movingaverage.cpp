#include "movingaverage.h"

MovingAverage::MovingAverage(unsigned size) :
    m_size(size),
    m_weight(1.0/size),
    m_buffer(size)
{
    m_filter_order = size - 1;
}

void MovingAverage::setSize(unsigned size)
{
    m_size = size;
    m_weight = 1.0/size;
    m_buffer.setBufferSize(size);
    m_filter_order = size - 1;
}

void MovingAverage::clear()
{
    m_buffer.clear();
}

double MovingAverage::update(double input)
{
    m_buffer.insert(input);
    m_avg = m_avg - m_weight*m_buffer[m_size] + m_weight*input;
    return m_avg;
}
