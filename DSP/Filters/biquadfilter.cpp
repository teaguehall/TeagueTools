#include "biquadfilter.h"

/**
 * @brief Constructs a biquad IIR filter implemented in 'transposed direct form 2'
 * @param a_coefs
 * @param b_coefs
 */
BiquadFilter::BiquadFilter(std::vector<double> b_coefs, std::vector<double> a_coefs) :
    IIRFilter(b_coefs, a_coefs)
{
    initFilter();
}

/**
 * @brief Returns the normalized 'a' (denominator) coefficients
 * @return Returns the normalized 'a' (denominator) coefficients
 */
std::vector<double> BiquadFilter::getNormalizedACoefs()
{
    return m_norm_a_coefs;
}

/**
 * @brief Returns the normalized 'b' (numerator) coefficients
 * @return Returns the normalized 'b' (numerator) coefficients
 */
std::vector<double> BiquadFilter::getNormalizedBCoefs()
{
    return m_norm_b_coefs;
}

/**
 * @brief Clears (zeros) the filter
 */
void BiquadFilter::clearFilter()
{
    std::fill(m_buffer.begin(), m_buffer.end(), 0);
}

/**
 * @brief This method updates the filter using transposed direct form 2 implementation
 *
 * @param input Filter input value
 * @return Returns the filter output
 */
double BiquadFilter::update(double input)
{
    double output = m_norm_b_coefs[0]*input + m_buffer[0];
    m_buffer[0] = m_norm_b_coefs[1]*input - m_norm_a_coefs[0]*output + m_buffer[1];
    m_buffer[1] = m_norm_b_coefs[2]*input - m_norm_a_coefs[1]*output;
	
    return output;
}

/*************** Private **************/
/**
 * @brief Initializes filter
 */
void BiquadFilter::initFilter()
{
    m_buffer.resize(2);
    m_norm_a_coefs.resize(2);
    m_norm_b_coefs.resize(3);
    calcNormalizedCoefs();
}

/**
 * @brief Calculates the normalized coefficients to be used in 'direct form' implementations
 */
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
