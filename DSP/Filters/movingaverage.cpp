#include "movingaverage.h"
#include "algorithm"

MovingAverage::MovingAverage(unsigned size)
{
    m_fir_type = FIRType::movingaverage;
    m_size = size;
    m_weight = 1.0/size;
    m_buffer.setBufferSize(size);
    m_filter_order = m_size - 1;
    createImpResponse();
}

MovingAverage::MovingAverage(std::vector<double> impulse_response)
{
    m_fir_type = FIRType::movingaverage;
    m_impulse_response = impulse_response;
    m_size = impulse_response.size();
    m_weight = 1.0/m_size;
    m_buffer.setBufferSize(m_size);
    m_filter_order = m_size - 1;
}

void MovingAverage::setSize(unsigned size)
{
    m_size = size;
    m_weight = 1.0/size;
    m_buffer.setBufferSize(size);
    m_filter_order = m_size - 1;
    createImpResponse();
}

void MovingAverage::setImpulseResponse(std::vector<double> impulse_response)
{
    m_impulse_response = impulse_response;
    m_size = impulse_response.size();
    m_weight = 1.0/m_size;
    m_buffer.setBufferSize(m_size);
    m_filter_order = m_size - 1;
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

void MovingAverage::createImpResponse()
{
    m_impulse_response.resize(m_size);
    std::fill(m_impulse_response.begin(), m_impulse_response.end(), m_weight);
}
