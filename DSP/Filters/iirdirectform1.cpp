#include "iirdirectform1.h"

/**
 * @brief Constructs an direct form type 1 IIR filter
 * @param a_coefs
 * @param b_coefs
 */
IIRDirectForm1::IIRDirectForm1(std::vector<double> b_coefs, std::vector<double> a_coefs) :
    IIRFilter(b_coefs, a_coefs)
{
    initFilter();
}

/**
 * @brief Updates filter with input and produces corresponding output
 * @param input Filter input value
 * @return Returns the filter output
 */
double IIRDirectForm1::update(double input)
{
    double output = 0;
    m_buffer_x.insert(input);

    for(unsigned  i = 0; i < m_norm_b_coefs.size(); i++)
    {
        output += m_norm_b_coefs[i]*m_buffer_x[i];
    }

    for(unsigned i = 0; i < m_norm_a_coefs.size(); i++)
    {
        output -= m_norm_a_coefs[i]*m_buffer_y[i]; // note that first coefficient is skipped
    }

    m_buffer_y.insert(output);
    return output;
}

/**
 * @brief Clears (zeros) the filter
 */
void IIRDirectForm1::clearFilter()
{
    m_buffer_x.clear();
    m_buffer_y.clear();
}

/**
 * @brief Returns the normalized 'a' (denominator) coefficients
 * @return Returns the normalized 'a' (denominator) coefficients
 */
std::vector<double> IIRDirectForm1::getNormalizedACoefs()
{
    return m_norm_a_coefs;
}

/**
 * @brief Returns the normalized 'b' (numerator) coefficients
 * @return Returns the normalized 'b' (numerator) coefficients
 */
std::vector<double> IIRDirectForm1::getNormalizedBCoefs()
{
    return m_norm_a_coefs;
}

/*************** Private **************/

/**
 * @brief Initializes filter
 */
void IIRDirectForm1::initFilter()
{
    m_buffer_x.setBufferSize(m_b_coefs.size());
    m_buffer_y.setBufferSize(m_a_coefs.size() - 1); // see note below
    m_norm_a_coefs.resize(m_a_coefs.size() - 1);
    m_norm_b_coefs.resize(m_b_coefs.size());
    calcNormalizedCoefs();

    /* The subtraction of 1 is used due to the fact that the first normalized coefficient (a0)
     * will always equal zero. This coefficient is not directly used in calculating the filter output,
     * thus it will not be included in the normalized 'a' coef vector. */
}

/**
 * @brief Calculates the normalized coefficients to be used in 'direct form 1' implementation
 */
void IIRDirectForm1::calcNormalizedCoefs()
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


