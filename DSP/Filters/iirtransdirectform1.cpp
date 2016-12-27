#include "iirtransdirectform1.h"
#include <iostream>

/**
 * @brief Constructs a 'transposed direct form 1' IIR filter
 * @param a_coefs
 * @param b_coefs
 */
IIRTransDirectForm1::IIRTransDirectForm1(std::vector<double> b_coefs, std::vector<double> a_coefs) :
    IIRFilter(b_coefs, a_coefs)
{
    initFilter();
}

/**
 * @brief Returns the normalized 'a' (denominator) coefficients
 * @return Returns the normalized 'a' (denominator) coefficients
 */
std::vector<double> IIRTransDirectForm1::getNormalizedACoefs()
{
    return m_norm_a_coefs;
}

/**
 * @brief Returns the normalized 'b' (numerator) coefficients
 * @return Returns the normalized 'b' (numerator) coefficients
 */
std::vector<double> IIRTransDirectForm1::getNormalizedBCoefs()
{
    return m_norm_b_coefs;
}

/**
 * @brief Clears (zeros) the filter
 */
void IIRTransDirectForm1::clear()
{
    std::fill(m_buffer_1.begin(), m_buffer_1.end(), 0);
    std::fill(m_buffer_2.begin(), m_buffer_2.end(), 0);
}

/**
 * @brief Updates filter with input and produces corresponding output
 * @param input Filter input value
 * @return Returns the filter output
 */
double IIRTransDirectForm1::update(double input)
{
    unsigned i;
    double v = input + m_buffer_1[0];
    double output;

    // calculate buffer 1
    for(i = 0; i < m_buffer_1.size()-1; i++)
    {
        m_buffer_1[i] = m_buffer_1[i+1] - v*m_norm_a_coefs[i];
    }
    m_buffer_1[i] = - v*m_norm_a_coefs[i];

    output = v*m_norm_b_coefs[0] + m_buffer_2[0];

    // calculate memory 2
   for(i = 0; i < m_buffer_2.size()-1; i++)
   {
       m_buffer_2[i] = m_buffer_2[i+1] + v*m_norm_b_coefs[i+1];
   }
   m_buffer_2[i] = v*m_norm_b_coefs[i+1];

   return output;
}

/*************** Private **************/
/**
 * @brief Initializes filter
 */
void IIRTransDirectForm1::initFilter()
{
    m_buffer_1.resize(m_a_coefs.size() - 1);
    m_buffer_2.resize(m_b_coefs.size() - 1);
    m_norm_a_coefs.resize(m_a_coefs.size() - 1);  // see note below
    m_norm_b_coefs.resize(m_b_coefs.size());
    calcNormalizedCoefs();

    /* The subtraction of 1 (for m_norm_a_coefs sizing) is used due to the fact that the first normalized coefficient (a0)
     * will always equal zero. This coefficient is not directly used in calculating the filter output,
     * thus it will not be included in the normalized 'a' coef vector. */
}

/**
 * @brief Calculates the normalized coefficients to be used in 'direct form' implementations
 */
void IIRTransDirectForm1::calcNormalizedCoefs()
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
