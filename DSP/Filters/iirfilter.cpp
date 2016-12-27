#include "iirfilter.h"

/**
 * @brief Constructs an IIR filter
 * @param a_coefs The 'a' coefficients of the IIR filter (also known as the denominator coefficients)
 * @param b_coefs The 'b' coefficients of the IIR filter (also known as the numerator coefficients)
 */
IIRFilter::IIRFilter(std::vector<double> b_coefs, std::vector<double> a_coefs) :
    m_a_coefs(a_coefs),
    m_b_coefs(b_coefs)
{
    commonInitFilter();
}

/**
 * @brief Updates filter with input and produces corresponding output
 * @param input Filter input value
 * @return Returns the filter output
 */
double IIRFilter::update(double input)
{
    return input; // this method will be overwritten, so output whatever
}

/**
 * @brief Clears (zeros) the filter history
 */
void IIRFilter::clear()
{
}

/**
 * @brief Sets the 'a' (denominator) and 'b' (numerator' coefficients of the IIR filter.
 * @param a_coefs The 'a' (denominator) coefficients
 * @param b_coefs The 'b' (numerator) coefficients
 */
void IIRFilter::setCoefs(std::vector<double> b_coefs, std::vector<double> a_coefs)
{
    m_a_coefs = a_coefs;
    m_b_coefs = b_coefs;
    commonInitFilter();
    initFilter();
}

/**
 * @brief Sets the 'a'  (denominator) coefficients of the filter
 * @param a_coefs The 'a' (denominator) coefficents
 */
void IIRFilter::setACoefs(std::vector<double> a_coefs)
{
    m_a_coefs = a_coefs;
    commonInitFilter();
    initFilter();
}

/**
 * @brief Sets the 'b'  (numerator) coefficients of the filter
 * @param b_coefs The 'b' (numerator) coefficents
 */
void IIRFilter::setBCoefs(std::vector<double> b_coefs)
{
    m_b_coefs = b_coefs;
    commonInitFilter();
    initFilter();
}

/**
 * @brief Returns the 'a' (denominator) coefficients
 * @return Returns the 'a' (denominator) coefficients
 */
std::vector<double> IIRFilter::getACoefs()
{
    return m_a_coefs;
}

/**
 * @brief Returns the 'b' (numerator) coefficients
 * @return Returns the 'b' (numerator) coefficients
 */
std::vector<double> IIRFilter::getBCoefs()
{
    return m_b_coefs;
}

/******************* Protected *****************/

/**
 * @brief Function to be called when the filter needs to be initialized (e.g. after the
 * filter's coefficients have been modified). This function will be specific to classes
 * that derive from this class.
 */
void IIRFilter::initFilter()
{

}

/******************* Private *****************/

/**
 * @brief This function will be called to initialize the filter after the impulse response has
 * been modified. Note that this function contains initialization code that will be common for
 * all classes that derive from the IIRFilter class.
 */
void IIRFilter::commonInitFilter()
{
    m_filter_order = m_a_coefs.size() - 1;
}

