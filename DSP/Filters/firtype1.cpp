#include "firtype1.h"

FIRType1::FIRType1(std::vector<double> impulse_response) :
    FIRFilter(impulse_response)
{
    m_fir_type = FIRType::linearphasetype1;
    init();
}

double FIRType1::update(double input)
{
    int i = 0;
    double output = 0;
    m_buffer.insert(input);

    for(i = 0; i < (m_num_relevant_coefs - 1); i++)
    {
        output += m_impulse_response[i]*(m_buffer[i] + m_buffer[m_filter_order - i]);
    }
    output+= m_impulse_response[i]*m_buffer[i];
    return output;
}

/********************
 * Private Functions
 ********************/

void FIRType1::init()
{
    m_num_relevant_coefs = (int)std::ceil(m_impulse_response.size()/2.0);
}

