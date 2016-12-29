#include "firtype4.h"

FIRType4::FIRType4(std::vector<double> impulse_response) :
    FIRFilter(impulse_response)
{
    m_fir_type = FIRType::linearphasetype4;
    init();
}

double FIRType4::update(double input)
{
    int i = 0;
    double output = 0;
    m_buffer.insert(input);

    for(i = 0; i < m_num_relevant_coefs; i++)
    {
        output += m_impulse_response[i]*(m_buffer[i] - m_buffer[m_filter_order - i]);
    }
    return output;
}

/********************
 * Private Functions
 ********************/

void FIRType4::init()
{
    m_num_relevant_coefs = (int)(m_impulse_response.size()/2);
}

