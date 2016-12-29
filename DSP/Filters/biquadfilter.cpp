#include "biquadfilter.h"

BiquadFilter::BiquadFilter(const std::vector<double>& b_coefs, const std::vector<double>& a_coefs) :
    IIRFilter(b_coefs, a_coefs)
{
    init();
}

std::vector<double> BiquadFilter::getNormalizedACoefs()
{
    return m_norm_a_coefs;
}

std::vector<double> BiquadFilter::getNormalizedBCoefs()
{
    return m_norm_b_coefs;
}

void BiquadFilter::clear()
{
    std::fill(m_buffer.begin(), m_buffer.end(), 0);
}

double BiquadFilter::update(double input)
{
    double output = m_norm_b_coefs[0]*input + m_buffer[0];
    m_buffer[0] = m_norm_b_coefs[1]*input - m_norm_a_coefs[0]*output + m_buffer[1];
    m_buffer[1] = m_norm_b_coefs[2]*input - m_norm_a_coefs[1]*output;
	
    return output;
}

/********************
 * Private Functions
 ********************/

void BiquadFilter::init()
{
    m_buffer.resize(2);
    m_norm_a_coefs.resize(2);
    m_norm_b_coefs.resize(3);
    calcNormalizedCoefs();
}

void BiquadFilter::calcNormalizedCoefs()
{
    double a0 = m_a_coefs[0];

    for(unsigned i = 0; i < m_norm_a_coefs.size(); i++) // normalize 'a' coefficients
    {
        m_norm_a_coefs[i] = m_a_coefs[i+1]/a0; // i+1 is due to the fact that the first 'a' coef (a0) is ignored
    }

    for(unsigned i = 0; i < m_norm_b_coefs.size(); i++) // normalize 'b' coefficients
    {
        m_norm_b_coefs[i] = m_b_coefs[i]/a0;
    }
}
