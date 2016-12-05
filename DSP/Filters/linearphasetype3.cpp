#include "linearphasetype3.h"

/**
 * @brief Constructs a type 3 linear phase FIR filter.
 * @param first_half_imp_response The first half of the impulse response.
 */

LinearPhaseType3::LinearPhaseType3(std::vector<double> impulse_response) :
    FIRFilter(impulse_response)
{
    m_fir_type = linearphasetype3;
    initFilter();
}

/**
 * @brief Accepts input and calculates filter output
 *
 * @param input Filter input
 * @return Returns filter output
 */
double LinearPhaseType3::update(double input)
{
    int i = 0;
    double output = 0;
    m_buffer.insert(input);
    for(i = 0; i < (m_num_relevant_coefs - 1); i++)
    {
        output += m_impulse_response[i]*(m_buffer[i] - m_buffer[m_filter_order - i]);
    }
    output+= m_impulse_response[i]*m_buffer[i];
    return output;
}

/********************** Private *****************/

/**
 * @brief Reinitializes filter after the impulse respone has been modified
 */
void LinearPhaseType3::initFilter()
{
    m_num_relevant_coefs = (int)std::ceil(m_impulse_response.size()/2.0);
}

