#include "iirtransdirectform2.h"

IIRTransDirectForm2::IIRTransDirectForm2(std::vector<double> b_coefs, std::vector<double> a_coefs) :
    IIRFilter(b_coefs, a_coefs)
{
    initFilter();
}

std::vector<double> IIRTransDirectForm2::getNormalizedACoefs()
{
    return m_norm_a_coefs;
}

std::vector<double> IIRTransDirectForm2::getNormalizedBCoefs()
{
    return m_norm_b_coefs;
}

void IIRTransDirectForm2::clear()
{
    std::fill(m_buffer.begin(), m_buffer.end(), 0);
}

double IIRTransDirectForm2::update(double input)
{
    unsigned i;
    double output = m_norm_b_coefs[0]*input + m_buffer[0];

    // add previous states
    for(i = 0; i < m_buffer.size() - 1; i++)
    {
        m_buffer[i] = m_buffer[i+1];
    }
    m_buffer[i] = 0;

    // add b_coefs*input
    for(i = 0; i < m_norm_b_coefs.size() - 1; i++)
    {
        m_buffer[i] = m_buffer[i] + input*m_norm_b_coefs[i+1];
    }

    // subtrack a_coefs*output
    for(i = 0; i < m_norm_a_coefs.size(); i++)
    {
        m_buffer[i] = m_buffer[i] - output*m_norm_a_coefs[i];
    }

   return output;
}

/********************
 * Private Functions
 ********************/

void IIRTransDirectForm2::initFilter()
{
    sizeBuffer();
    m_norm_a_coefs.resize(m_a_coefs.size() - 1);  // see note below
    m_norm_b_coefs.resize(m_b_coefs.size());
    calcNormalizedCoefs();

    /* The subtraction of 1 (for m_norm_a_coefs sizing) is used due to the fact that the first normalized coefficient (a0)
     * will always equal zero. This coefficient is not directly used in calculating the filter output,
     * thus it will not be included in the normalized 'a' coef vector. */
}

void IIRTransDirectForm2::sizeBuffer()
{
    if(m_b_coefs.size() > m_a_coefs.size())
        m_buffer.resize(m_b_coefs.size() - 1);
    else
        m_buffer.resize(m_a_coefs.size() - 1);
}

void IIRTransDirectForm2::calcNormalizedCoefs()
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
