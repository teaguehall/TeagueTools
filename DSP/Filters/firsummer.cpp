#include "firsummer.h"
#include "algorithm"

FIRSummer::FIRSummer(unsigned size)
{
    m_fir_type = FIRType::summer;
    m_size = size;
    m_buffer.setBufferSize(size);
    m_filter_order = m_size - 1;
    createImpResponse();
}

FIRSummer::FIRSummer(std::vector<double> impulse_response)
{
    m_fir_type = FIRType::summer;
    m_size = impulse_response.size();
    m_buffer.setBufferSize(m_size);
    m_filter_order = m_size - 1;
    createImpResponse();
}

void FIRSummer::setSize(unsigned size)
{
    m_size = size;
    m_buffer.setBufferSize(size);
    m_filter_order = m_size - 1;
    createImpResponse();
}

void FIRSummer::setImpulseResponse(std::vector<double> impulse_response)
{
    m_size = impulse_response.size();
    m_buffer.setBufferSize(m_size);
    m_filter_order = m_size - 1;
    createImpResponse();
}

void FIRSummer::clear()
{
    m_buffer.clear();
}

double FIRSummer::update(double input)
{
    m_buffer.insert(input);
    m_sum = m_sum - m_buffer[m_size] + input;
    return m_sum;
}

void FIRSummer::createImpResponse()
{
    m_impulse_response.resize(m_size);
    std::fill(m_impulse_response.begin(), m_impulse_response.end(), 1);
}
