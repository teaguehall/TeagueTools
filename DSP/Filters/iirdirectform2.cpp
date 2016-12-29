#include "iirdirectform2.h"

IIRDirectForm2::IIRDirectForm2(std::vector<double> b_coefs, std::vector<double> a_coefs) :
    IIRFilter(b_coefs, a_coefs)
{
    initFilter();
}

std::vector<double> IIRDirectForm2::getNormalizedACoefs()
{
    return m_norm_a_coefs;
}

std::vector<double> IIRDirectForm2::getNormalizedBCoefs()
{
    return m_norm_b_coefs;
}

void IIRDirectForm2::clear()
{
    m_buffer.clear();
}

double IIRDirectForm2::update(double input)
{
    double output = 0;
    double v = input;

    /* perform 'pole' section */
    for(unsigned i = 0; i < m_norm_a_coefs.size(); i++)
    {
        v-=m_buffer[i]*m_norm_a_coefs[i];
    }

    m_buffer.insert(v);

    /* perform 'zero' section */
    for(unsigned i = 0; i < m_norm_b_coefs.size(); i++)
    {
        output+= m_buffer[i]*m_norm_b_coefs[i];
    }

    return output;
}

/********************
 * Private Functions
 ********************/

void IIRDirectForm2::initFilter()
{
    m_norm_a_coefs.resize(m_a_coefs.size() - 1); // see note below
    m_norm_b_coefs.resize(m_b_coefs.size());
    m_buffer.setBufferSize(m_a_coefs.size());
    calcNormalizedCoefs();

    /* The subtraction of 1 is used due to the fact that the first normalized coefficient (a0)
     * will always equal zero. This coefficient is not directly used in calculating the filter output,
     * thus it will not be included in the normalized 'a' coef vector. */
}

void IIRDirectForm2::calcNormalizedCoefs()
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
