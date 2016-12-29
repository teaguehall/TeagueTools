#include "firfilter.h"

FIRFilter::FIRFilter(std::vector<double> impulse_response) :
    m_impulse_response(impulse_response)
{
    commonInit();
}

void FIRFilter::setImpulseResponse(std::vector<double> impulse_response)
{
    m_impulse_response = impulse_response;
    commonInit();
    init();
}

std::vector<double> FIRFilter::getImpulseResponse()
{
    return m_impulse_response;
}

FIRFilter::FIRType FIRFilter::getFIRType()
{
    return m_fir_type;
}

void FIRFilter::clear()
{
    m_buffer.clear();
}

/********************
 * Private Functions
 ********************/

void FIRFilter::commonInit()
{
    m_filter_order = m_impulse_response.size() - 1;
    m_buffer.setBufferSize(m_impulse_response.size());
}
