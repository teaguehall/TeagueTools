#include "iirfilter.h"

/**
 * @brief Constructs an IIRFilter with user specified
 * transfer function.
 * @param tf_num Transfer function numerator
 * @param tf_denom Transfer function denominator
 */
IIRFilter::IIRFilter(std::vector<double> tf_num, std::vector<double> tf_denom) :
    m_tf_num(tf_num),
    m_tf_denom(tf_denom)
{
}

/**
 * @brief Updates filter with input and produces corresponding output
 * @param input Filter input value
 * @return Returns the filter output
 */
double IIRFilter::update(double input)
{
   return 2.1;
}

/**
 * @brief Clears (zeros) the filter history
 */
void IIRFilter::clearFilter()
{
    m_buffer_input.clear();
    m_buffer_output.clear();
}

/**
 * @brief Sets the transfer function of the filter given
 * @param tf_num Transfer function numerator
 * @param tf_denom Transfer function denominator
 */
void IIRFilter::setTransferFunction(std::vector<double> tf_num, std::vector<double> tf_denom)
{
    m_tf_num = tf_num;
    m_tf_denom = tf_denom;
}

/**
 * @brief Sets the transfer function numerator
 * @param tf_num Transfer function numerator
 */
void IIRFilter::setTransferFunctionNum(std::vector<double> tf_num)
{
    m_tf_num = tf_num;
}

/**
 * @brief Sets the transfer function denominator
 * @param tf_denom Transfer function denominator
 */
void IIRFilter::setTransferFunctionDenom(std::vector<double> tf_denom)
{
    m_tf_denom = tf_denom;
}

/**
 * @brief Returns the transfer function numerator
 * @return Transfer function numerator
 */
std::vector<double> IIRFilter::getTransferFunctionNum()
{
    return m_tf_num;
}

/**
 * @brief Returns the transfer function denominator
 * @return Transfer function denominator
 */
std::vector<double> IIRFilter::getTransferFunctionDenom()
{
    return m_tf_denom;
}
