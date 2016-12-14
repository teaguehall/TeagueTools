#include "qmfbank.h"

/**
 * @brief Creates a quadrature mirror filter bank
 * @param p_in A reference to an input source
 */
QMFBank::QMFBank(std::shared_ptr<double> p_in) :
    m_p_in(p_in)
{
}

/**
 * @brief Sets the reference to the QMF banks input source
 * @param p_in A reference to an input source
 */
void QMFBank::setInputReference(std::shared_ptr<double> p_in)
{
    m_p_in = p_in;
}

/**
 * @brief Retrieves a reference to the lowpassband output
 * @return Returns a shared pointer to the lowpassband output
 */
std::shared_ptr<double> QMFBank::getLowBandReference()
{
    return m_p_out_lowband;
}

/**
 * @brief Retrieves a reference to the highpassband output
 * @return Returns a shared pointer to the highpassband output
 */
std::shared_ptr<double> QMFBank::getHighBandReference()
{
    return m_p_out_highband;
}

/**
 * @brief Clears (zeros) the filter bank history
 */
void QMFBank::clearFilter()
{
}

/**
 * @brief Updates the filter bank.
 * When this method is called, the filter bank will retrieve a new input and update its outputs
 */
void QMFBank::update()
{
}



